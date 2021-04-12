#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

pair<double,double> mouse[101];
vector<int> avail[101];
bool visit[100] = { false, };
int hiding[101];

double get_dist(pair<double,double> a, pair<double,double> b)
{
	return (b.first - a.first)*(b.first - a.first) + (b.second - a.second)*(b.second - a.second);
}

bool dfs(int cur)
{
	if (visit[cur])
		return false;

	visit[cur] = true;

	for (int next : avail[cur]) {
		if (hiding[next] == -1 || dfs(hiding[next])) {
			hiding[next] = cur;
			return true;
		}
	}
	return false;
}

int main(void)
{
	int n, m, s, v;
	double limit;
	int ans = 0;

	cin >> n >> m >> s >> v;

	limit = (s * v) * (s * v);

	for (int i=0; i<n; i++)
		cin >> mouse[i].first >> mouse[i].second;

	for (int i=0; i<m; i++) {
		pair<double,double> cave;

		cin >> cave.first >> cave.second;

		for (int j=0; j<n; j++) {
			double dist = get_dist(mouse[j], cave);

			if (dist <= limit)
				avail[j].push_back(i);
		}
	}

	fill(hiding, hiding + m, -1);
	for (int i=0; i<n; i++) {
		fill(visit, visit + m, false);
		if (dfs(i))
			ans++;
	}

	cout << (int)(n - ans);

	return 0;
}
