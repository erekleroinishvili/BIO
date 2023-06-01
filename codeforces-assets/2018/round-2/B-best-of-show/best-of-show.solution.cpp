#include <iostream>
#include <list>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int n; cin >> n;
    vector< vector<bool> > matrix(1+n, vector<bool>(1+n));
    for (int i = 0; i < n*(n-1)/2; ++i) {
        int w, l; cin >> w >> l;
        matrix[w][l] = false;
        matrix[l][w] = true;
    }

    list<int> order;
    order.insert(order.end(), 1);
    for (int i = 2; i <= n; ++i) {
        bool found = false;
        for (list<int>::iterator it = order.begin(); it != order.end() && !found; ++it) {
            int j = *it;
            if (matrix[i][j]) {
                found = true;
                order.insert(it, i);
            }
        }
        if (!found) order.insert(order.end(), i);
    }

    for (int i : order) cout << i << ' ';
    cout << endl;
    return 0;
}
