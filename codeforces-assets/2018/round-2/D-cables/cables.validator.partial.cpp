#include <bits/stdc++.h>
#include "testlib.h"

using namespace std;

#define SL_MAX ((1<<13)-1)
#define XY_MAX ((1<<16)-1)

int main(int argc, char *argv[]) {
    registerValidation(argc, argv);

    const int loopSize = inf.readInt(3, SL_MAX, "s"); inf.readSpace();
    const int loopCount = inf.readInt(1, SL_MAX, "l"); inf.readEoln();
    const int ppCount = loopSize * loopCount; // Number of power-points on the grid
    ensuref(ppCount < SL_MAX, "Condition s*l < 8192 is not met: %d*%d = %d >= 8192", loopSize, loopCount, ppCount);

    set<pair<int, int>> powerpoints;
    for (int i = 0; i < ppCount; ++i) {
        int const x = inf.readInt(0, XY_MAX, "x"); inf.readSpace();
        int const y = inf.readInt(0, XY_MAX, "y"); inf.readEoln();
        ensuref(powerpoints.insert({x,y}).second, "Multiple power-points at location (%d, %d)", x, y);
    }
    inf.readEof();
    return 0;
}
