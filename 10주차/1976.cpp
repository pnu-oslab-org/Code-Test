#include <cstring>
#include <iostream>
#include <set>
using namespace std;

#define MAX_N (201)
#define endl ('\n')
set<int> to[MAX_N];

int N, M;
set<int> plan;
bool is_visit[MAX_N];

void prepare() {
  cin >> N;
  cin >> M;

  for (int i = 1; i <= N; i++) {
    for (int j = 1; j <= N; j++) {
      int is_linked = 0;
      cin >> is_linked;
      if (is_linked == 1) {
        to[i].insert(j);
        to[j].insert(i);
      }
    }
  }

  for (int i = 1; i <= M; i++) {
    int city;
    cin >> city;
    plan.insert(city);
  }
}

void dfs(int node) {
  if (is_visit[node]) {
    return;
  }
  is_visit[node] = true;
  for (auto next : to[node]) {
    dfs(next);
  }
}

bool is_valid_plan() {
  for (auto node : plan) {
    if (!is_visit[node]) {
      return false;
    }
  }
  return true;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  prepare();
  for (int node = 1; node <= N; node++) {
    memset(is_visit, false, sizeof(is_visit));
    dfs(node);
    if (is_valid_plan()) {
      cout << "YES" << endl;
      return 0;
    }
  }
  cout << "NO" << endl;
  return 0;
}
