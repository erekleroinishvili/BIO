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

int main(int argc, char *argv[]) {
    registerGen(argc, argv, 1);

    const int h = argc > 1 && (strcmp(argv[1], "-")) // If first parameter exists and is not a hyphen, then it is max number of houses
        ? rnd.next(2, min(H_MAX, atoi(argv[1]))) // Limit number of houses to the argument
        : rnd.next(2, H_MAX);

    cout << h << endl;

    const int tubeCount = argc > 2 && (strcmp(argv[2], "-")) // If second parameter exists and is not a hyphen, it is max number of tubes
        ? rnd.next(0, min(1 + 3 * (h-1) / 2, atoi(argv[2]))) // Tube number can be from 0 to its maximum
        : rnd.next(0, 1 + 3 * (h-1) / 2); // Tube number can be from 0 to its maximum


    // pair<index, resource> Resource is the number of tubes this house can still connect
    vector<pair<int, int>> node(h); // h houses
    node[0] = {1, 2}; //  First house can connect two tubes
    for (int i = 1; i < h; ++i) node[i] = {1 + i, 3}; // All other houses can connect three tubes

    for (int tube = 1; tube <= tubeCount; ++tube) {
        if ( node.size() < 2 ) break; // At least two nodes must exist.
        int t1 = rnd.next((int)node.size() - 0); // First candidate chosen freely
        int t2 = rnd.next((int)node.size() - 1); // Second candidate chosen with a leeway to avoid collision
        if ( t1 == t2 ) ++t2; // If both candidates are same, change second candidate
        if ( node[t1].first > node[t2].first ) swap(t1, t2); // Ensure the house numbers are increasing from t1 to t2
        cout << node[t1].first << ' ' << node[t2].first << endl;
        if ( --node[t2].second <= 0 ) node.erase(node.begin() + t2);
        if ( --node[t1].second <= 0 ) node.erase(node.begin() + t1);
    }

    cout << "-1 -1" << endl; // End of input data

}
