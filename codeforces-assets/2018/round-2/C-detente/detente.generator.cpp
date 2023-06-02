#include <bits/stdc++.h>
#include "testlib.h"

/*
Optional Command-line Parameter:
   - Number of desks

If no parameters are specified, random number will be used
*/

using namespace std;

#define N_MAX ((1<<13)-1)
#define XY_MAX ((1<<16)-1)

int main(int argc, char *argv[]) {
    registerGen(argc, argv, 1);

    int n = argc > 1 && (strcmp(argv[1], "-"))
        ? max(1, min(N_MAX, atoi(argv[1])))
        : rnd.next(1, N_MAX);

    int xyMax = argc > 2 && (strcmp(argv[2], "-"))
        ? max(0, min(XY_MAX, atoi(argv[2])))
        : rnd.next(1, XY_MAX);
    while ((xyMax+1) * (xyMax+1) < n) ++xyMax;

    set<pair<int,int>> desks;
    for (int d = 0; d < n; ++d) {
        int x0 = rnd.next(0, xyMax);
        int y0 = rnd.next(0, xyMax);
        int x,y;
        bool xFirst, yFirst, uniqueFound = false;
        for (x = x0, xFirst = true; xFirst || x != x0; x = (x + 1) % (xyMax+1), xFirst = false) {
            for (y = y0, yFirst = true; yFirst || y != y0; y = (y + 1) % (xyMax+1), yFirst = false) {
                uniqueFound = desks.find({x,y}) == desks.end();
                if (uniqueFound) break;
            }
            if (uniqueFound) break;
        }
        ensuref(uniqueFound, "Could not find possible coordinates for the next desk");
        desks.emplace(x,y);
    }

    vector<pair<int, int>> d{desks.begin(), desks.end()};
    shuffle(d.begin(), d.end());

    cout << n << endl;

    for (auto [x, y] : d) cout << x << ' ' << y << endl;

}
