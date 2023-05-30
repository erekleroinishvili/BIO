#include <bits/stdc++.h>
#include "testlib.h"

// This validator does not allow changing mind to the same cutlery, e.g. from 3 to 3

using namespace std;

#define N_MAX (1<<20)

int main(int argc, char *argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, N_MAX, "n"); inf.readSpace();
    int m = inf.readInt(1, 2*n, "m"); inf.readSpace();
    int c = inf.readInt(1, N_MAX, "c"); inf.readEoln();

    int firstChoice = 0; // Initial cutlery choice by the first spy in the first row - the trendsetter

    for (int row = 1; row <= 2; ++row) {
        for (int seat = 1; seat <= n; ++seat) {
            if (seat > 1) inf.readSpace();

            row == 1 && seat == 1
                ? firstChoice = inf.readInt(1, m, "initial cutlery choice")
                : inf.readInt(1, m, "initial cutlery choice");
        }
        inf.readEoln();
    }

    for (int change = 1, lastChoice = firstChoice; change <= c; ++change) {
        if (change > 1) inf.readSpace();
        int newChoice = inf.readInt(1, m, "change of mind");
        ensuref(newChoice != lastChoice, "Change of mind cannot happen from %d to %d", lastChoice, newChoice);
        lastChoice=newChoice;
    }
    inf.readEoln();

    inf.readEof();
}
