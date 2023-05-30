#include <bits/stdc++.h>
#include "testlib.h"

using namespace std;

#define N_MAX (1<<20)

int main(int argc, char *argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, N_MAX, "n"); inf.readSpace();
    int m = inf.readInt(1, 2*n, "m"); inf.readEoln();

    for (int row = 1; row <= 2; ++row) {
        for (int seat = 1; seat <= n; ++seat) {
            if (seat > 1) inf.readSpace();
            inf.readInt(1, m, "initial cutlery choice");
        }
        inf.readEoln();
    }

    inf.readEof();
}
