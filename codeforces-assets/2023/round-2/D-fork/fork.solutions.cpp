#include <bits/stdc++.h>

using namespace std;

int main() {
	// freopen("input.txt", "r", stdin);
	// freopen("output.txt", "w", stdout);
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int n, m, c; cin >> n >> m >> c;
	vector<int> s(2*n), a(1+c);
	for (int &x : s) cin >> x;
	for (int i = 1; i <= c; ++i) cin >> a[i];
	a[0] = s[0];

	vector<vector<int>> nextOccurance(1+m);
	for (int i = c; i >= 0; --i) nextOccurance[a[i]].push_back(i);

	// Dijkstra's
	vector<int> dist(2*n, c+1);
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
	dist[0] = 0, pq.emplace(0, 0);
	vector<bool> seen(2*n);
	int lastT = 0;
	while (!pq.empty()) {
		pair<int, int> pr = pq.top();
		pq.pop();
		int t = pr.first, v = pr.second;
		if (seen[v]) continue;
		seen[v] = true;

		while (lastT < t) {
			nextOccurance[a[lastT]].pop_back();
			++lastT;
		}

		vector<int> children;
		if (v % n) children.push_back(v-1);
		if ((v+1) % n) children.push_back(v+1);
		children.push_back(v < n ? v+n : v-n);
		for (int u : children) {
			// find next point in time from t when the trendsetter changes to v[u]
			/// currently brute force
			int nextT = c+1;
			if (!nextOccurance[s[u]].empty()) nextT = nextOccurance[s[u]].back();
			if (nextT < dist[u]) {
				dist[u] = nextT;
				pq.emplace(nextT, u);
			}
		}
	}

	int cnt = 0;
	for (int i = 0; i < 2*n; ++i) cnt += dist[i] <= c || s[i] == a.back();
	cout << cnt << endl;
	return 0;
}
