#include <vector>
#include <string>

using namespace std;

int numTrees(vector<string> &input, int d, int r) {
    int width = input[0].size();
    int total = 0;
    int right = r;
    int down = d;
    while (d < input.size()) {
        if (input[d][r] == '#') {
            total++;
        }
        d += down;
        r = (r + right) % width;
    }
    return total;
}