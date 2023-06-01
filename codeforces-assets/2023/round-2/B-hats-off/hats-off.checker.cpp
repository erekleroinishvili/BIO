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

#define C_MAX 20

pair<int, vector<string>> readInput(InStream& stream);
vector<int> readAns(InStream& stream, int c);
int checkAnswer(vector<int> selected, vector<string> input, int dancers);

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    auto const [dancers, combinations] = readInput(inf);
    const int inputSize = combinations.size(); // Number of all possible combinations
    vector<int> output = readAns(ouf, inputSize);
    vector<int> answer = readAns(ans, inputSize);

    int unbalancedDancer;
    unbalancedDancer = checkAnswer(output, combinations, dancers);
    ouf.quitif(unbalancedDancer, _wa, "Wrong Answer: Dancer %d is unbalanced", unbalancedDancer);
    sort(output.begin(), output.end());
    for (int i = output.size() - 1; i > 0; --i) {
        ouf.quitif(output[i]==output[i-1], _wa, "Duplicate selection %d", output[i]);
    }

    unbalancedDancer = checkAnswer(answer, combinations, dancers);
    ans.quitif(unbalancedDancer, _wa, "Wrong Answer by Judge: Dancer %d is unbalanced", unbalancedDancer);

    if (output.size() < answer.size()) quitf(_ok, "User selected fewer combinations than the Judge.");
    else if (output.size() == answer.size()) quitf(_ok, "User selected the same number of combinations as the Judge.");
    else quitf(_ok, "User selected more combinations than the Judge.");
}

pair<int, vector<string>> readInput(InStream& stream) {
    const int dancers = stream.readInt(1, C_MAX, "c");
    stream.readEoln();
    const int length = 1 << dancers;
    vector<string> items(length);
    for (int i = 0; i < length; ++i) {
        items[i] = stream.readString("[undp]{" + to_string(dancers) + "}", "combination");
    }
    stream.readEof();
    return {dancers, items};
}


vector<int> readAns(InStream& stream, int inputSize) {
    const int answerLength = stream.readInt(1, inputSize, "c");
    stream.readEoln();
    vector<int> reply(answerLength);
    for (int i = 0; i < answerLength; ++i) {
        if ( i ) stream.readSpace();
        reply[i] = stream.readInt(1, inputSize, "combination_index");
    }
    stream.readEoln();
    stream.readEof();
    return reply;
}

/** Returns 1-based index of the unbalanced dancer or 0 otherwize. */
int checkAnswer(vector<int> selected, vector<string> input, int dancers) {
    vector<int> deltaUpDown(dancers); // For each dancer, difference (up-down) while facing front
    for (int c : selected) {
        string combination = input[c - 1];
        for (int d = 0; d < dancers; ++d) {
            char move = combination[d]; // Position of dancer with index d
            if ( move == 'u' ) ++deltaUpDown[d];
            else if (move == 'd' ) --deltaUpDown[d];
        }
    }

    for (int i = 0; i < dancers; ++i) {
        if ( deltaUpDown[i] ) return 1 + i;
    }
    return 0;
}
