#include <vector>
#include <string>
#include <iostream>
#include <set>
#include <climits>

using namespace std;

int search(string s) {
    int low = 0;
    int high = 127;
    for (int i = 0; i < 7; i++) {
        if (s[i] == 'F') {
            high = (low + high) / 2;
        } else if (s[i] == 'B') {
            low = (low + high) / 2 + (low + high) % 2;
        }
    }
    int row = low;
    low = 0;
    high = 7;
    for (int i = 7; i < 10; i++) {
        if (s[i] == 'L') {
            high = (low + high) / 2;
        } else if (s[i] == 'R') {
            low = (low + high) / 2 + (low + high) % 2;
        }
    }
    int col = low;
    return row * 8 + col;
}

int highestSeatID(vector<string> input) {
    int maxID = 0;
    for (string s : input) {
        maxID = max(search(s), maxID);
    }
    return maxID;
}

int findID(vector<string> input) {
    int sum = 0;
    int minID = INT_MAX;
    int maxID = 0;
    for (string s : input) {
        int current = search(s);
        minID = min(minID, current);
        maxID = max(maxID, current);
        sum += current;
    }
    int sum2 = (maxID * (maxID + 1) / 2) - (minID * (minID - 1) / 2);
    return sum2 - sum;
}