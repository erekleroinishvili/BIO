#include <bits/stdc++.h>

using namespace std;

int main() {
	// freopen("input.txt", "r", stdin);
	// freopen("output.txt", "w", stdout);
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int n; cin >> n;
	vector<vector<int>> g(n);
	int g1, g2;
	while (cin >> g1 >> g2 && g1 != -1) {
		--g1, --g2;
		g[g1].push_back(g2);
		g[g2].push_back(g1);
	}

	if (g[0].size() < 2) {
		cout << 1 << endl;
		return 0;
	}

	vector<bool> notThree(n);
	for (int i = 0; i < n; ++i) {
		if (g[i].size() < 3) notThree[i] = true;
	}


	// bfs from root
	vector<int> distFromRoot(n, -1);
	distFromRoot[0] = 0;
	queue<int> q;
	q.push(0);
	while (!q.empty()) {
		int v = q.front();
		q.pop();
		for (int u : g[v]) {
			if (distFromRoot[u] == -1) {
				distFromRoot[u] = distFromRoot[v] + 1;
				q.push(u);
			}
		}
	}

	int minBad = n;

	// case 1: get to node with degree < 3
	for (int v = 1; v < n; ++v) {
		if (notThree[v] && distFromRoot[v] != -1) minBad = min(minBad, distFromRoot[v] + 1);
	}

	// case 2: reach and traverse a cycle
	for (int pivot = 0; pivot < n; ++pivot) { // reach pivot which is on a cycle
		if (distFromRoot[pivot] == -1) continue;

		// optimisation to ignore pivots that can never help
		//  cycleLen >= 3, so total cost will be at least distFromRoot[pivot] + 3 - 1 = distFromRoot[pivot] + 2
		if (distFromRoot[pivot] + 2 >= minBad) continue;

		// max useful cycle:
		//  distFromRoot[pivot] + cycleLen - 1 < minBad
		//  cycleLen - 1 < minBad - distFromRoot[pivot]
		//  dist[i] + dist[j] < minBad - distFromRoot[pivot]

		// bfs from pivot
		while (!q.empty()) q.pop();
		vector<int> dist(n, -1), previous(n, -1);
		dist[pivot] = 0;
		q.push(pivot);
		while (!q.empty()) {
			int v = q.front();
			if (dist[v] + dist[v] - 1 >= minBad - distFromRoot[pivot]) break; // optimisation
			q.pop();
			for (int u : g[v]) {
				if (dist[u] == -1) {
					dist[u] = dist[v] + 1;
					previous[u] = v;
					q.push(u);
				} else if (u != previous[v] && v != previous[u]) {
					minBad = min(minBad, distFromRoot[pivot] + dist[u] + dist[v]);
				}
			}
		}

//		for (int i = 0; i < n; ++i) {
//			if (distFromRoot[i] == -1) continue;
//			for (int j : g[i]) {
//				if (previous[i] != j && previous[j] != i) {
//					int cycleLen = dist[i] + dist[j] + 1;
//					minBad = min(minBad, distFromRoot[pivot] + cycleLen - 1);
//				}
//			}
//		}
	}

	cout << minBad << endl;
	return 0;
}
