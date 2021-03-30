#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> tree, weight;
vector<int> stk;
int V, n, t, w;
int **dp;

int DFS(int, int, int*);
int main() {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    
    int length=0, node;
	cin >> V;

	tree.assign(V+1, vector<int>());
	weight.assign(V+1, vector<int>());

	for (int i=0; i<V; ++i) {
		cin >> n;
		while (1) {
			cin >> t;
			if (t < 0)
				break;
			cin >> w;
			tree[n].push_back(t);
			weight[n].push_back(w);
		}
	}
	node = DFS(1, -1, &length);
	length = 0;
	DFS(node, -1, &length);

	cout << length << endl;
}

int DFS(int cur, int root, int *length) {
    int child, path_length, maximum_weight=0, maximum_node=cur, node, i=0;
    for (i=0; i<tree[cur].size(); ++i){
        child = tree[cur][i];
        if (child == root){
            continue;
        }
        path_length = 0;
        node = DFS(child, cur, &path_length);
        if (maximum_weight < weight[cur][i] + path_length) {
            maximum_weight = weight[cur][i] + path_length;
            maximum_node = node;
        }
    }
    *length = maximum_weight;
    return maximum_node;
}
