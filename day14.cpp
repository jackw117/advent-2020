#include <vector>
#include <string>
#include <unordered_map>
#include <iostream>
#include <bitset>
#include <unordered_set>

using namespace std;

// addresses to be used in part 2
unordered_set<unsigned long long int> addresses;

/*
    Finds the key (memory address) and value represented in binary from a given string.
*/
pair<string, string> getKeyVal(string s) {
    // find the key and values from the string
    int i;
    bool start = false;
    string key = "";
    for (i = 0; i < s.length(); i++) {
        if (s[i] == ']') {
            start = false;
        } else if (start) {
            key += s[i];
        } else if (s[i] == '[') {
            start = true;
        } else if (s[i] == '=') {
            break;
        }
    }
    // convert value to binary
    string val = bitset<36>(stoi(s.substr(++i))).to_string();
    return make_pair(key, val);
}

/*
    Applies the mask to the binary value string.
*/
string applyMask(string mask, string val, char unchange) {
    // apply mask to the value
    for (int j = 0; j < mask.length(); j++) {
        if (mask[j] != unchange) {
            val[j] = mask[j];
        }
    }
    return val;
}

/*
    Recursive function to calculate all the addresses to be updated from the "floating" bit addresses.
*/
void convertFloating(string address) {
    int i;
    for (i = 0; i < address.length(); i++) {
        if (address[i] == 'X') {
            address[i] = '0';
            convertFloating(address);
            address[i] = '1';
            convertFloating(address);
        }
    }
    // base case
    if (i == address.length()) {
        addresses.insert(stoull(address, nullptr, 2));
    }
}

unsigned long long int memSum(vector<string> input) {
    string mask;
    unordered_map<int, unsigned long long int> m;
    for (string s : input) {
        if (s.substr(0, 4).compare("mask") == 0) {
            mask = s.substr(7);
        } else {
            //get the key and value from the current string
            pair<string, string> keyVal = getKeyVal(s);

            //apply the mask to the value
            keyVal.second = applyMask(mask, keyVal.second, 'X');

            // convert binary to int and store in map
            m[stoi(keyVal.first)] = stoull(keyVal.second, nullptr, 2);
        }
    }

    // find the sum of all the values in the map
    unsigned long long int sum = 0;
    for (auto a : m) {
        sum += a.second;
    }
    
    return sum;
}

unsigned long long int memSum2(vector<string> input) {
    string mask;
    unordered_map<unsigned long long int, unsigned long long int> m;
    for (string s : input) {
        if (s.substr(0, 4).compare("mask") == 0) {
            mask = s.substr(7);
        } else {
            //reset addresses
            addresses = unordered_set<unsigned long long int>();

            //get the key and value from the current string
            pair<string, string> keyVal = getKeyVal(s);

            //convert key to binary
            keyVal.first = bitset<36>(stoi(keyVal.first)).to_string();

            //apply the mask to the key, then calculate all addresses
            keyVal.first = applyMask(mask, keyVal.first, '0');
            convertFloating(keyVal.first);

            for (unsigned long long int i : addresses) {
                // don't need the value in binary for this part, so convert back to decimal
                m[i] = stoull(keyVal.second, nullptr, 2);
            }
        }
    }
    unsigned long long int sum = 0;
    for (auto a : m) {
        sum += a.second;
    }
    
    return sum;
}