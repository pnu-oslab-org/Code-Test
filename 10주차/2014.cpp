#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

#define endl ('\n')

using namespace std;

int K; // Number of primes
int N; // Target sequence number

// YOU MUST USE THE INT, IF YOU DON'T WANT TO ENCOUNTER THE MEMORY LEAKAGE
priority_queue<int, vector<int>, greater<int>> pq;
vector<int> primes;

void prepare() {
  int temp;
  cin >> K >> N;
  for (int i = 0; i < K; i++) {
    cin >> temp;
    pq.push(temp);
    primes.push_back(temp);
  }
}

void multiplications(int64_t current) {
  for (const auto &prime : primes) {
    // HOWEVER, MULTIPLICATION MUST USE THE INT64_T NOT UINT64_T
    if (current * prime >= ((int64_t)1 << 31)) {
      continue;
    } // Except the value which contains over 2^31
    pq.push(current * prime);
  }
}

void same_case_remove(int64_t current) {
  while (current == pq.top()) {
    pq.pop();
  }
}

void execute() {
  int64_t current = 0;
  for (int sequence = 0; sequence < N - 1; sequence++) {
    current = pq.top();
    multiplications(current);
    same_case_remove(current);
  }
  cout << pq.top() << endl;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  prepare();
  execute();
  return 0;
}
