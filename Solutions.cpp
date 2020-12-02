#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_set>

#include "day1.cpp"

using namespace std;

int main() {
    int d1p1 = multiply2020();
    int d1p2 = multiply2020_3();
    cout << d1p1 << endl;
    cout << d1p2 << endl;
    return 0;
}