#include <bits/stdc++.h>
#include "testlib.h"

using namespace std;

#define SL_MAX ((1<<13)-1)
#define XY_MAX ((1<<16)-1)

typedef std::pair<int, int> Point;

bool has3collinear(set<Point> points);
bool collinear3(Point const & p1, Point const & p2, Point const & p3);


int main(int argc, char *argv[]) {
    registerValidation(argc, argv);

    const int loopSize = inf.readInt(3, SL_MAX, "s"); inf.readSpace();
    const int loopCount = inf.readInt(1, SL_MAX, "l"); inf.readEoln();
    const int ppCount = loopSize * loopCount; // Number of power-points on the grid
    ensuref(ppCount < SL_MAX, "Condition s*l < 8192 is not met: %d*%d = %d >= 8192", loopSize, loopCount, ppCount);

    set<Point> powerpoints;
    for (int i = 0; i < ppCount; ++i) {
        int const x = inf.readInt(0, XY_MAX, "x"); inf.readSpace();
        int const y = inf.readInt(0, XY_MAX, "y"); inf.readEoln();
        ensuref(powerpoints.insert({x,y}).second, "Multiple power-points at location (%d, %d)", x, y);
    }
    inf.readEof();
    ensuref(!has3collinear(powerpoints), "Condition violated: No three power-points lie in a straight line.");
    return 0;
}


bool has3collinear(set<Point> points) {
    for (auto i = points.begin(); i != points.end(); ++i) {
        for (auto j = next(i); j != points.end(); ++j) {
            for (auto k = next(j); k != points.end(); ++k) {
                if (collinear3(*i, *j, *k)) return true;
            }
        }
    }
    return false;
}

bool collinear3(Point const & p1, Point const & p2, Point const & p3) {
    return (long long)(p2.second-p1.second)*(p3.first-p2.first) == (long long)(p2.first-p1.first)*(p3.second-p2.second);
}
