#include <bits/stdc++.h>
#include "testlib.h"

using namespace std;

#define H_MAX (1<<12)

int main(int argc, char *argv[]) {
    registerValidation(argc, argv);

    int h = inf.readInt(2, H_MAX, "h");
    inf.readEoln();

    set<pair<int, int>> tubes; // Existing tubes to make sure tube does not repeat

    vector<int> node(h); // h houses
    node[0] = 2; //  First house can connect two tubes
    for (int i = 1; i < h; ++i) node[i] = 3; // All other houses can connect three tubes

    while (true) {
        if ( node.size() < 2 ) break; // At least two nodes must exist.
        int t1 = inf.readInt(-1, h, "house"); // Tube: first house
        inf.readSpace();
        int t2 = inf.readInt(-1, h, "house"); // Tube: Second house
        inf.readEoln();
        ensuref(t1 != 0 && t2 != 0, "Invalid tube from %d to %d", t1, t2);
        if ( t1 == -1 || t2 == -1 ) {
            ensuref(t1 == t2, "Invalid tube from %d to %d", t1, t2);
            break;
        }
        ensuref(t1 != t2, "Tube loops to itself on house %d", t1);
        if ( t1 > t2 ) swap(t1, t2);
        ensuref(tubes.find({t1, t2})==tubes.end(), "Duplicate tube %d<-->%d", t1, t2);
        tubes.emplace(t1, t2);

        ensuref(--node[t1-1] >= 0, "Too many tubes connect to house %d", t1);
        ensuref(--node[t2-1] >= 0, "Too many tubes connect to house %d", t2);
    }

    inf.readEof();
}
