#include <bits/stdc++.h>
#include "testlib.h"

/*
Up to 2 Command-line Parameters:
   1: Max number of seats or hyphen for default
   2. Max number of cutlery choices or hyphen for default

If parameters are omitted, the defaults will be assumed
*/

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

    cout << n << ' ' << m << endl;

    // Generate initial cutlery choices
    for (int row = 1; row <= 2; ++row) {
        for (int seat = 1; seat <= n; ++seat) {
            if (seat > 1) cout << ' ';
            cout << rnd.next(1, m);
        }
        cout << endl;
    }

    cout << endl;

}
