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

#define N_MAX (1<<10)

pair<int, set<pair<int, int>>> readInput(InStream& stream);
void checkAnswer(InStream& stream, set<pair<int, int>> comparisons, int filmCount, string author);

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    auto const [filmCount, comparisons] = readInput(inf);
    checkAnswer(ouf, comparisons, filmCount, "Contestant");
    checkAnswer(ans, comparisons, filmCount, "Judge");

    quitf(_ok, "All films are ordered correctly");

}

pair<int, set<pair<int, int>>> readInput(InStream& stream) {
    const int filmCount = stream.readInt(1, N_MAX, "n");
    stream.readEoln();
    const int length = filmCount*(filmCount-1)/2;
    set<pair<int, int>> comparisons;
    for (int i = 0; i < length; ++i) {
        int const a = stream.readInt(1, filmCount, "n"); stream.readSpace();
        int const b = stream.readInt(1, filmCount, "n"); stream.readEoln();
        stream.quitif(a==b, _fail, "Bad input: Should not compare film to itself: %d %d", a, b);
        bool hasAB = comparisons.find({a, b}) != comparisons.end();
        bool hasBA = comparisons.find({b, a}) != comparisons.end();
        stream.quitif(hasAB || hasBA, _fail, "Bad input: Duplicate pair %d %d", a, b);
        comparisons.emplace(a, b);
    }
    stream.readEof();
    return {filmCount, comparisons};
}

void checkAnswer(InStream& stream, set<pair<int, int>> comparisons, int filmCount, string author) {
    int a = 0, b = 0;
    vector<bool> seen(1 + filmCount, false);
    vector<int> films = stream.readIntegers(filmCount, 1, filmCount, "film");
    seen[films[0]] = true;
    for (int i = 1; i < filmCount; ++i) {
        stream.quitif(seen[films[i]], _wa, "%s output film %d more than once", author.c_str(), films[i]);
        seen[films[i]] = true;
        stream.quitif(comparisons.find({films[i], films[i-1]})==comparisons.end(), _wa, "%s output an invalid sequence %d %d", author.c_str(), films[i-1], films[i]);
    }
    stream.skipBlanks();
    stream.readEof();
}
