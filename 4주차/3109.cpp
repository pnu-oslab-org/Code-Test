#include<iostream>
 
#define endl "\n"
#define MAX 10000
using namespace std;
 
int R, C, Answer;
char MAP[MAX][500];
bool Visit[MAX][500];
bool Ans;
 
int dx[] = { -1, 0, 1 };
int dy[] = { 1, 1, 1, };
void Input()
{
    cin >> R >> C;
    for (int i = 0; i < R; i++)
    {
        for (int j = 0; j < C; j++)
        {
            cin >> MAP[i][j];
        }
    }
}
 
void DFS(int x, int y)
{
    Visit[x][y] = true;
    if (y == C - 1)
    {
        Ans = true;
        Answer++;
        return;
    }
 
    for (int i = 0; i < 3; i++)
    {
        int nx = x + dx[i];
        int ny = y + dy[i];
 
        if (nx >= 0 && ny >= 0 && nx < R && ny < C)
        {
            if (MAP[nx][ny] == '.' && Visit[nx][ny] == false)
            {
                DFS(nx, ny);
                if (Ans == true) return;
            }
        }
    }
}
 
void Solution()
{
    for (int i = 0; i < R; i++)
    {
        Ans = false;
        DFS(i, 0);
    }
    cout << Answer << endl;
}
 
void Solve()
{
    Input();
    Solution();
}
 
int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
 
    Solve();
 
    return 0;
}
