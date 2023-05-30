#include <bits/stdc++.h>
#include "testlib.h"

/*
Optional parameter: max number of cast members.

If parameter is omitted, the defaults maximum will be assumed.
*/

using namespace std;

#define C_MAX (20)

int main(int argc, char *argv[]) {
    registerGen(argc, argv, 1);

    // Generate n, m, c
    const int c = argc > 1 && (strcmp(argv[1], "-")) // If first parameter exists and is not a hyphen, then it is max number of cast members
        ? rnd.next(1, min(C_MAX, atoi(argv[1]))) // Limit number of cast members
        : rnd.next(1, C_MAX);

    cout << c << endl;

    for (int d = (1 << c) - 1; d >= 0; --d) {
        for (int bit = c, n = d; bit >= 1; --bit, n = n >> 1) {

            if (n & 1) { // Hat is up
                cout << rnd.next("u|n"); // Randomly face front or back
            } else { // Hat is down
                cout << rnd.next("d|p"); // Randomly face front or back
            }
        }
        cout << endl;
    }

    return 0;

}
