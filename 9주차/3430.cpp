#include<stdio.h>
#include<queue>
#include<vector>
#include<algorithm>
using namespace std;
const int MAX_N = 1e6, MAX_M = 1e6;
int n, m, z, a[MAX_M], t[MAX_N + 1], nxt[MAX_M];
bool ck[MAX_N + 1];
int main() {
    scanf("%d", &z);
    while (z--) {
        scanf("%d %d", &n, &m);
        for (int i = 0; i < m; i++) scanf("%d", &a[i]);
        fill(t + 1, t + n + 1, m);
        fill(ck + 1, ck + n + 1, true);
        for (int i = m - 1; i >= 0; i--) {
            nxt[i] = t[a[i]];
            t[a[i]] = i;
        }
        vector<int> res;
        priority_queue<pair<int, int> > pq;
        for (int i = 1; i <= n; i++) pq.push({ -t[i], i });
        int i;
        for (i = 0; i < m; i++) {
            if (!a[i]) {
                if (pq.empty()) res.push_back(0);
                else {
                    res.push_back(pq.top().second);
                    ck[pq.top().second] = false;
                    pq.pop();
                }
            }
            else {
                if (ck[a[i]]) break;
                ck[a[i]] = true;
                pq.push({ -nxt[i], a[i] });
            }
        }
        if (i == m) {
            puts("YES");
            for (auto it : res) printf("%d ", it);
            puts("");
        }
        else puts("NO");
    }
    return 0;
}
