#include <vector>
#include <string>
#include <algorithm>
#include <regex>
#include <unordered_set>
#include <unordered_map>
#include <queue>

using namespace std;

/*
    Returns a set containing all the values contained in a range of numbers, as denoted by the input string
    in the form "X-Y"
*/
unordered_set<int> getRange(string s) {
    auto const r = regex("([0-9]+-[0-9]+)");
    unordered_set<int> ranges;
    smatch match;
    // regex match to find the range of numbers
    while(regex_search(s, match, r)) {
        string matched = match.str();
        string num = "";
        int first;
        int last;
        // split the matched sting into a first and last number
        for (int i = 0; i < matched.length(); i++) {
            if (matched[i] != '-') {
                num += matched[i];
            } else {
                first = stoi(num);
                num = "";
            }
        }
        last = stoi(num);
        // add all numbers in the current range to the set
        for (int i = first; i <= last; i++) {
            ranges.insert(i);
        }
        // remove the current match from the string
        s = match.suffix();
    }
    return ranges;
}

/*
    Returns a set of every single number in each of the ranges
*/
unordered_set<int> getAllRanges(vector<string> input) {
    unordered_set<int> ranges;
    for (string s : input) {
        for (int i : getRange(s)) {
            ranges.insert(i);
        }
    }
    return ranges;
}

/*
    Returns a mapping of the field number to its range
*/
unordered_map<int, unordered_set<int>> getRangeByField(vector<string> input) {
    unordered_map<int, unordered_set<int>> fieldMap;
    for (int i = 0; i < input.size(); i++) {
        fieldMap[i] = getRange(input[i]);
    }
    return fieldMap;
}

/*
    Converts a comma separated string of numbers to a vector of ints
*/
vector<int> getInts(string s) {
    vector<int> nums;
    auto const r = regex("([0-9]+)");
    smatch match;
    // regex match to split ticket numbers
    while(regex_search(s, match, r)) {
        nums.push_back(stoi(match.str()));

        // remove the current match from the string
        s = match.suffix();
    }
    return nums;
}

/*
    Returns the sum of each element in the list of tickets that is not contained in the total range
*/
int sumOfInvalidTickets(vector<string> input, unordered_set<int> ranges) {
    int sum = 0;
    auto const r = regex("([0-9]+)");
    for (string s : input) {
        smatch match;
        // regex match to split ticket numbers
        while(regex_search(s, match, r)) {
            int matched = stoi(match.str());
            if (ranges.count(matched) == 0) {
                sum += matched;
            }
            // remove the current match from the string
            s = match.suffix();
        }
    }
    return sum;
}

/*
    Returns a vector of valid tickets, where each ticket is represented as a vector of ints
*/
vector<vector<int>> discardInvalidTickets(vector<string> input, unordered_set<int> ranges) {
    vector<vector<int>> tickets;
    auto const r = regex("([0-9]+)");
    for (string s : input) {
        vector<int> ticket;
        smatch match;
        bool valid = true;
        // regex match to split ticket numbers
        while(regex_search(s, match, r)) {
            int matched = stoi(match.str());
            if (ranges.count(matched) == 0) {
                valid = false;
            }
            ticket.push_back(matched);
            // remove the current match from the string
            s = match.suffix();
        }
        
        if (valid) {
            // add current ticket to the list of valid tickets
            tickets.push_back(ticket);
        }
    }
    return tickets;
}

/*
    Takes in a map of field numbers to row number guesses as input.
    Finds which key in the map only has a single value, and creates a pair of the field number to row number
    as indicated by that value. This value is then removed from every other key's set, and the pattern continues
    until the map is empty.
    Returns the final pairs of field numbers to row numbers.
*/
vector<pair<int, int>> getFinalPairs(unordered_map<int, unordered_set<int>> indexToIndex) {
    vector<pair<int, int>> finalPairs;
    while (indexToIndex.size() != 0) {
        unordered_set<int> eraseIndices;
        for (auto a : indexToIndex) {
            if (a.second.size() == 0) {
                // key has no more values
                break;
            } else if (a.second.size() == 1) {
                // only one value in the key's set, so that must be the correct one
                int only = *a.second.begin();
                finalPairs.push_back(make_pair(a.first, only));
                // remove this value from every other key's set
                for (auto b : indexToIndex) {
                    if (b.second.count(only) == 1) {
                        indexToIndex[b.first].erase(only);
                        if (indexToIndex[b.first].size() == 0) {
                            eraseIndices.insert(b.first);
                        }
                    }
                }
                
            }
        }
        // remove empty key from map
        for (int i : eraseIndices) {
            indexToIndex.erase(i);
        }
    }
    return finalPairs;
}

/*
    Returns the error rate of the tickets, as represented by the sum of values not included in the range of any field
*/
int errorRate(vector<string> input) {
    // get the set of values included in every range
    vector<string>::iterator it = find(input.begin(), input.end(), "");
    unordered_set<int> ranges = getAllRanges(vector<string> (input.begin(), it));

    // get the vector of nearby tickets
    auto it2 = find(input.rbegin(), input.rend(), "");
    vector<string> tickets (input.rbegin(), it2 - 1);
    return sumOfInvalidTickets(tickets, ranges);
}

/*
    Returns the product of each value in "my ticket" from the fields that start with the word "departure"
*/
unsigned long long int multiplyDeparture(vector<string> input) {
    unsigned long long int mult = 1;

    // get the set of values included in every range
    vector<string>::iterator it = find(input.begin(), input.end(), "");
    vector<string> fields (input.begin(), it);
    unordered_set<int> ranges = getAllRanges(fields);

    // get the vector of all tickets and discard any that are invalid
    auto it2 = find(input.rbegin(), input.rend(), "");
    vector<string> ticketStrings (input.rbegin(), it2 - 1);
    auto it3 = find(input.begin(), input.end(), "your ticket:");
    string myString = vector<string> (it3, it3 + 2)[1];
    ticketStrings.push_back(myString);

    vector<vector<int>> tickets = discardInvalidTickets(ticketStrings, ranges);

    // creates a map of row indices to all the values contained in that row
    unordered_map<int, unordered_set<int>> ticketMap;
    for (int i = 0; i < tickets.size(); i++) {
        for (int j = 0; j < tickets[0].size(); j++) {
            ticketMap[j].insert(tickets[i][j]);
        }
    }

    // gets the map of field indices to the range of that field
    unordered_map<int, unordered_set<int>> fieldMap = getRangeByField(fields);

    unordered_map<int, unordered_set<int>> indexToIndex;
    // make a map representing the field index to the guesses for row indices
    for (auto a : fieldMap) {
        for (auto b : ticketMap) {
            bool include = true;
            for (int i : b.second) {
                if (a.second.count(i) == 0) {
                    include = false;
                    break;
                }
            }
            if (include) {
                indexToIndex[a.first].insert(b.first);
            }
        }
    }

    // final result of field index to row index
    vector<pair<int, int>> finalPairs = getFinalPairs(indexToIndex);    

    // gets the numbers represented in "my ticket"
    vector<int> myStringValues = getInts(myString);

    // get the indices of fields that contain the word "departure"
    unordered_set<int> departures;
    for (int i = 0; i < fields.size(); i++) {
        if(fields[i].find("departure") != string::npos) {
            departures.insert(i);
        }
    }

    // multiply the values contained in "my ticket" together that have the word "departure" in their field name
    for (pair<int, int> p : finalPairs) {
        if (departures.count(p.first) == 1) {
            mult *= myStringValues[p.second];
        }
    }

    return mult;
}