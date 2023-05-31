#include <bits/stdc++.h>
#include "testlib.h"

using namespace std;

#define V_MAX (1<<12)
#define T_MAX (1LL<<50)

pair<int, int> orderedPairOf(int a, int b);
bool isLinked(const vector<vector<int>> & graph);

int main(int argc, char *argv[]) {
    registerValidation(argc, argv);

    int v = inf.readInt(2, V_MAX, "v");
    inf.readEoln();

    set<pair<int, int>> byways; // Existing byways to avoid duplicates
    vector<vector<int>> graph(v); // For each village, list of directly linked villages. All 0-based.

    while (true) {
        int node1 = inf.readInt(-1, v, "village_from"); // Byway: first village
        inf.readSpace();
        int node2 = inf.readInt(-1, v, "village_to"); // Byway: second village
        inf.readSpace();
        long long time = inf.readLong(-1, T_MAX, "travel_time");
        inf.readEoln();

        if (node1 == -1 && node2 == -1 && time == -1) break;
        ensuref(node1>0 && node2>0, "Invalid village on byway %d %d %td", node1, node2, time);
        ensuref(node1 != node2, "Self loop byway %d %d %d", node1, node2, time);
        ensuref(time>0 && !(time&1), "Invalid travel time for byway %d %d %td", node1, node2, time);

        auto path = orderedPairOf(node1, node2);
        ensuref(byways.find(path)==byways.end(), "Duplicate byway from village %d to %d", path.first, path.second);
        byways.insert(path);
        --node1, --node2;
        graph[node1].push_back(node2);
        graph[node2].push_back(node1);
    }
    inf.readEof();
    ensuref(isLinked(graph), "All villages must be linked");
}

/** Generates a pair of integers in non-decreasing order, i.e.: p.first <= p.second*/
pair<int, int> orderedPairOf(int a, int b) {
    if (a<b) return {a,b};
    return {b,a};
}

/** Checks if a graph is connected */
bool isLinked(const vector<vector<int>> & graph) {
    vector<bool> seen(graph.size(), false);

    auto dfs = [&seen, &graph](auto dfs, int node = 0){
        if ( seen[node] ) return;
        seen[node] = true;
        for (int n : graph[node]) dfs(dfs, n);
    };

    dfs(dfs);
    for (bool visited : seen) if ( ! visited ) return false;
    return true;
}
