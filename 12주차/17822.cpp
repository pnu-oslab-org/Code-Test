#include <cstring>
#include <iostream>

using namespace std;

#define CLOCK_WISE (0)

#define MAX_N (51)
#define MAX_M (51)
#define NONE (0)
#define endl ('\n')

#define do_garbage_collection() \
  do {                          \
    garbage[plane][pos] = 1;    \
    is_collected = 1;           \
  } while (0)

int N, M;

int circle[MAX_N][MAX_M];
int garbage[MAX_N][MAX_M];
int total[MAX_N];
int valid[MAX_N];

void rotate_circle(int plane, int direction, int move) {
  static int buffer[MAX_M];
  for (int pos = 0; pos < M; pos++) {
    if (direction == CLOCK_WISE) {
      buffer[(pos + move) % M] = circle[plane][pos];
    } else {
      buffer[pos] = circle[plane][(pos + move) % M];
    }
  }
  memcpy(circle[plane], buffer, sizeof(buffer));
}

int garbage_collect(int plane) {
  int is_collected = 0;
  for (int pos = 0; pos < M; pos++) {
    int right = (pos + 1) % M;
    int left = pos - 1 < 0 ? M - 1 : pos - 1;
    int up = plane + 1, down = plane - 1;
    if (circle[plane][pos] == 0) {
      continue;
    }
    if (circle[plane][pos] == circle[plane][left]) {
      do_garbage_collection();
    } else if (circle[plane][pos] == circle[plane][right]) {
      do_garbage_collection();
    } else if (down >= 0 && circle[plane][pos] == circle[down][pos]) {
      do_garbage_collection();
    } else if (up < N && circle[plane][pos] == circle[up][pos]) {
      do_garbage_collection();
    } else {
      total[plane] += circle[plane][pos];
      valid[plane]++;
    }
  }
  return is_collected;
}

void update_no_gc_circle(int plane, int sum, int counter) {
  total[plane] = 0;
  for (int pos = 0; pos < M; pos++) {
    if (garbage[plane][pos] || circle[plane][pos] == 0) {
      continue;
    }

    if (circle[plane][pos] * counter > sum) {
      circle[plane][pos]--;
    } else if (circle[plane][pos] * counter < sum) {
      circle[plane][pos]++;
    }
    total[plane] += circle[plane][pos];
  }
}

void traverse_circle(int x, int d, int k) {
  int is_gc = 0;
  int sum = 0;
  int counter = 0;
  for (int base = 1; base * x <= N; base++) {
    rotate_circle(base * x - 1, d, k);
  }

  memset(garbage, 0, sizeof(garbage));
  for (int plane = 0; plane < N; plane++) {
    total[plane] = 0;
    valid[plane] = 0;
    is_gc |= garbage_collect(plane);
    sum += total[plane];
    counter += valid[plane];
  }

  for (int plane = 0; plane < N; plane++) {
    for (int pos = 0; pos < M; pos++) {
      if (garbage[plane][pos] == 1) {
        circle[plane][pos] = NONE;
      }
    }
  }

  if (!is_gc && counter > 0) {
    for (int plane = 0; plane < N; plane++) {
      if (valid[plane]) {
        update_no_gc_circle(plane, sum, counter);
      }
    }
  }
}

int main(void) {
  int T;
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> N >> M >> T;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      cin >> circle[i][j];
    }
  }
  for (int i = 0; i < T; i++) {
    int x, d, k;
    cin >> x >> d >> k;
    traverse_circle(x, d, k);
  }

  int result = 0;
  for (int i = 0; i < N; i++) {
    result += total[i];
  }
  cout << result << endl;
  return 0;
}
