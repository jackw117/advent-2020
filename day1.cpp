#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_set>

using namespace std;

// day 1 read file
vector<int> getIntFile(string file) {
    vector<int> report;
    fstream newfile;
    newfile.open(file, ios::in);
    if (newfile.is_open()) {
        string tp;
        while (getline(newfile, tp)) {
            report.push_back(stoi(tp));
        }
    }
    newfile.close();
    return report;
}

// day 1 search
int search(int start, vector<int> report, int third) {
    int sum;
    int end = report.size() - 1;
    
    while (start < end) {
        sum = report[start] + report[end] + third;
        if (sum == 2020) {
            return third == 0 ? report[start] * report[end] : report[start] * report[end] * third;
        } else if (sum < 2020) {
            start++;
        } else {
            end--;
        }
    }
    return 0;
}

// day 1 part 1
int multiply2020() {
    vector<int> report = getIntFile("day1.txt");
    sort(report.begin(), report.end());

    int mult = search(0, report, 0);
    return mult;
}

// day 1 part 2
int multiply2020_3() {
    vector<int> report = getIntFile("day1.txt");
    sort(report.begin(), report.end());
    
    for (int i = 0; i < report.size(); i++) {
        int mult = search(i + 1, report, report[i]);
        if (mult != 0) {
            return mult;
        }
    }
    return 0;
}