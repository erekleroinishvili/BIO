#include <bits/stdc++.h>
#include "testlib.h"

/*
Up to 2 Command-line Parameters:
   1: Max number of houses
   2. Max number of tubes

If parameters are omitted, the maximum will be assumed
*/

using namespace std;

#define H_MAX (1<<12)

pair<int, int> orderedPairOf(int a, int b) {
    if (a<b) return {a,b};
    return {b,a};
}

int main(int argc, char *argv[]) {
    registerGen(argc, argv, 1);

    const int h = argc > 1 && (strcmp(argv[1], "-")) // If first parameter exists and is not a hyphen, then it is max number of houses
        ? rnd.next(2, min(H_MAX, atoi(argv[1]))) // Limit number of houses to the argument
        : rnd.next(2, H_MAX);

    cout << h << endl;

    const int tubeCount = argc > 2 && (strcmp(argv[2], "-")) // If second parameter exists and is not a hyphen, it is max number of tubes
        ? rnd.next(0, min(1 + 3 * (h-1) / 2, atoi(argv[2]))) // Tube number can be from 0 to its maximum
        : rnd.next(0, 1 + 3 * (h-1) / 2); // Tube number can be from 0 to its maximum

    set<pair<int, int>> tubes; // Existing tubes to make sure tube does not repeat

    vector<int> capacity(h); // For each house, how many more tubes it can still connect
    capacity[0] = 2; // First house can connect two tubes
    for (int i = 1; i < h; ++i) capacity[i] = 3; // All other houses can connect three tubes

    for (int tube = 1; tube <= tubeCount; ++tube) {
        // Choose house A
        int t1 = rnd.next(h); // Start by randomly trying a house
        for (int i = t1, first=1; first || i!=t1 ; t1=(t1+1)%h, first=0) {
            if ( capacity[t1] ) break;
        }
        assert(capacity[t1]);
        --capacity[t1];
        // Choose house B
        int t2 = rnd.next(h); // Second candidate chosen with a leeway to avoid collision
        for (int i = t2, first=1; first || i!=t2 ; t2=(t2+1)%h, first=0) {
            if ( capacity[t2] && t1!=t2 && tubes.find(orderedPairOf(t1,t2))==tubes.end() ) break;
        }
        assert(capacity[t2] && t1!=t2 && tubes.find(orderedPairOf(t1,t2))==tubes.end());
        --capacity[t2];
        tubes.insert(orderedPairOf(t1,t2)); // Remember the tube
        cout << (1+t1) << ' ' << (1+t2) << endl; // Output tube
    }
    cout << "-1 -1" << endl; // End of input data

}
