#include <bits/stdc++.h>
#include "testlib.h"

using namespace std;

#define N_MAX (1<<10)

int main(int argc, char *argv[]) {
    registerValidation(argc, argv);

    const int filmCount = inf.readInt(1, N_MAX, "n"); inf.readEoln();
    const int length = filmCount*(filmCount-1)/2;
    set<pair<int, int>> comparisons;
    for (int i = 0; i < length; ++i) {
        int const a = inf.readInt(1, filmCount, "n"); inf.readSpace();
        int const b = inf.readInt(1, filmCount, "n"); inf.readEoln();
        ensuref(a!=b, "Bad input: Should not compare film to itself: %d %d", a, b);
        bool hasAB = comparisons.find({a, b}) != comparisons.end();
        bool hasBA = comparisons.find({b, a}) != comparisons.end();
        ensuref(! hasAB && ! hasBA, "Bad input: Duplicate pair %d %d", a, b);
        comparisons.emplace(a, b);
    }
    inf.readEof();
    return 0;

}
