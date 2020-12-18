#include <vector>
#include <string>
#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <fstream>
#include <sstream>

using namespace std;


vector<unordered_map<string, string>> getVectorVector(string file) {
    vector<unordered_map<string, string>> v;
    fstream newfile;
    newfile.open(file, ios::in);
    if (newfile.is_open()) {
        string tp;
        unordered_map<string, string> current;
        while (getline(newfile, tp)) {
            if (tp.length() == 0) {
                v.push_back(current);
                current = {};
            } else {
                stringstream ss(tp);
                while (ss >> tp) {
                    current[tp.substr(0, 3)] = tp.substr(4);
                }
            }
        }
        v.push_back(current);
    }
    return v;
}

int validPassports(vector<unordered_map<string, string>> v) {
    int total = 0;
    for (unordered_map<string, string> v2 : v) {
        if (v2.size() == 8 || (v2.size() == 7 && v2.count("cid") == 0)) {
            total++;
        }
    }
    return total;
}

int validPassports2(vector<unordered_map<string, string>> v) {
    int total = 0;
    for (unordered_map<string, string> v2 : v) {
        if (v2.size() == 8 || (v2.size() == 7 && v2.count("cid") == 0)) {
            try {
                if (v2.count("byr") == 0 || stoi(v2["byr"]) < 1920 || stoi(v2["byr"]) > 2002) {
                    continue;
                }

                if (v2.count("iyr") == 0 || stoi(v2["iyr"]) < 2010 || stoi(v2["iyr"]) > 2020) {
                    continue;
                }

                if (v2.count("eyr") == 0 || stoi(v2["eyr"]) < 2020 || stoi(v2["eyr"]) > 2030) {
                    continue;
                }

                if (v2.count("hgt") == 0) {
                    continue;
                }

                string height = v2["hgt"];
                string cmin = height.substr(height.length() - 2);
                int h = stoi(height.erase(height.length() - 2, 2));
                if (cmin.compare("cm") != 0 && cmin.compare("in") != 0) {
                    continue;
                }

                if (cmin.compare("cm") == 0 && (h < 150 || h > 193)) {
                    continue;
                }

                if (cmin.compare("in") == 0 && (h < 59 || h > 76)) {
                    continue;
                }

                if (v2.count("hcl") == 0 || v2["hcl"][0] != '#') {
                    continue;
                }
                
                string hair = v2["hcl"].substr(1);
                if (hair.length() != 6 || !(all_of(hair.begin(), hair.end(), ::isxdigit))) {
                    continue;
                }

                vector<string> ecl {"amb", "blu", "brn", "gry", "grn", "hzl", "oth"};
                if (v2.count("ecl") == 0 || find(ecl.begin(), ecl.end(), v2["ecl"]) == ecl.end()) {
                    continue;
                }

                if (v2.count("pid") == 0 || stoi(v2["pid"]) < 0 || v2["pid"].length() != 9) {
                    continue;
                }
                
                total++;
            }
            catch (...) {
                continue;
            }
            
        }
    }
    return total;
}