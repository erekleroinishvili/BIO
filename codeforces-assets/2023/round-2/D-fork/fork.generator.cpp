#include <bits/stdc++.h>
#include "testlib.h"

/*
Up to 3 Command-line Parameters:
   1: Max number of seats or hyphen for default
   2. Max number of cutlery choices or hyphen for default
   3. Max number of mind change steps or hyphen for default

If parameters are omitted, the defaults will be assumed
*/

// In all tests, change of mind will be to a different cutlery.

using namespace std;

#define N_MAX (1<<20)

int main(int argc, char *argv[]) {
    registerGen(argc, argv, 1);

    // Generate n, m, c
    const int n = argc > 1 && (strcmp(argv[1], "-")) // If first parameter exists and is not a hyphen, then it is max number of seats per side
        ? rnd.next(1, min(N_MAX, atoi(argv[1]))) // Limit number of seats per side to the argument
        : rnd.next(1, N_MAX);
    const int m = argc > 2 && (strcmp(argv[2], "-")) // If second parameter exists and is not a hyphen, it is max number of cutlery items
        ? rnd.next(2, min(2*n, atoi(argv[2])))
        : rnd.next(2, 2*n);
    const int c = argc > 3 && (strcmp(argv[3], "-")) // If third parameter exists and is not a hyphen, it is max number the first spy changed mind
        ? rnd.next(1, min(N_MAX, atoi(argv[3])))
        : rnd.next(1, N_MAX);

    cout << n << ' ' << m << ' ' << c << endl;

    int firstChoice = 0; // Initial cutlery choice by the first spy in the first row - the trendsetter

    // Generate initial cutlery choices
    for (int row = 1; row <= 2; ++row) {
        for (int seat = 1; seat <= n; ++seat) {
            if (seat > 1) cout << ' ';
            const int initialChoice = rnd.next(1, m);
            cout << initialChoice;
            if ( row == 1 && seat == 1 ) firstChoice = initialChoice;
        }
        cout << endl;
    }

    // Generate change of minds by the first spy
    for (int change = 1, lastChoice = firstChoice; change <= c; ++change) {
            int nextChoice = rnd.next(1, m);
            if (lastChoice == nextChoice) nextChoice = nextChoice > 1 ? nextChoice - 1 : 2;
            cout << (change > 1 ? " " : "") << nextChoice;
            lastChoice = nextChoice;
        }
    cout << endl;

}
