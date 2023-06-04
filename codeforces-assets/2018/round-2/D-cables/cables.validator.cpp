#include <bits/stdc++.h>
#include "testlib.h"

using namespace std;

#define SL_MAX ((1<<13)-1)
#define XY_MAX ((1<<16)-1)

class Fraction {
    public:
    bool positive = true;
    unsigned long long nominator = 0;
    unsigned long long denominator = 1; // If 0, the fraction is considered infinity, regardless of nominator
    string str() const {return (this->positive?"":"-")+to_string(this->nominator)+"/"+to_string(this->denominator);}
    Fraction() {}
    Fraction(long long nominator, long long denominator) {
        assert(nominator || denominator); // Both cannot be 0
        assert(-(long long)UINT32_MAX <= nominator && nominator <= UINT32_MAX);
        assert(-(long long)UINT32_MAX <= denominator && denominator <= UINT32_MAX);
        this->positive = nominator < 0 && denominator < 0 || nominator >= 0 && denominator >= 0;
        this->nominator = nominator < 0 ? -nominator : nominator;
        this->denominator = denominator < 0 ? -denominator : denominator;
        if ( this->nominator == 0 ) this->denominator = 1, this->positive = true;
        if ( this->denominator == 0 ) this->nominator = 1, this->positive = true;
    }
    bool operator==(Fraction const & fraction) const {
        if ( this->denominator && fraction.denominator ) {
            return this->positive == fraction.positive && this->nominator * fraction.denominator == this->denominator * fraction.nominator;
        } else return this->denominator == fraction.denominator;
    }
    bool operator<(Fraction const & fraction) const {
        if ( this->denominator && fraction.denominator ) {
            if (this->positive != fraction.positive) return this->positive < fraction.positive;
            return this->positive == (this->nominator * fraction.denominator < this->denominator * fraction.nominator);
        } else return fraction.denominator == 0;
    }
};

typedef std::pair<int, int> Point;
typedef std::pair<Fraction, Fraction> Line;

bool has3collinear(set<Point> points);

int main(int argc, char *argv[]) {
    registerValidation(argc, argv);

    const int loopSize = inf.readInt(3, SL_MAX, "s"); inf.readSpace();
    const int loopCount = inf.readInt(1, SL_MAX, "l"); inf.readEoln();
    const int ppCount = loopSize * loopCount; // Number of power-points on the grid
    ensuref(ppCount < SL_MAX, "Condition s*l < 8192 is not met: %d*%d = %d >= 8192", loopSize, loopCount, ppCount);

    set<pair<int, int>> powerpoints;
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
    vector<Line> lines(points.size()*(points.size()-1)>>1);
    int lineIndex = 0;
    for (auto i = points.begin(); i != points.end(); ++i) {
        for (auto j = next(i); j != points.end(); ++j) {
            Line line;
            if ( i->first == j->first ) {
                line = {{1, 0}, {i->first, 1}}; // Vertical line. Slope is infinite. X-intercept used for Y-intercept
            } else {
                line = {
                    {j->second - i->second, j->first - i->first}, // slope or gradient
                    {j->first*i->second - i->first*j->second, j->first - i->first} // Y-intercept
                };
            }
            lines[lineIndex++] = line;
        }
    }
    sort(lines.begin(), lines.end());

    for (auto i = lines.begin() + 1; i!=lines.end(); ++i) {
        if ( *i == *prev(i) ) return true;
    };

    return false;
}
