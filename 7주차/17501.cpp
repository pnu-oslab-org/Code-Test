#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

struct tree_node { char sym; int left, right, count; };

int N;
int num[100001];
int sub[100001];
tree_node node[200001];
queue<tree_node> q;
int answer = 0;
void bfs();

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> N;
	for (int i = 1; i <= N; i++)
		cin >> num[i];
	for (int i = N+1; i < 2*N; i++) {
		char temp; int left, right;
		cin >> temp >> left >> right;
		node[i] = {temp, left, right, 0};
	}
	
	q.push(node[2*N-1]);
	bfs();
	
	int count = 0;
	for (int i = 1; i <= N; i++) {
		if (sub[i] % 2 == 1)
			count++;
	} 
	sort(num+1, num+N+1);
	for (int i = 1; i <= N; i++) {
		if (i <= count)
			answer -= num[i];
		else answer += num[i];
	}
	cout << answer; return 0;
}
void bfs() {
	while(!q.empty()) {
		tree_node front = q.front();
		q.pop();
		if (front.left <= N)
			sub[front.left] = front.count;
		else
			q.push({ node[front.left].sym, node[front.left].left, node[front.left].right, node[front.left].count + front.count});
		if (front.right <= N)
			sub[front.right] = front.count + (front.sym=='-');
		else
			q.push({ node[front.right].sym, node[front.right].left, node[front.right].right, node[front.right].count + front.count + (front.sym=='-')});
	}
}
