#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <regex>
#include <iostream>
#include <queue>
#include <deque>

using namespace std;

/*
    Uses regex to split a vector of strings into rules for luggage represented as a map with a bag as the key, and
    the bags that can be contained inside them as the values.
*/
unordered_map<string, vector<string>> getMap(vector<string> input) {
    unordered_map<string, vector<string>> m;
    auto const r = regex("^.*(?=( bags contain))");
    auto const r2 = regex("([0-9]+.*?(?= bag))");
    string key;
    string vals;
    string val;
    for (string s : input) {
        smatch match;
        bool textContains = regex_search(s, match, r);
        key = match.str();
        vals = match.suffix();
        match = smatch{};
        while(regex_search(vals, match, r2)) {
            val = match.str();
            // add multiple bags to the map if there are more than 1 of a certain kind that can fit in the key
            for (int i = 0; i < (int)val[0] - 48; i++) {
                m[key].push_back(val.substr(2));
            }
            vals = match.suffix();
        }
    }
    return m;
}

/*
    Takes a map of strings to vectors of strings as an input that represents the bags and the bags that can be contained in them.
    Searches through each key in the map to check whether a certain bag can be contained in that key. 
    Returns the total number of bags that the "shiny gold" bag can be contained in.
*/
int shinyGold(unordered_map<string, vector<string>> um) {
    int total = 0;
    string check = "shiny gold";
    unordered_set<string> cache;            // bags that can hold the check string
    unordered_set<string> badCache;         // bags that will never contain the check string
    for (auto a : um) {
        // increments total if the cache contains the current map key
        if (cache.count(a.first) == 1) {
            total++;
        } 
        // increments total if the map values contain the check string
        else if (find(a.second.begin(), a.second.end(), check) != a.second.end()) {
            cache.insert(a.first);
            total++;
        } else {
            queue<string> q;
            vector<string> a2 = a.second;
            unique(a2.begin(), a2.end());
            // adds all the unique bag values to a queue that are not contained in the bad cache
            for (string s : a2) {
                if (badCache.count(s) == 0) {
                    q.push(s);
                }
            }
            // checks each map key of the queue and adds its corresponding map values to the end of the queue to be checked
            while (!q.empty()) {
                // breaks out of the while loop if cache contains the current head of the queue
                if (cache.count(q.front()) == 1) {
                    total++;
                    break;
                }
                // breaks out of the loop if the current head is equal to the check string
                else if (q.front().compare(check) == 0) {
                    cache.insert(a.first);
                    total++;
                    break;
                } 
                // add all values from the map using the queue head as the key to the back of the queue
                else {
                    vector<string> v = um[q.front()];
                    unique(v.begin(), v.end());
                    for (string s : v) {
                        if (badCache.count(s) == 0) {
                            q.push(s);
                        }
                    }
                    q.pop();
                }
            }
            // inserts the current key to the bad cache if the check string can't be contained in it
            if (q.empty() && a.first.compare(check) != 0) {
                badCache.insert(a.first);
            }
        }
    }
    return total;
}

/*
    Returns the total number of bags that can fit inside of the "shiny gold" bag at once
*/
int shinyGoldBags(unordered_map<string, vector<string>> um) {
    int total = 0;
    queue<string> q;
    // check each value from the base rule for "shiny gold" bags
    for (string s : um["shiny gold"]) {
        q.push(s);
    }
    // check each nested rule until there aren't any more to check
    while (!q.empty()) {
        total++;
        for (string s : um[q.front()]) {
            q.push(s);
        }
        q.pop();
    }
    return total;
}