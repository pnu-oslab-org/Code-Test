#include <iostream>
#include <vector>
#include <queue>
#include <string.h>

using namespace std;

const int dx[] = { 1, -1, 0, 0};
const int dy[] = { 0, 0, 1, -1};

int n, m;
int v[100][100];
bool visited[100][100];
vector<pair<int,int>> c;

void bfs()
{
    queue<pair<int,int>> q;

    memset(visited, false, sizeof(visited));
    q.push({0, 0});
    visited[0][0] = true;

    while (!q.empty()) {
        auto next = q.front(); q.pop();

        for (int i=0; i<4; i++) {
            int x = next.second + dx[i];
            int y = next.first + dy[i];

            if (y < 0 || x < 0 || y >= n || x >= m)
                continue;
            if (visited[y][x])
                continue;

            if (v[y][x] >= 1) {
                v[y][x]++;
                continue;
            }

            q.push({y, x});
            visited[y][x] = true;
        }
    }
}

bool melt()
{
    bool melted = false;

    for (auto next : c) {
        if (v[next.first][next.second] >= 3) {
            v[next.first][next.second] = 0;
            melted = true;
        } else if (v[next.first][next.second] == 2) {
            v[next.first][next.second] = 1;
        }
    }

    return melted;
}

int main()
{

    cin >> n >> m;
    for (int i=0; i<n; i++) {
        for (int j=0; j<m; j++) {
            cin >> v[i][j];
            if (v[i][j])
                c.push_back({i, j});
        }
    }

    int time = 0;
    while (true) {
        bfs();
        if (melt()) time++;
        else break;
    }

    cout << time;

    return 0;
}
