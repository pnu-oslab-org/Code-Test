#include <bits/stdc++.h>

using namespace std;

vector<vector<pair<int, int > > > loadMap;
vector<int> weight;
vector<bool> v;
vector<vector<bool>> visited;
int N, M;
int S, D;
int MMM;

int DFS1(int start, int dest) {
    int child, w;
    if (start == dest)
        return 0;

    for (int i=0; i<loadMap[start].size(); ++i){
        child = loadMap[start][i].first;
        w = loadMap[start][i].second;
        if(!v[child]){
            weight[start] = max(weight[start], DFS1(child, dest) + w);
        } else {
            weight[start] = max(weight[start], weight[child] + w);
        }
    }
    v[start] = true;
    return weight[start];

}

int DFS2(int start, int dest, int ww) {
    int ret = 0, child, w;
    if (ww + weight[start] == MMM) {
        ++ret;
    } else {
        return 0;
    }

    for (int i=0; i<loadMap[start].size(); ++i) {
        child = loadMap[start][i].first;
        w = loadMap[start][i].second;
        if (visited[start][child] == false) {
            ret += DFS2(child, dest, ww + w);
            visited[start][child] = true;
        }
    }
    return ret;
}

int main() {
    int from, to, w, start, dest, total=0, ret;
    cin >> N >> M;
    loadMap.assign(N+1, vector<pair<int, int>>());
    weight.assign(N+1, 0);
    v.assign(N+1, false);
    visited.assign(N+1, vector<bool>(N+1, false));
    for (int i=0; i<M; ++i) {
        cin >> from >> to >> w;
        loadMap[from].push_back(make_pair(to, w));
    }

    cin >> S >> D;

    ret = DFS1(S, D);
    MMM = ret;
    total = DFS2(S, D, 0);

    cout <<ret<< endl;
    cout << total -1 << endl;

    return 0;
}
