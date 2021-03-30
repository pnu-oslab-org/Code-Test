#include <bits/stdc++.h>

#define minimum -10000000

using namespace std;

void traversal(int, int);

vector<vector<int>> game, dp, visited;

int N,M,D, res, chk;

int main() {
    int t, flag=0;

    cin >> N >> M >> D;

    game.assign(N+1, vector<int>(M+1, 0));
    dp.assign(N+1, vector<int>(M+1, 0));
    visited.assign(N, vector<int>(M, 0));
    for(int i=0; i<M; ++i) {
        dp[0][i] = 0;
        visited[0][i] = 1;

    }

    for (int i=0; i<N; ++i) {
        for (int j=0; j<M; ++j) {
            cin >> game[i][j];
        }
    }

    for(int i=0; i<N; ++i) {
        for (int j=0; j<M; ++j) {
            if (!visited[i][j])
                continue;
            traversal(i, j);
        }
    }

    for (t=0; t<M; ++t) {
        if (visited[N-1][t]) {
            res = dp[N-1][t];
            flag = 1;
            break;
        }
    }

    for (; t<M; ++t) {
        if (visited[N-1][t] && res < dp[N-1][t]) {
            res = dp[N-1][t];
            flag = 1;
        }
    }

    if (!flag) { res = 0; }
    cout << res << endl;

    return 0;
}

void traversal(int x, int y) {
    int dest_x, dest_y, buf;
    for (int i=1; i<=D; ++i) {
        for (int j=-(D-i); j<=D-i; ++j) {
            dest_x = x + i;
            dest_y = y +j;
            if (!(dest_x >= 0 && dest_x <N &&
                dest_y >= 0 && dest_y <M)) {
                continue;
                }
            if (visited[dest_x][dest_y]){
                dp[dest_x][dest_y] = max(dp[dest_x][dest_y] ,dp[x][y] + game[x][y]*game[dest_x][dest_y]);
            } else {
                dp[dest_x][dest_y] = dp[x][y] + game[x][y]*game[dest_x][dest_y];
            }
            visited[dest_x][dest_y] = 1;
        }
    }
}
