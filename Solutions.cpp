#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_set>

#include "day3.cpp"

using namespace std;

vector<string> getInputVector(string file) {
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

int main() {
    vector<string> input = getInputVector("day3.txt");
    int d3p1 = numTrees(input, 1, 3);
    long d3p2 = 1;
    vector<vector<int>> pairs {vector<int>{1,1}, vector<int>{1,3}, vector<int>{1,5}, vector<int>{1,7}, vector<int>{2,1}};
    for (int i = 0; i < pairs.size(); i++) {
        d3p2 *= numTrees(input, pairs[i][0], pairs[i][1]);
    }
    cout << d3p1 << endl;
    cout << d3p2 << endl;
    return 0;
}