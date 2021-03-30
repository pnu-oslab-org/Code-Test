#include <bits/stdc++.h>

using namespace std;

int N, from, to;
int weight[10001];
int memo[2][10001];
vector<int> edge[10001];

int DFS(int, int, int);

int main() {
	int treeWeight[2] = {0,}, res, root = 1;
	
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> N;

	for (int i=1; i<=N; ++i) {
		cin >> weight[i];
	}

	for (int i=0; i<N-1; ++i) {
		cin >> from >> to;
		edge[from].push_back(to);
		edge[to].push_back(from);
	}
	
	treeWeight[0] = DFS(root, 0, 0);
	treeWeight[1] = DFS(root, 0, 1);
	
	res = treeWeight[0] > treeWeight[1] ? treeWeight[0] : treeWeight[1];
	cout << res << endl;
	
	return 0;
}

int DFS(int cur, int root, int color)
{
	int child;
	int treeWeight[2] = {0,}, totalMem=0;
	if (memo[color][cur])
        return memo[color][cur];
    for (auto ptr=edge[cur].begin(); ptr != edge[cur].end(); ++ptr) {
        child = *ptr;
        if (child == root) {
            continue;
        }

        treeWeight[0] = DFS(child, cur, 0);
        if (!color) {
            treeWeight[1] = DFS(child, cur, 1);
        }
        
        totalMem += treeWeight[0]>treeWeight[1]?treeWeight[0]:treeWeight[1];
    }
    if (color) {
        totalMem += weight[cur];
    }
    memo[color][cur] = totalMem;
	return totalMem;
}
