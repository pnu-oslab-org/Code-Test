#include <iostream>
#include <limits>
#include <vector>
using namespace std;

#define endl ('\n')
#define INF (numeric_limits<int>::max())
#define MAX_SPIN (1001)

enum Dir {
  SOUTH = 0,
  WEST,
  NORTH,
  EAST,
};

enum Rotation {
  CLOCKWISE = -1,
  COUNTER_CLOCKWISE = 1,
};

class Point {
 public:
  int x;
  int y;
};

class SpinInfo {
 public:
  int move_time;
  Rotation rotation;
};

class Line {
 public:
  Point p1, p2;
  Dir dir;
  Line(Point p1, Point p2) {
    if (p1.x == p2.x) {  // vertical line
      dir = SOUTH;
    } else {  // horizontal line
      dir = WEST;
    }

    this->p1 = {min(p1.x, p2.x), min(p1.y, p2.y)};
    this->p2 = {max(p1.x, p2.x), max(p1.y, p2.y)};
  }
};

vector<Line> lines;
Point delta[] = {
    [SOUTH] = {0, 1},
    [WEST] = {-1, 0},
    [NORTH] = {0, -1},
    [EAST] = {1, 0},
};
SpinInfo spin[MAX_SPIN];

int L; /* Board Size = (-L, -L) ~ (L, L) */
int N; /* Number of spinnings */

void prepare() {
  cin >> L >> N;
  for (int i = 0; i < N; i++) {
    int move_time;
    char rotation;
    cin >> move_time >> rotation;

    spin[i].move_time = move_time;
    switch (rotation) {
      case 'L':
        spin[i].rotation = COUNTER_CLOCKWISE;
        break;
      case 'R':
        spin[i].rotation = CLOCKWISE;
        break;
    }
  }
  spin[N] = {INF, CLOCKWISE}; /* For finish to execute */

  /* Initial Boarder Setting */
  lines.push_back(Line({-L - 1, -L - 1}, {L + 1, -L - 1}));  // top
  lines.push_back(Line({-L - 1, -L - 1}, {-L - 1, L + 1}));  // left
  lines.push_back(Line({-L - 1, L + 1}, {L + 1, L + 1}));    // bottom
  lines.push_back(Line({L + 1, -L - 1}, {L + 1, L + 1}));    // right
}

int get_horizontal_max_move_time(int ts, Dir dir, const Line& line,
                                 const Point& current) {
  bool is_bound = true;
  int move_time = 0;
  switch (dir) {
    case SOUTH:
      is_bound &= (current.x == line.p1.x);
      is_bound &= (current.y < line.p1.y);
      move_time = (line.p1.y - current.y);
      break;
    case WEST:
      is_bound &= (line.p1.y <= current.y);
      is_bound &= (current.y <= line.p2.y);
      is_bound &= (line.p1.x < current.x);
      move_time = (current.x - line.p1.x);
      break;
    case NORTH:
      is_bound &= (current.x == line.p1.x);
      is_bound &= (line.p2.y < current.y);
      move_time = (current.y - line.p2.y);
      break;
    case EAST:
      is_bound &= (line.p1.y <= current.y);
      is_bound &= (current.y <= line.p2.y);
      is_bound &= (current.x < line.p1.x);
      move_time = (line.p1.x - current.x);
      break;
  }
  if (is_bound) {
    ts = min(ts, move_time);
  }
  return ts;
}

int get_vertical_max_move_time(int ts, Dir dir, const Line& line,
                               const Point& current) {
  bool is_bound = true;
  int move_time = 0;
  switch (dir) {
    case SOUTH:
      is_bound &= (line.p1.x <= current.x);
      is_bound &= (current.x <= line.p2.x);
      is_bound &= (current.y < line.p1.y);
      move_time = (line.p1.y - current.y);
      break;
    case WEST:
      is_bound &= (current.y == line.p1.y);
      is_bound &= (line.p2.x < current.x);
      move_time = (current.x - line.p2.x);
      break;
    case NORTH:
      is_bound &= (line.p1.x <= current.x);
      is_bound &= (current.x <= line.p2.x);
      is_bound &= (line.p1.y < current.y);
      move_time = (current.y - line.p1.y);
      break;
    case EAST:
      is_bound &= (current.y == line.p1.y);
      is_bound &= (current.x < line.p1.x);
      move_time = (line.p1.x - current.x);
      break;
  }
  if (is_bound) {
    ts = min(ts, move_time);
  }
  return ts;
}

int get_max_move_time(Dir dir, const Point& current) {
  int ts = INF;
  for (const auto& line : lines) {
    if (line.dir == SOUTH) { /* Horizontal Line */
      ts = get_horizontal_max_move_time(ts, dir, line, current);
    } else { /* Vertiacal Line */
      ts = get_vertical_max_move_time(ts, dir, line, current);
    }
  }
  return ts;
}

int execute() {
  Point current = {0, 0};
  Dir dir = EAST;
  int64_t total_move_time = 0;
  for (int i = 0; i <= N; i++) {
    int avail_move_time = get_max_move_time(dir, current);

    /* Check the dead status */
    const bool is_die = (avail_move_time <= spin[i].move_time);
    if (is_die) {
      cout << total_move_time + avail_move_time << endl;
      return 0;
    }

    /* Get next point, direction and add a line */
    total_move_time += spin[i].move_time;
    Point next = {current.x + delta[dir].x * spin[i].move_time,
                  current.y + delta[dir].y * spin[i].move_time};
    dir = static_cast<Dir>((dir + spin[i].rotation + 4) % 4);
    lines.push_back(Line(current, next));
    current = next;
  }
  return 0;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  prepare();
  return execute();
}
