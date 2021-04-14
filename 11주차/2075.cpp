#include <algorithm>
#include <iostream>

using namespace std;

#define endl ('\n')
#define MAX_N (1501)

int N;
int memory[MAX_N * MAX_N];

void prepare() {
  cin >> N;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      cin >> memory[(i * N) + j];
    }
  }
  sort(&memory[0], &memory[N * N], std::greater<int>());
}

void execute() { cout << memory[N - 1] << endl; }

int main(void) {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
  prepare();
  execute();
  return 0;
}
