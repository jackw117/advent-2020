#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
#include <sstream>

using namespace std;

vector<string> getStringFile(string file) {
    vector<string> report;
    fstream newfile;
    newfile.open(file, ios::in);
    if (newfile.is_open()) {
        string tp;
        while (getline(newfile, tp)) {
            report.push_back(tp);
        }
    }
    newfile.close();
    return report;
}

vector<int> getLowHigh(string s) {
    vector<int> v;
    string s2 = "";
    for (char ch : s) {
        if (ch != '-') {
            s2 += ch;
        } else {
            v.push_back(stoi(s2));
            s2 = "";
        }
    }
    v.push_back(stoi(s2));
    return v;
}

vector<string> getStrs(string s) {
    vector<string> strs;
    string s2 = "";
    for (char ch : s) {
        if (ch != ' ') {
            s2 += ch;
        } else {
            strs.push_back(s2);
            s2 = "";
        }
    }
    strs.push_back(s2);
    return strs;
}

int validPasswords() {
    vector<string> report = getStringFile("day2.txt");
    int total = 0;

    for (string s : report) {
        vector<string> strs = getStrs(s);
        char check = strs[1][0];
        int count = 0;

        for (char ch : strs[2]) {
            if (ch == check) {
                count++;
            }
        }

        vector<int> nums = getLowHigh(strs[0]);

        if (count >= nums[0] && count <= nums[1]) {
            total++;
        }
    }
    return total;
}

int validPasswords2() {
    vector<string> report = getStringFile("day2.txt");
    int total = 0;

    for (string s : report) {
        vector<string> strs = getStrs(s);
        string pass = strs[2];
        char check = strs[1][0];
        vector<int> nums = getLowHigh(strs[0]);
        int low = nums[0];
        int high = nums[1];
        if (pass[low - 1] == check && pass[high - 1] != check) {
            total++;
        } else if (pass[low - 1] != check && pass[high - 1] == check) {
            total++;
        }
    }
    return total;
}