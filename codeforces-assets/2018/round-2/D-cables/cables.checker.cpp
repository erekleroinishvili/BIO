#include <bits/stdc++.h>
#include "testlib.h"

/**
 * https://codeforces.com/blog/entry/18431
 *
 * Invoked with three command-line arguments:
 *  1: input (inf) - test data filename
 *  2: output (out) - participant output filename
 *  3: answer (ans) - jury answer filename
 *
*/

using namespace std;

typedef pair<int, int> Point;

#define SL_MAX ((1<<13)-1)
#define XY_MAX ((1<<16)-1)

tuple<int, int, vector<Point>> readInput(InStream& stream);
void checkAnswer(InStream& stream, vector<Point> powerPoints, int loopSize, int loopCount);
bool intersect(pair<Point, Point> const s1, pair<Point, Point> const s2);

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    auto const [loopSize, loopCount, powerPoints] = readInput(inf);
    checkAnswer(ouf, powerPoints, loopSize, loopCount);
    // checkAnswer(ans, powerPoints, loopSize, loopCount);

    quitf(_ok, "All loops are well-formed.");

}

tuple<int, int, vector<Point>> readInput(InStream& stream) {
    const int loopSize = stream.readInt(3, SL_MAX, "s"); inf.readSpace();
    const int loopCount = stream.readInt(1, SL_MAX / loopSize, "l"); inf.readEoln();
    const int ppCount = loopSize * loopCount; // Number of power-points on the grid
    stream.ensuref(ppCount < SL_MAX, "Condition s*l < 8192 is not met: %d*%d = %d >= 8192", loopSize, loopCount, ppCount);

    set<Point> locations;
    vector<Point> powerPoints(ppCount);
    for (int i = 0; i < ppCount; ++i) {
        int const x = inf.readInt(0, XY_MAX, "x"); inf.readSpace();
        int const y = inf.readInt(0, XY_MAX, "y"); inf.readEoln();
        Point point{x,y};
        ensuref(locations.insert(point).second, "Multiple power-points at location (%d, %d)", x, y);
        powerPoints[i] = point;
    }
    inf.readEof();
    return {loopSize, loopCount, powerPoints};
}

void checkAnswer(InStream& stream, vector<Point> powerPoints, int loopSize, int loopCount) {
    const int ppCount = loopSize * loopCount; // Number of power-points on the grid
    vector<bool> seen(ppCount);
    vector<vector<int>> loops(loopCount, vector<int>(loopSize));
    for (int loop = 0; loop < loopCount; ++loop) {
        for (int pp = 0; pp < loopSize; ++pp) {
            const int index = stream.readInteger(1, ppCount, "power-point-index") - 1;
            stream.quitif(seen[index], _wa, "Power Point %d appears more than once.", index + 1);
            seen[index] = true;
            loops[loop][pp] = index;
            stream.skipBlanks();
        }
    }
    stream.readEof();

    vector<pair<int, int>> segments;
    for (vector<int> loop : loops) {
        for (int loopSlot = 0; loopSlot < loopSize; ++loopSlot) {
            segments.push_back({loop[loopSlot], loop[(loopSlot+1)%loopSize]});
        }
    }

    for (int i = 0; i < ppCount - 1; ++i) {
        for (int j = i + 1; j < ppCount; ++j) {
            int i1 = segments[i].first;
            int i2 = segments[i].second;
            int j1 = segments[j].first;
            int j2 = segments[j].second;
            Point p1{powerPoints[i1]};
            Point p2{powerPoints[i2]};
            Point p3{powerPoints[j1]};
            Point p4{powerPoints[j2]};
            stream.quitif(i1!=j2 && i2!=j1 && intersect({p1,p2}, {p3,p4}), _wa, "Loops intersect.");
        }
    }
}

bool intersect(pair<Point, Point> const s1, pair<Point, Point> const s2) {
    int dx1 = s1.second.first - s1.first.first;
    int dx2 = s2.second.first - s2.first.first;
    int dy1 = s1.second.second - s1.first.second;
    int dy2 = s2.second.second - s2.first.second;
    int p0 = dy2*(s2.second.first-s1.first.first) - dx2*(s2.second.second-s1.first.second);
    int p1 = dy2*(s2.second.first-s1.second.first) - dx2*(s2.second.second-s1.second.second);
    int p2 = dy1*(s1.second.first-s2.first.first) - dx1*(s1.second.second-s2.first.second);
    int p3 = dy1*(s1.second.first-s2.second.first) - dx1*(s1.second.second-s2.second.second);
    return (p0*p1<=0) && (p2*p3<=0);
}
