#include <vector>
#include <string>
#include <iostream>
#include <cmath>

using namespace std;

int getDistance(vector<string> input) {
    int n = 0;
    int e = 0;
    int d = 90;
    for (string s : input) {
        int val = stoi(s.substr(1));
        if (s[0] == 'N') {
            n += val;
        } else if (s[0] == 'S') {
            n -= val;
        } else if (s[0] == 'E') {
            e += val;
        } else if (s[0] == 'W') {
            e -= val;
        } else if (s[0] == 'L') {
            d -= val;
        } else if (s[0] == 'R') {
            d += val;
        } else {
            d = d % 360;
            if (d < 0) {
                d += 360;
            }
            if (d == 0) {
                n += val;
            } else if (d == 90) {
                e += val;
            } else if (d == 180) {
                n -= val;
            } else {
                e -= val;
            }
        }
    }
    return abs(n) + abs(e);
}

int getDistance2(vector<string> input) {
    int wn = 1;
    int we = 10;
    int n = 0;
    int e = 0;
    for (string s : input) {
        int val = stoi(s.substr(1));
        if (s[0] == 'N') {
            wn += val;
        } else if (s[0] == 'S') {
            wn -= val;
        } else if (s[0] == 'E') {
            we += val;
        } else if (s[0] == 'W') {
            we -= val;
        } else if (s[0] == 'L') {
            val /= 90;
            for (int i = 0; i < val; i++) {
                int temp = wn;
                wn = we;
                we = 0 - temp;
            }            
        } else if (s[0] == 'R') {
            val /= 90;
            for (int i = 0; i < val; i++) {
                int temp = we;
                we = wn;
                wn = 0 - temp;
            }
        } else {
            n += val * wn;
            e += val * we;
        }
    }
    return abs(n) + abs(e);
}