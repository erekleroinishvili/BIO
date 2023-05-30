#include <bits/stdc++.h>
#include "testlib.h"

using namespace std;

#define N_MAX (1<<20)

int main(int argc, char *argv[]) {
    registerValidation(argc, argv);

    int c = inf.readInt(1, N_MAX, "c"); inf.readEoln();
    int n = (1 << c);
    vector<bool> seen(n, false);
    int seenCount = 0;
    for (int d = 0; d < n; ++d) {
        string combination = inf.readString("[undp]{" + to_string(c) + "}", "combination");
        int z = 0;
        for (int bit = 0; bit < c; ++bit) {
            const bool up = combination[bit] == 'u' || combination[bit] == 'n';
            z = (z<<1) + up;
        }
        ensuref(! seen[z], "Combination %d (on line %d) is not unique", 1 + d, 2 + d);
        seen[z] = true; ++seenCount;
    }

    inf.readEof();
    return 0;

}
