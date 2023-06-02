#include <iostream>
#include <vector>
#include <set>

using namespace std;

const int MAX_V = 1 << 16;
set<int> withX[1+MAX_V], withY[1+MAX_V];

int main() {
    int n; cin >> n;
    vector<int> x(1+n), y(1+n);
    for (int i = 1; i <= n; ++i) {
        cin >> x[i] >> y[i];
        withX[x[i]].insert(i);
        withY[y[i]].insert(i);
    }

    string ans(1+n, ' ');
    for (int start = 1; start <= n; ++start) {
        if (ans[start] != ' ') continue;
        auto goFrom = [&](int node, int dir) {
            while (node != -1) {
                // find the next node
                withX[x[node]].erase(node);
                withY[y[node]].erase(node);
                int fol;
                if (dir == 0) {
                    if (withX[x[node]].empty()) fol = -1;
                    else fol = *withX[x[node]].begin();
                } else {
                    if (withY[y[node]].empty()) fol = -1;
                    else fol = *withY[y[node]].begin();
                }

                if (fol != -1) ans[fol] = 'A' + 'B' - ans[node];
                node = fol;
                dir = 1 - dir;
            }
        };
        ans[start] = 'A';
        goFrom(start, 0);
        goFrom(start, 1);
    }
    for (int i = 1; i <= n; ++i) cout << ans[i] << endl;
    return 0;
}
