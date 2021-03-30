#include <iostream>
#include <queue>
#include <vector>

using namespace std;

#define endl ('\n')
#define MAX_N (1001)

// If you want to use the greater<>(), must follow the below manner
#define weight first
#define vertex second

typedef pair<int, int> point;

vector<point> graph[MAX_N];
priority_queue<int> heap[MAX_N];
priority_queue<point, vector<point>, greater<> > pq;
int N, M, K;  // Vertex, Edge, K-th shortest

void dijkstra() {
  int weight = 0;
  int vertex = 1;

  pq.push({weight, vertex});
  heap[vertex].push(weight);

  while (pq.size()) {
    int weight = pq.top().weight;
    int source = pq.top().vertex;

    pq.pop();

    for (auto item : graph[source]) {
      int next_vertex = item.vertex;
      int next_weight = item.weight + weight;

      if (heap[next_vertex].size() < K) {
        heap[next_vertex].push(next_weight);
        pq.push({next_weight, next_vertex});
      } else if (heap[next_vertex].top() > next_weight) {
        heap[next_vertex].pop();
        heap[next_vertex].push(next_weight);
        pq.push({next_weight, next_vertex});
      }  // end-of-if
    }    // end-of-for
  }      // end-of-while
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> N >> M >> K;

  for (int i = 0; i < M; i++) {
    int source, destination, weight;
    cin >> source >> destination >> weight;
    // [NOTE] You must follow the same sequnece of the pq
    graph[source].push_back({weight, destination});
  }

  dijkstra();

  for (int i = 1; i <= N; i++) {
    if (heap[i].size() != K) {
      cout << "-1" << endl;
    } else {
      cout << heap[i].top() << endl;
    }  // end-of-if
  }    // end-of-for
  return 0;
}
