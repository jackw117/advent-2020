#include <vector>
#include <string>
#include <iostream>
#include <unordered_map>
#include <queue>

using namespace std;

/*
    Returns the input vector (a single string) as a vector of ints
*/
vector<int> getInts(vector<string> input) {
    string s = input[0];
    string delimiter = ",";
    vector<int> nums;
    size_t pos = 0;
    string token;
    int i = 0;
    while ((pos = s.find(delimiter)) != string::npos) {
        token = s.substr(0, pos);
        nums.push_back(stoi(token));
        s.erase(0, pos + delimiter.length());
        i++;
    }
    nums.push_back(stoi(s));
    return nums;
}

/*
    Returns the nth number in the sequence of the memory game
*/
int getNthNum(vector<string> input, int stop) {
    vector<int> nums = getInts(input);
    // stores the spoken number with the indices it is spoken on
    unordered_map<int, priority_queue<int>> numToIndex;
    for (int i = 0; i < nums.size(); i++) {
        numToIndex[nums[i]].push(i);
    }
    int last = nums[nums.size() - 1];
    for (int i = nums.size(); i < stop; i++) {
        if (numToIndex[last].size() > 1) {
            // the new spoken number is the difference in the two indices it was previously spoken on
            int lastSpoken = numToIndex[last].top();
            numToIndex[last].pop();
            int newLast = lastSpoken - numToIndex[last].top();
            numToIndex[last].push(lastSpoken);
            last = newLast;
        } else {
            last = 0;
        }
        numToIndex[last].push(i);
    }
    return last;
}