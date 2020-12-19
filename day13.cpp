#include <vector>
#include <string>
#include <regex>
#include <iostream>
#include <cmath>
#include <climits>
#include <unordered_map>
#include <execution>
#include <numeric>

using namespace std;

unordered_map<int, int> getNums(string s) {
    string delimiter = ",";
    unordered_map<int, int> nums;
    size_t pos = 0;
    string token;
    int i = 0;
    while ((pos = s.find(delimiter)) != string::npos) {
        token = s.substr(0, pos);
        if (token.compare("x") != 0) {
            nums[i] = stoi(token);
        }
        s.erase(0, pos + delimiter.length());
        i++;
    }
    if (s.compare("x") != 0) {
        nums[i] = stoi(s);
    }
    return nums;
}

int earliestBus(vector<string> input) {
    int earliest = INT_MAX;
    int start = stoi(input[0]);
    unordered_map<int, int> nums = getNums(input[1]);
    int earliestID = 0;

    for (auto i : nums) {
        double i2 = i.second;
        int nearest = ceil(start / i2) * i2;
        earliest = min(nearest, earliest);
        if (earliest == nearest) {
            earliestID = i2;
        }
    }
    return (earliest - start) * earliestID;
}

unsigned long long int earliestSequence(vector<string> input) {
    unordered_map<int, int> nums = getNums(input[1]);
    unsigned long long int minValue = 0;
    unsigned long long int prod = 1;

    for (auto i : nums) {
        while ((minValue + i.first) % i.second != 0) {
            minValue += prod;
        }
        
        prod *= i.second;
        int test = 0;
    }

    return minValue;
}