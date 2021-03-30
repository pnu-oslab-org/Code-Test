#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <queue>

#define INF 9999999999999999

using namespace std;
typedef pair<int, int> p;
typedef long long ll;

int n, m;
ll dist_fox[4001];
ll dist_wolf[4001][2];
vector<p> adj[4001];

void dijkstra_fox() {
    priority_queue<pair<ll, int>> pque;
    dist_fox[1] = 0;
    pque.push({ 0, 1 });

    while (!pque.empty()) {
        pair<ll, int> cur = pque.top();
        pque.pop();

        ll distval = -cur.first;
        int node = cur.second;

        if (dist_fox[node] >= distval) {
            for (int i = 0; i < adj[node].size(); i++) {
                int nextnode = adj[node][i].first;
                ll newDist = distval + adj[node][i].second;
                if (dist_fox[nextnode] > newDist) {
                    dist_fox[nextnode] = newDist;
                    pque.push({ -newDist, nextnode });
                }
            }
        }
    }
}

void dijkstra_wolf() {
    priority_queue<pair<pair<ll, int>, int>> pque;
    dist_wolf[1][1] = 0;
    pque.push({ { 0, 1 }, 1 });

    while (!pque.empty()) {
        pair<pair<ll, int>, int> cur = pque.top();
        pque.pop();

        ll distval = -cur.first.first;
        int node = cur.first.second;
        int sprint = cur.second;

        if (dist_wolf[node][sprint] >= distval) {
            for (int i = 0; i < adj[node].size(); i++) {
                int nextnode = adj[node][i].first;
                ll newDist;
                if(sprint) newDist = distval + adj[node][i].second / 2;
                else newDist = distval + (long long)adj[node][i].second * 2;

                int nextsprint;
                if (sprint) nextsprint = 0;
                else nextsprint = 1;

                if (dist_wolf[nextnode][nextsprint] > newDist) {
                    dist_wolf[nextnode][nextsprint] = newDist;
                    pque.push({ { -newDist, nextnode }, nextsprint });
                }
            }
        }
    }
}


void init() {
    int f, s, w;
    cin >> n >> m;

    for (int i = 0; i < m; i++) {
        cin >> f >> s >> w;
        adj[f].push_back({ s, w * 2 });
        adj[s].push_back({ f, w * 2 });
    }

    for (int i = 1; i <= n; i++) {
        dist_fox[i] = INF;
        dist_wolf[i][0] = INF;
        dist_wolf[i][1] = INF;
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(NULL);

    init();
    dijkstra_fox();
    dijkstra_wolf();

    int answer = 0;
    for (int i = 2; i <= n; i++) {
        if (dist_fox[i] == INF) continue;
        if (dist_fox[i] < min(dist_wolf[i][0], dist_wolf[i][1])) answer++;
    }

    printf("%d\n", answer);

    return 0;
}
