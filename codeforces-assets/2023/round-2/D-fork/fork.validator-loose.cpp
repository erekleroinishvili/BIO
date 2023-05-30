#include <bits/stdc++.h>
#include "testlib.h"

// This validator allows changing mind to the same cutlery, e.g. from 3 to 3

using namespace std;

#define N_MAX (1<<20)

int main(int argc, char *argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, N_MAX, "n"); inf.readSpace();
    int m = inf.readInt(1, 2*n, "m"); inf.readSpace();
    int c = inf.readInt(1, N_MAX, "c"); inf.readEoln();

    for (int row = 1; row <= 2; ++row) {
        for (int seat = 1; seat <= n; ++seat) {
            if (seat > 1) inf.readSpace();
            inf.readInt(1, m, "initial cutlery choice");
        }
        inf.readEoln();
    }

    for (int change = 1; change <= c; ++change) {
        if (change > 1) inf.readSpace();
        inf.readInt(1, m, "change of mind");
    }
    inf.readEoln();

    inf.readEof();
}
