#include <bits/stdc++.h>
//yjs
using namespace std;

vector<vector<int > > garden(51, vector<int>(51,0)), garden_copy, step_visited, visited[2];
vector<pair<int, int>> RG_list, RG_comb[2], test;

int N, M, RG[2], RG_count[3], flower, ans;
int dx[] = {0,1,0,-1};
int dy[] = {-1,0,1,0};

void Combination(int);
void Game();
bool step(int x, int y, int RG, int cur);
int gcnt;
int main() {
    cin >> N >> M >> RG[0] >> RG[1];
    for (int i=1; i<N+1; ++i) {
        for (int j=1; j<M+1; ++j) {
            cin >> garden[i][j];
            if (garden[i][j] == 2) {
                RG_list.push_back(make_pair(i, j));
                RG_count[0]++;
            }
        }
    }

    Combination(0);

    cout << ans << endl;

    return 0;
}

void Combination(int cur) {
    if (RG_count[1] == RG[0] && RG_count[2] == RG[1]) {
        Game();
    } else if (cur == RG_count[0]){
        return;
    } else {
        for (int i=0; i<2; ++i) {
            if (RG_count[i+1] < RG[i]) {
                RG_count[i+1]++;
                RG_comb[i].push_back(RG_list[cur]);
                Combination(cur+1);
                RG_comb[i].pop_back();
                RG_count[i+1]--;
            }
        }
        Combination(cur+1);
    }
}

void Game() {
    queue<pair<int, int>> RGQ[2];
    int idx, qsize, x, y,cur=1, bufx, bufy;
    pair<int, int> point;
    step_visited.clear();
    step_visited.assign(51, vector<int>(51,0));
    garden_copy.clear();
    garden_copy.insert(garden_copy.end(), garden.begin(), garden.end());
    flower = 0;
    for (int i=0; i<2; ++i) {
        visited[i].clear();
        visited[i].assign(51, vector<int>(51,0));
        for (int j=0; j<RG_comb[i].size(); ++j) {
            point = RG_comb[i][j];
            RGQ[i].push(point);
            step_visited[point.first][point.second] = cur;
            visited[i][point.first][point.second] = 1;
        }
    }

    while(!(RGQ[0].empty() && RGQ[1].empty())) {
        cur++;
        for (int m=0; m<2; ++m) {
            qsize = RGQ[m].size();
            for (int i=0; i<qsize; ++i) {
                x = RGQ[m].front().first;
                y = RGQ[m].front().second;
                RGQ[m].pop();
                if (!garden_copy[x][y])
                    continue;
                for (int j=0; j<4; ++j) {
                    bufx = x + dx[j];
                    bufy = y + dy[j];
                    if (bufx < 1 || bufx > N || bufy < 1 || bufy > M)
                        continue;
                    if (!visited[m][bufx][bufy]) {
                        if (step(bufx, bufy, m+3, cur)) {
                                RGQ[m].push(make_pair(bufx, bufy));
                        }
                        visited[m][bufx][bufy] = 1;
                    }
                }
            }
        }
    }

    if (ans < flower) {
        ans = flower;
    }

}

bool step(int x, int y, int RG, int cur) {
    if (!garden_copy[x][y])
        return false;
    if (step_visited[x][y] && step_visited[x][y] != cur)
        return false;
    step_visited[x][y] = cur;
    if (garden_copy[x][y] == 3 && RG == 4) {
        flower++;
        garden_copy[x][y] = 0;
        return false;
    }
    garden_copy[x][y] = RG;
    return true;
}
