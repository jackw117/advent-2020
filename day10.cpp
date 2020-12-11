#include <vector>
#include <algorithm>
#include <iostream>
#include <unordered_set>
#include <unordered_map>

using namespace std;

unordered_map<int, unsigned long long int> dp;

/*
    Takes a vector of ints as input and builds a chain of all the elements so that everything
    is at most 3 away from the previous element (starting at 0).
    Returns the number of 1-difference elements multiplied the number of 3-diffrence elements.
*/
int multiplyAdapters(vector<int> input) {
    int mult;
    sort(input.begin(), input.end());
    int current = 0;
    int one = 0;
    int three = 0;
    for (int i : input) {
        if (i - current == 1) {
            one++;
        } else if (i - current == 3) {
            three++;
        }
        current = i;
    }
    return one * (three + 1);
}

/*
    Recursive helper function to find the number of unique combinations of elements.
*/
unsigned long long int helper(int i, vector<int> input) {
    if (i == input.size() - 1) {
        return 1;
    }
    if (dp.count(i)) {
        return dp[i];
    }
    unsigned long long int total = 0;
    for (int j = i+1; j < input.size(); j++) {
        if (input[j] - input[i] <= 3) {
            total += helper(j, input);
        }
    }
    dp[i] = total;
    return total;
}

/*
    Finds the number of unique combinations of elements so that each element is at most 3 away from the previous one
*/
unsigned long long int findCombos(vector<int> input) {
    input.push_back(0);
    sort(input.begin(), input.end());
    input.push_back(input[input.size() - 1] + 3);
    return helper(0, input);
}

