#include <bits/stdc++.h>

using namespace std;

int main() {
	// freopen("input.txt", "r", stdin);
	// freopen("output.txt", "w", stdout);
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int n, m; cin >> n >> m;
	vector<int> s(2*n);
	for (int &x : s) cin >> x;

	vector<int> lastOccurance(1+m, -1); // x position of rightmost occurance
	for (int i = 0; i < n; ++i) {
		lastOccurance[s[i]] = i;
		lastOccurance[s[n+i]] = i;
	}

	vector<int> lopresum(1+n);
	for (int i = 1; i <= m; ++i) if (lastOccurance[i] >= 0) lopresum[lastOccurance[i]+1]++;
	for (int i = 1; i <= n; ++i) lopresum[i] += lopresum[i-1];

	vector<pair<int, int>> componentFinish(2*n); // position, 0/1/2
	for (int i = n-1; i >= 0; --i) {
		if (i < n-1 && s[i] == s[i+1]) componentFinish[i] = componentFinish[i+1];
		else componentFinish[i] = {i, 0};
		if (i < n-1 && s[n+i] == s[n+i+1]) componentFinish[n+i] = componentFinish[n+i+1];
		else componentFinish[n+i] = {i, 1};

		if (s[i] == s[n+i]) {
			if (componentFinish[i].first > i || componentFinish[n+i].first > i) {
				componentFinish[i] = componentFinish[n+i] = max(componentFinish[i], componentFinish[n+i]);
			} else componentFinish[i] = componentFinish[n+i] = {i, 2};
		}
	}


	// dp on distance travelled right and which of the last column's two cells are occupied
	//  value in dp is time to finish if filled in all gaps of values that do not appear further to the right
	vector<int> dp[3]{}; // 0 means top, 1 means bottom, 2 means both
	dp[0].resize(n), dp[1].resize(n), dp[2].resize(n);
	for (int i = n-2; i >= 0; --i) {
		for (int type = 2; type >= 0; --type) {
			pair<int, int> choice[2]{}; int v[2]{};
			if (type == 0) {
				choice[0] = componentFinish[i+1]; v[0] = s[i+1];
				choice[1] = componentFinish[n+i]; v[1] = s[n+i];
				if (choice[1].first == i) choice[1].second = 2;
			} else if (type == 1) {
				choice[0] = componentFinish[i]; v[0] = s[i];
				if (choice[0].first == i) choice[0].second = 2;
				choice[1] = componentFinish[n+i+1]; v[1] = s[n+i+1];
			} else {
				choice[0] = componentFinish[i+1]; v[0] = s[i+1];
				choice[1] = componentFinish[n+i+1]; v[1] = s[n+i+1];
			}
			// if not last occurance, add one to cost
			int cost[2]{};
			for (int ch = 0; ch <= 1; ++ch) {
				if (lastOccurance[v[ch]] != choice[ch].first) ++cost[ch];
				cost[ch] += dp[choice[ch].second][choice[ch].first];
				int extra = lopresum[choice[ch].first + 1] - lopresum[i + 1];
				cost[ch] += extra;
			}
			dp[type][i] = min(cost[0], cost[1]);
		}
	}

	int extra = lopresum[componentFinish[0].first + 1];
	if (lastOccurance[s[0]] == componentFinish[0].first) --extra;
	cout << dp[componentFinish[0].second][componentFinish[0].first] + extra << endl;
	return 0;
}
