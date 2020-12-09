#include <vector>
#include <string>
#include <utility>
#include <iostream>
#include <unordered_set>

using namespace std;

// global accumulator
int acc = 0;

/*
    Converts the vector of strings into a vector of pairs representing the instruction and value associated with it.
*/
vector<pair<string, int>> getPairs(vector<string> input) {
    vector<pair<string, int>> vt;
    for (string s : input) {
        vt.push_back(make_pair(s.substr(0, 3), stoi(s.substr(4))));
    }
    return vt;
}

/*
    Loops through the vector of instructions and returns true if an infinite loop is detected.
    This is determined by whether a given instruction is visited twice.
*/
bool loop(vector<pair<string, int>> vt) {
    int i = 0;
    pair<string, int> current;
    unordered_set<int> us;
    while (i < vt.size()) {
        current = vt[i];
        if (us.count(i) > 0) {
            return true;
        } else {
            us.insert(i);
        }
        if (current.first.compare("acc") == 0) {
            acc += current.second;
            i++;
        } else if (current.first.compare("jmp") == 0) {
            i += current.second;
        } else if (current.first.compare("nop") == 0) {
            i++;
        }
    }
    return false;
}

/*
    Returns the accumulator value right before an infinite loop is detected.
*/
int infiniteLoopAcc(vector<string> input) {
    vector<pair<string, int>> vt = getPairs(input);
    return loop(vt) == true ? acc : 0;
}

/*
    Fixes the instructions by converting either a single "jmp" to a "nop" or a "nop" to a "jmp".
    Returns the accumulator value after sucessfully terminating from the instructions, as determined
    by going past the last index of the input.
*/
int fixInfiniteLoop(vector<string> input) {
    vector<pair<string, int>> vt = getPairs(input);
    for (int i = 0; i < vt.size(); i++) {
        acc = 0;
        bool check = false;
        pair<string, int> current = vt[i];
        unordered_set<int> us;
        vector<pair<string, int>> vt2;
        if (current.first.compare("jmp") == 0) {
            vt2 = getPairs(input);
            vt2[i].first = "nop";
            check = true;
        } else if (current.first.compare("nop") == 0) {
            vt2 = getPairs(input);
            vt2[i].first = "jmp";
            check = true;
        }
        if (check) {
            if (loop(vt2) == false) {
                return acc;
            }
        }
    }
    return acc;
}