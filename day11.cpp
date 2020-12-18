#include <vector>
#include <string>
#include <iostream>

using namespace std;

const char occ = 'o';
const char emp = 'e';

/*
    Checks all 8 sides of a given index in a 2D vector and returns the number of occupied spaces.
*/
int checkSides(vector<string> input, int i, int j) {
    int total = 0;
    if (i > 0) {
        if (j > 0 && (input[i-1][j-1] == '#' || input[i-1][j-1] == emp)) {
            total++;
        }
        if (input[i-1][j] == '#' || input[i-1][j] == emp) {
            total++;
        }
        if (j < input[i].length() - 1 && (input[i-1][j+1] == '#' || input[i-1][j+1] == emp)) {
            total++;
        }
    }
    if (j > 0 && (input[i][j-1] == '#' || input[i][j-1] == emp)) {
        total++;
    }
    if (j < input[i].length() - 1 && (input[i][j+1] == '#' || input[i][j+1] == emp)) {
        total++;
    }
    if (i < input.size() - 1) {
        if (j > 0 && (input[i+1][j-1] == '#' || input[i+1][j-1] == emp)) {
            total++;
        }
        if (input[i+1][j] == '#' || input[i+1][j] == emp) {
            total++;
        }
        if (j < input[i].length() - 1 && (input[i+1][j+1] == '#' || input[i+1][j+1] == emp)) {
            total++;
        }
    }
    return total;
}

/*
    Checks all 8 directions of a given index in a 2D vector and returns the number of occupied spaces
    determined by the first non '.' seat it can see in each direction.
*/
int checkSides2(vector<string> input, int i, int j) {
    int total = 0;
    int tempI = i;
    int tempJ = j;
    //top left
    while (--tempJ >= 0 && --tempI >= 0) {
        if (input[tempI][tempJ] == '#' || input[tempI][tempJ] == emp) {
            total++;
            break;
        } else if (input[tempI][tempJ] == 'L') {
            break;
        }
    }

    tempI = i;
    tempJ = j;
    //top
    while (--tempI >= 0) {
        if (input[tempI][j] == '#' || input[tempI][j] == emp) {
            total++;
            break;
        } else if (input[tempI][tempJ] == 'L') {
            break;
        }
    }

    tempI = i;
    //top right
    while (++tempJ < input[i].length() && --tempI >= 0) {
        if (input[tempI][tempJ] == '#' || input[tempI][tempJ] == emp) {
            total++;
            break;
        } else if (input[tempI][tempJ] == 'L') {
            break;
        }
    }

    tempI = i;
    tempJ = j;
    //left
    while (--tempJ >= 0) {
        if (input[tempI][tempJ] == '#' || input[tempI][tempJ] == emp) {
            total++;
            break;
        } else if (input[tempI][tempJ] == 'L') {
            break;
        }
    }

    tempJ = j;
    //right
    while (++tempJ < input[i].length()) {
        if (input[tempI][tempJ] == '#' || input[tempI][tempJ] == emp) {
            total++;
            break;
        } else if (input[tempI][tempJ] == 'L') {
            break;
        }
    }

    tempJ = j;
    //bottom left
    while (--tempJ >= 0 && ++tempI < input.size()) {
        if (input[tempI][tempJ] == '#' || input[tempI][tempJ] == emp) {
            total++;
            break;
        } else if (input[tempI][tempJ] == 'L') {
            break;
        }
    }

    tempJ = j;
    tempI = i;
    //bottom
    while (++tempI < input.size()) {
        if (input[tempI][j] == '#' || input[tempI][j] == emp) {
            total++;
            break;
        } else if (input[tempI][tempJ] == 'L') {
            break;
        }
    }

    tempI = i;
    //bottom right
    while (++tempJ < input[i].length() && ++tempI < input.size()) {
        if (input[tempI][tempJ] == '#' || input[tempI][tempJ] == emp) {
            total++;
            break;
        } else if (input[tempI][tempJ] == 'L') {
            break;
        }
    }
    return total;
}

/*
    Takes an input of "seats" as input with "#" representing occupied, "L" representing open, and "." representing the floor.
    Simulates plane boarding where people sit/move depending on the surrounding seats.
    Returns the total number of occupied seats after no more seats are changed.
*/
int findOccupied(vector<string> input) {
    int total = 0;
    int current = -1;
    while (current != 0) {
        current = 0;
        total = 0;
        // sets seats to be changed to a temporary value
        for (int i = 0; i < input.size(); i++) {
            for (int j = 0; j < input[i].length(); j++) {
                if (input[i][j] == '.') {
                    continue;
                }
                int sides = checkSides(input, i, j);
                if (input[i][j] == 'L' && sides == 0) {
                    input[i][j] = occ;
                } else if (input[i][j] == '#' && sides >= 4) {
                    input[i][j] = emp;
                }
            }
        }

        // changes seats
        for (int i = 0; i < input.size(); i++) {
            for (int j = 0; j < input[i].length(); j++) {
                if (input[i][j] == occ) {
                    current++;
                    input[i][j] = '#';
                    total++;
                } else if (input[i][j] == emp) {
                    current++;
                    input[i][j] = 'L';
                } else if (input[i][j] == '#') {
                    total++;
                }
            }
        }
    }
    return total;
}

/*
    Similar to the above function, but searches in the 8 directions, instead of just the adjacent 8 seats.
*/
int findOccupied2(vector<string> input) {
    int total = 0;
    int current = -1;
    while (current != 0) {
        current = 0;
        total = 0;
        for (int i = 0; i < input.size(); i++) {
            for (int j = 0; j < input[i].length(); j++) {
                if (input[i][j] == '.') {
                    continue;
                }
                int sides = checkSides2(input, i, j);
                if (input[i][j] == 'L' && sides == 0) {
                    input[i][j] = occ;
                } else if (input[i][j] == '#' && sides >= 5) {
                    input[i][j] = emp;
                }
            }
        }

        for (int i = 0; i < input.size(); i++) {
            for (int j = 0; j < input[i].length(); j++) {
                if (input[i][j] == occ) {
                    current++;
                    input[i][j] = '#';
                    total++;
                } else if (input[i][j] == emp) {
                    current++;
                    input[i][j] = 'L';
                } else if (input[i][j] == '#') {
                    total++;
                }
            }
        }
    }
    return total;
}