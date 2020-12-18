#include <vector>
#include <unordered_set>
#include <algorithm>
#include <queue>
#include <climits>

using namespace std;

/*
    Takes a vector of doubles as input, and finds the one number that is not a multiple of any of the previous 25 elements.
    Returns that number.
*/
double findError(vector<double> input) {
    int pre = 25;
    vector<double> v;
    // build initial vector of every possible sum of the first 25 elements
    for (int i = 0; i < pre; i++) {
        for (int j = 0; j < pre; j++) {
            if (i != j) {
                v.push_back(input[i] + input[j]);
            }
        }
    }
    // loop through the rest of the input
    for (int i = pre; i < input.size(); i++) {
        // returns if the current number in the loop is not in the sums vector
        if (find(v.begin(), v.end(), input[i]) == v.end()) {
            return input[i];
        } else {
            //remove the sums associated with the i - 25th element
            v = vector<double> (v.begin() + pre - 1, v.end());
            //add the new sums
            for (int j = i - pre + 1; j < i; j++) {
                v.push_back(input[i] + input[j]);
            }
        }
    }
    return 0;
}

/*
    Takes a vector of doubles and the number that is not a multiple of the previous 25 elements as input.
    Returns the sum of the largest and smallest values in the contiguous list that adds up to this number.
*/
double findWeakness(vector<double> input, double w) {
    int l = 0;
    int r = 1;
    // queue to keep track of the current numbers being considered in the sum
    queue<double> q;
    q.push(input[l]);
    double sum = input[l];
    while (r < input.size()) {
        if (sum == w) {
            break;
        }
        else if (sum < w) {
            sum += input[r];
            q.push(input[r]);
            r++;
        } else {
            sum -= q.front();
            q.pop();
            l++;
        }
    }
    // find the largest and smallest elements in the queue
    double dmin = LONG_MAX;
    double dmax = LONG_MIN;
    while (!q.empty()) {
        dmin = min(dmin, q.front());
        dmax = max(dmax, q.front());
        q.pop();
    }
    return dmin + dmax;
}