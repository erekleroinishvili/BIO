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

#define N_MAX ((1<<13)-1)
#define XY_MAX ((1<<16)-1)

pair<int, vector<pair<int, int>>> readInput(InStream& stream);
void checkAnswer(InStream& stream, vector<pair<int, int>> desks);

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    auto const [deskCount, desks] = readInput(inf);
    checkAnswer(ouf, desks);
    // checkAnswer(ans, desks);

    quitf(_ok, "All rows and columns are balanced.");

}

pair<int, vector<pair<int, int>>> readInput(InStream& stream) {
    const int deskCount = stream.readInt(1, N_MAX, "n");
    stream.readEoln();
    vector<pair<int, int>> desks(deskCount);
    for (int i = 0; i < deskCount; ++i) {
        int const a = stream.readInt(0, XY_MAX, "x"); stream.readSpace();
        int const b = stream.readInt(0, XY_MAX, "y"); stream.readEoln();
        desks[i] = make_pair(a, b);
    }
    stream.readEof();
    return {deskCount, desks};
}

void checkAnswer(InStream& stream, vector<pair<int, int>> desks) {
    map<int, int> rows;
    map<int, int> cols;
    for (int i = 0; i < desks.size(); ++i) {
        string team = stream.readWord("[AB]", "AlphaOrBetaTeam");
        if (team=="A") {
            ++rows[desks[i].second];
            ++cols[desks[i].first];
        } else {
            --rows[desks[i].second];
            --cols[desks[i].first];
        }
    }
    for (auto [y, delta] : rows) {
        stream.quitif(abs(delta)>1, _wa, "Row y=%d has high delta of %d", y, abs(delta));
    }
    for (auto [x, delta] : cols ) {
        stream.quitif(abs(delta)>1, _wa, "Column x=%d has high delta of %d", x, abs(delta));
    }

}
