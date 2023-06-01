#include <bits/stdc++.h>
#include "testlib.h"

/*
Optional Command-line Parameter:
   - Number of films

If no parameters are specified, random number will be used
*/

using namespace std;

#define N_MAX (1<<10)

pair<int, int> randomOrderPair(int a, int b) {
    return rnd.next(0,1) ? make_pair(a, b) : make_pair(b, a);
}

int main(int argc, char *argv[]) {
    registerGen(argc, argv, 1);

    const int n = argc > 1 && (strcmp(argv[1], "-"))
        ? max(1, min(N_MAX, atoi(argv[1])))
        : rnd.next(1, N_MAX);

    vector<pair<int, int>> preference;
    for (int i = 1; i < n; ++i) {
        for (int j = i + 1; j <= n; ++j) {
            preference.push_back(randomOrderPair(i, j));
        }
    }

    shuffle(preference.begin(), preference.end());

    cout << n << endl;
    for (auto [a, b] : preference) cout << a << ' ' << b << endl;

}
