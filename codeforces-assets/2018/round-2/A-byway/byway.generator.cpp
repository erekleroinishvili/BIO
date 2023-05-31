#include <bits/stdc++.h>
#include "testlib.h"

/*
Optional Command-line Parameters:
   - Max number of villages or hyphen for default
   - Max time: maximum time required to travel between any two villages. Hyphen for default maximum
   - Max Loop edges: maximum number of edges to add after the tree of villages is built

If no parameters are specified, the defaults will be assumed
*/

using namespace std;

#define V_MAX (1<<12)
#define T_MAX (1LL<<50)

int main(int argc, char *argv[]) {
    registerGen(argc, argv, 1);

    const int v = argc > 1 && (strcmp(argv[1], "-")) // If first parameter exists and is not a hyphen, then it is max number of villages
        ? rnd.next(2, min(V_MAX, atoi(argv[1]))) // Limit number of villages to the argument
        : rnd.next(2, V_MAX);

    const long long maxTime = argc > 2 && (strcmp(argv[2], "-")) // If second parameter exists and is not a hyphen, it is max travel time between any two villages
        ? max(2LL, min(T_MAX, atoll(argv[2]))) // Tube number can be from 0 to its maximum
        : T_MAX; // Tube number can be from 0 to its maximum

    const int loopEdges = argc > 3 && strcmp(argv[3], "-") // If second parameter exists and is not a hyphen, it is loop edges
        ? atoi(argv[3]) // Exact number of extra edges was provided
        : rnd.next(0, v); // Some random number of extra edges, but not too many

    vector<set<int>> child(v);
    for (int i = 1; i < v; ++i) child[rnd.next(i)].insert(i); // First, build a tree

    // Try adding extra edges
    for (int e = 0; e < loopEdges; ++e) {
        int from = rnd.next(v);
        int to = rnd.next(v);
        if ( from == to ) to = (to + 1) % v; // No self loops
        if ( from > to ) swap(from, to);
        if ( child[from].find(to) == child[from].end() ) child[from].insert(to);
    }

    vector<pair<int, int>> byway; // Convert all byways into a vector for shuffling
    for (int from = 0; from < v; ++from) {
        for (int to : child[from]) {
            rnd.next(1) ? byway.emplace_back(from, to) : byway.emplace_back(to, from);
        }
    }

    shuffle(byway.begin(), byway.end());
    // Emit output
    cout << v << endl;
    long long const halfTime = maxTime >> 1;
    for (auto [from, to] : byway) {
        cout << (1+from) << ' ' << (1+to) << ' ' << (rnd.next(1LL, halfTime)<<1) << endl;
    }

    cout << "-1 -1 -1" << endl; // End of input data

}
