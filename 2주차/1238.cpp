#include <bits/stdc++.h>

using namespace std;

void dik(int);

struct cmp {
    bool operator()(pair<int, int> a, pair<int, int> b){
        return a.second > b.second;
    };
};

priority_queue<pair<int, int>, vector<pair<int, int>>, cmp> pq;
vector<vector<pair<int, int>>> tree[2];
vector<int> length[2], visited;
int N, M, X;

int main() {
    int from, to, T, maximum=0, buf;

    cin >> N >> M >> X;

    tree[0].assign(N+1, vector<pair<int, int>>());
    tree[1].assign(N+1, vector<pair<int, int>>());
    length[0].assign(N+1, 100000);
    length[1].assign(N+1, 100000);
    visited.assign(N+1, 0);

    for (int i=0; i<M; ++i) {
        cin >> from >> to >> T;
        tree[0][from].push_back(make_pair(to, T));
        tree[1][to].push_back(make_pair(from, T));
    }

    length[0][X] = length[1][X] = 0;

    pq.push(make_pair(X, 0));
    dik(0);
    visited.clear();
    visited.assign(N+1, 0);
    pq.push(make_pair(X, 0));
    dik(1);

    for(int i=1; i<N+1; ++i){
        buf = length[0][i] + length[1][i];
        if (buf > maximum){
            maximum = buf;
        }
    }

    cout << maximum << endl;

    return 0;
}


void dik(int dir){
    pair<int, int> top;
    int child, child_weight, node;

    while(!pq.empty()) {
        top = pq.top();
        node = top.first;
        visited[node] = 1;
        pq.pop();
        for (int i=0; i<tree[dir][node].size(); ++i){
            child = tree[dir][node][i].first;
            child_weight = tree[dir][node][i].second;
            if (visited[child]){
                continue;
            }
            length[dir][child] = min(length[dir][child], length[dir][node] + child_weight);
            pq.push(make_pair(child, length[dir][child]));
        }
    }
}
