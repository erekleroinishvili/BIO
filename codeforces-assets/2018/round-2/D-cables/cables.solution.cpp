#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

struct Point {
    int x, y, i;
    bool operator == (const Point &p2) const {
        return x==p2.x && y==p2.y;
    }
};

int main() {
    int s, l; cin >> s >> l;
    vector<Point> p(s*l);
    for (int i = 0; i < s*l; ++i) {
        cin >> p[i].x >> p[i].y;
        p[i].i = i+1;
    }
    sort(p.begin(), p.end(), [](const Point &p1, const Point &p2) {
         return pair<int, int>(p1.x, p1.y) < pair<int, int>(p2.x, p2.y);
    });
    for (int i = 0; i < l; ++i) {
        vector<Point> loop(s);
        for (int j = 0; j < s; ++j) loop[j] = p[s*i + j];
        Point pivot(loop[0]);
        sort(loop.begin(), loop.end(), [&pivot](const Point &p1, const Point &p2) {
             if (p2 == pivot) return false;
             if (p1 == pivot) return true;
             return atan2(p1.y - pivot.y, p1.x - pivot.x) < atan2(p2.y - pivot.y, p2.x - pivot.x);
        });
        for (Point pnt : loop) cout << pnt.i << ' ';
        cout << endl;
    }
    return 0;
}
