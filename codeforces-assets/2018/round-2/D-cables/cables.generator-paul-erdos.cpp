/** https://en.wikipedia.org/wiki/No-three-in-line_problem
 *
 * No-three-in-line problem
 *
 * The no-three-in-line problem in discrete geometry asks how many points can be placed in
 * the nxn grid so that no three points lie on the same line.
 *
 * A solution of Paul Erdős, published by Roth (1951), is based on the observation that when
 * n is a prime number, the set of n grid points (i, i^2 % n), for 0<=i<n, contains no three
 * collinear points.
 */

#include <bits/stdc++.h>
#include "testlib.h"

/*
Optional Command-line Parameter:
   - s: Number of power-points on

If no parameters are specified, random number will be used
*/

using namespace std;

#define SL_MAX ((1<<13)-1)
#define XY_MAX ((1<<16)-1)

bool isPrime(int n) {
    for (int i = 2; i * i <= n; ++i) {
        if ( n % i == 0 ) return false;
    }
    return n > 1;
}

int main(int argc, char *argv[]) {
    registerGen(argc, argv, 1);

    int s = argc > 1 && (strcmp(argv[1], "-"))
        ? max(3, min(SL_MAX, atoi(argv[1])))
        : rnd.next(3, SL_MAX);

    int l = argc > 2 && (strcmp(argv[2], "-"))
        ? max(1, min((strcmp(argv[1], "-")?SL_MAX/s:SL_MAX), atoi(argv[2])))
        : rnd.next(1, SL_MAX / s);

    if ( s * l > SL_MAX ) s = rnd.next(3, (SL_MAX + 1) / l);

    ensuref(s*l<=SL_MAX, "Constraint s*x < %d is not met: %d*%d = %d >= %d", SL_MAX, s,l,s*l,SL_MAX);
    const int n = s * l;
    int p = n;
    while (!isPrime(p)) ++p; // Find prime

    // Construction based on method by Paul Erdős
    vector<pair<int, int>> point(n);
    for (int i = 0; i < n; ++i) {
        point[i] = make_pair(i, i*i % p);
    }

    shuffle(point.begin(), point.end());

    cout << s << ' ' << l << endl;
    for (auto [x, y] : point) cout << x << ' ' << y << endl;

}
