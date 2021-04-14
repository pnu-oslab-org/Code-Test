#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>
using namespace std;

#define endl ('\n')
#define MAX_N (11)
#define MAX_ALPHABET ('Z' - 'A' + 1)

#define alphabet second
#define priority first

int N;
string sentences[MAX_N];

pair<uint64_t, char> info[MAX_ALPHABET];
int mapping[MAX_ALPHABET];

void prepare() {
  cin >> N;
  for (int i = 0; i < MAX_ALPHABET; i++) {
    info[i].alphabet = 'A' + i;
    info[i].priority = 0;
  }
  for (int i = 0; i < N; i++) {
    cin >> sentences[i];
    for (size_t j = 0; j < sentences[i].size(); j++) {
      int idx = sentences[i].size() - j - 1;
      char ch = sentences[i][j];
      info[ch - 'A'].priority += pow(10, idx);
    }
  }
  sort(&info[0], &info[MAX_ALPHABET], std::greater<pair<uint64_t, char>>());
  for (int i = 0; i < MAX_ALPHABET; i++) {
    if (info[i].priority == 0) {
      continue;
    }
    mapping[info[i].alphabet - 'A'] = 9 - i;
  }
}

void execute() {
  uint64_t result = 0;
  for (int i = 0; i < N; i++) {
    for (size_t j = 0; j < sentences[i].size(); j++) {
      sentences[i][j] = mapping[sentences[i][j] - 'A'] + '0';
    }
    result += atoi(sentences[i].c_str());
  }
  cout << result << endl;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  prepare();
  execute();
  return 0;
}
