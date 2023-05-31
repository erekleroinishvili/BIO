#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

const long long int LL_MAX = ~0ULL >> 1;

int main() {
    int v; cin >> v;
    vector< vector< pair<int, long long> > > g(1+v);
    int x, y; long long t;
    while (cin >> x && cin >> y && cin >> t && x != -1) {
        g[x].emplace_back(y, t);
        g[y].emplace_back(x, t);
    }

    vector<long long> dist[2];
    auto shortestPath = [&](int start, int store) {
        dist[store] = vector<long long>(1+v, LL_MAX);
        priority_queue< pair<long long, int>, vector< pair<long long, int> >, greater< pair<long long, int> > > pq;
        vector<bool> seen(1+v);
        dist[store][start] = 0;
        pq.emplace(0, start);
        while (!pq.empty()) {
            int node = pq.top().second;
            pq.pop();

            if (seen[node]) continue;
            seen[node] = true;

            for (pair<int, long long> child : g[node]) {
                long long d = dist[store][node] + child.second;
                if (!seen[child.first] && d < dist[store][child.first]) {
                    dist[store][child.first] = d;
                    pq.emplace(d, child.first);
                }
            }
        }
    };

    shortestPath(1, 0);
    shortestPath(v, 1);

    long long minD = LL_MAX;
    for (int node = 1; node <= v; ++node) {
        for (auto [child, w] : g[node]) {
            long long curD = dist[0][node] + w/2 + dist[1][child];
            minD = min(minD, curD);
        }
    }
    cout << minD << endl;
    return 0;
}
