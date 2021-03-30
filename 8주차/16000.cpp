#include <iostream>
#include <cstring>
#include <queue>
#include <vector>
#include <map>
using namespace std;

#define fastio() ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);

// 섬
// 모든 가장자리는 바다이다
// 4방향 bfs 탐색으로 이어져있는 섬은 한 섬이다.

typedef pair<int, int> point;
int N, M;
string input[2001]; // 입력 맵을 담는다.
vector <char> answer; // 결과 맵을 담을 벡터
int index_map[2001][2001]; // 특정 좌표가 몇번째 섬인지를 담고 있음.
point dir[4] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}}; // ↓→↑←
point diagonal[4] = {{1, 1}, {-1, 1}, {-1, -1}, {1, -1}}; // ↘↗↖↙

void bfs(int r, int c, int idx) {

    queue <point> que;
    que.push({r, c});
    index_map[r][c] = idx;

    while(!que.empty()) {
        point p = que.front();
        que.pop();

        for(int i = 0; i<4; i++) {
            int rr = p.first + dir[i].first;
            int cc = p.second + dir[i].second;

            if(rr < 0 || rr >= N || cc < 0 || cc >= M) continue; // 맵에서 벗어남
            if(index_map[rr][cc] != 0) continue; // 이미 인덱싱됨.
            if(input[rr][cc] == '.') continue;   // 육지가 아니라 바다임.

            index_map[rr][cc] = idx; // (rr,cc)는 (r,c)와 같은 섬.
            que.push({rr, cc});
        }
    }
    // 밖에서부터 인덱싱하기 때문에 안쪽에 있는 섬은 같은 숫자로 인덱싱되지 않는다.
}

int indexing() {
    int count = 0;

    // 특정 셀이 육지고 아직 특정 섬이라고 인덱싱이 안됐다면,
    // 해당 셀과 주위 육지를 BFS로 특정 섬으로 인덱싱
    for(int i = 0; i<N; i++)
        for(int j = 0; j<M; j++)
            if(input[i][j] == '#' && index_map[i][j] == 0) {
                bfs(i, j, count + 1);
                count++;
            }

    return count;
}

void checkSafety(int r, int c) {
    // 최외곽은 -1로 지정해서 조건문을 안거치게 함
    index_map[r][c] = -1;
    queue <point> que;
    que.push({r, c});

    while(!que.empty()) {
        point p = que.front();
        que.pop();

        for(int i = 0; i<4; i++) {
            int rr = p.first + dir[i].first;
            int cc = p.second + dir[i].second;

            if(rr < 0 || rr >= N || cc < 0 || cc >= M) continue;

            // 만약 인덱싱 되어 있다면(육지 or 섬이라면) 최외곽으로 갈수있다는 표시로 'O'를 넣는다.
            // index_map[rr][cc] - 1 번째 섬은 안전한 섬이란 뜻
            if(index_map[rr][cc] > 0) {
                answer[index_map[rr][cc] - 1] = 'O';
                continue;
            }

            // 조건문을 스킵하고 탐색하기 위해서.
            if(index_map[rr][cc] == 0 && input[rr][cc] == '.') {
                index_map[rr][cc] = -1;
                que.push({rr, cc});
            }
        }

        for(int i = 0; i<4; i++) {
            // 대각선 영역
            int rr = p.first + diagonal[i].first;
            int cc = p.second + diagonal[i].second;

            if(rr < 0 || rr >= N || cc < 0 || cc >= M) continue;
            if(input[rr][cc] == '#') continue;

            // 대각선에 바다가 있을 때
            // 엇갈려있는 섬이 서로 다른 섬이라면 내부도 탐색가능하다.
            if(index_map[rr][cc] != -1 && index_map[rr][p.second] > 0
               && index_map[p.first][cc] > 0 && index_map[rr][p.second] != index_map[p.first][cc]) {
                index_map[rr][cc] = -1;
                que.push({rr, cc});
            }
        }
    }

}


int main() {

    fastio();

    cin >> N >> M;
    for(int i = 0; i<N; i++)
        cin >> input[i];

    int island = indexing();    // 특정 좌표가 몇번째 섬인지 인덱싱.

    // 모든 섬을 'X'로 기록해 둠.
    // checkSafety()에서 O로 기록하지 못한 섬들이 'X'가 된다.
    answer.resize(island, 'X');

    // BFS로 첫번째 셀부터 안전한지 확인해간다.
    // 외부부터 확인하기 때문에 내부로는 들어가지 않는 특징이 있다.
    checkSafety(0, 0);

    // 정답 출력
    for(int i = 0; i<N; i++) {
        for(int j = 0; j<M; j++)
        {
            if(input[i][j] == '.') cout << '.';
            else cout << answer[index_map[i][j] - 1]; // 몇번째 섬인지를 이용
        }
        cout << '\n';
    }

    return 0;
}
