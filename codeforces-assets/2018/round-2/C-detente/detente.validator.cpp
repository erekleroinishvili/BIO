#include <bits/stdc++.h>
#include "testlib.h"

using namespace std;

#define N_MAX ((1<<13)-1)
#define XY_MAX ((1<<16)-1)

int main(int argc, char *argv[]) {
    registerValidation(argc, argv);

    const int deskCount = inf.readInt(1, N_MAX, "n"); inf.readEoln();

    set<pair<int, int>> desks;
    for (int i = 0; i < deskCount; ++i) {
        int const x = inf.readInt(0, XY_MAX, "n"); inf.readSpace();
        int const y = inf.readInt(0, XY_MAX, "n"); inf.readEoln();
        ensuref(desks.insert({x,y}).second, "Desks overlap at position (%d, %d)", x, y);
    }
    inf.readEof();
    return 0;
}
