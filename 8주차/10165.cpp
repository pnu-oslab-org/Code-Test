#include <bits/stdc++.h>
using namespace std;

struct Node{
	int f, e, i;
	bool operator < (Node &x){
		if(f == x.f) return e > x.e;
		return f < x.f;
	}
};

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0);
	int n, m; cin >> n >> m;
	vector<Node> v(m);

	int back = 0; //0을 지나는 노선의 종점의 최댓값

	for(int i=0; i<m; i++){
		cin >> v[i].f >> v[i].e;
		v[i].i = i+1;
		if(v[i].f > v[i].e){
			back = max(back, v[i].e);
			v[i].e += n;
		}
	}
	sort(v.begin(), v.end());

	deque<Node> dq;
	for(auto node : v){
		if(dq.empty() || dq.back().e < node.e) dq.push_back(node);
	}
	while(!dq.empty() && dq.front().e <= back) dq.pop_front();
	sort(dq.begin(), dq.end(), [&](Node &a, Node &b){
		return a.i < b.i;
	});
	for(auto node : dq) cout << node.i << " ";
}
