#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>

using namespace std;

/*
    Counts the unique number of characters in each "group" as represented by the inner vectors of the input.
    Returns the sum of these counts from each of these groups.
*/
int countUnique(vector<vector<string>> input) {
    int total = 0;
    for (vector<string> v : input) {
        unordered_set<char> unique;
        for (string s : v) {
            for (char ch : s) {
                unique.insert(ch);
            }
        }
        total += unique.size();
    }
    return total;
}

/*
    Counts the characters in each vector that appear in every string of that vector.
    Returns the sum of all these counts.
*/
int countAllYes(vector<vector<string>> input) {
    int total = 0;
    for (vector<string> v : input) {
        if (v.size() == 1) {
            total += v[0].length();
        } else {
            unordered_map<char, int> unique;
            for (string s : v) {
                for (char ch : s) {
                    unique[ch]++;
                }
            }
            for (auto a : unique) {
                if (a.second == v.size()) {
                    total++;
                }
            }
        }
    }
    return total;
}