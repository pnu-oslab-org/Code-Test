#include <bits/stdc++.h>

using namespace std;

vector<int> weight, G[11];
bool visited[11], visited_side[2][11];
int N, edge, buf, side_count[2], minimum=9999999;

int DFS(int node, int side) {
    int child, res = weight[node];
    visited_side[side][node] = true;
    side_count[side]++;
    for (int i=0; i<G[node].size(); ++i) {
        child = G[node][i];
        if (visited[child] != side || visited_side[side][child])
            continue;
        res += DFS(child, side);
    }
    return res;
}

int CheckConnection(int side) {
    int res=0;
    for (int i=1; i<=N; ++i) {
        if (visited[i] == side) {
            res = DFS(i, side);
            return res;
        }
    }
    return res;
}

int Check() {
    int res1, res2, res;
    side_count[0] = 0;
    side_count[1] = 0;
    res1 = CheckConnection(0);
    res2 = CheckConnection(1);
    memset(visited_side, 0, sizeof(bool)*2*11);
    res = side_count[0] + side_count[1];
    if (res != N || res1 == 0 || res2 == 0)
        return -1;
    return max(res1, res2) - min(res1, res2);
}

int Combination(int start) {
    int res;
    res = Check();
    if ((res < minimum) && (res != -1)) {
        minimum = res;
    }
    for (int i=start; i<=N; ++i) {
        if (visited[i])
            continue;
        visited[i] = true;
        Combination(i);
        visited[i] = false;
    }
    return res;
}

int main() {
    cin >> N;
    weight.push_back(0);
    for (int i=0; i<N; ++i) {
        cin >> buf;
        weight.push_back(buf);
    }

    for (int i=1; i<=N; ++i) {
        cin >> edge;
        for (int j=0; j<edge; ++j) {
            cin >> buf;
            G[i].push_back(buf);
        }
    }

    Combination(1);
    if (minimum == 9999999) {
        cout << -1 << endl;
    } else {
        cout << minimum << endl;
    }
    return 0;
}
