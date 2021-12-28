#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

#define INF 2e9
#define MAX_VEL 500

typedef pair<int, int> interval;

int get_x(int v1, int step) {
  if (step < v1 - 1) {
    return step * v1 - (step - 1) * step / 2;
  }
  return v1 * (v1 + 1) / 2;
}

int get_y(int v2, int step) {
  return step * v2 - (step - 1) * step / 2;
}

bool line_contains(interval line, int x) {
  return line.first <= x && x <= line.second;
}

bool square_contains(pair<interval, interval> square, int x, int y) {
  return line_contains(square.first, x) && line_contains(square.second, y);
}

int simulate(int v1, int v2, pair<interval, interval> square) {

  // max x value
  if (v1 * (v1 + 1) / 2 < square.first.first) {
    // -INF = simulation doesn't hit square
    return -INF;
  }
  
  int best_y = -INF;
  bool valid = false;
 
  int step = 0, x = 0, y = 0;
  while (x <= square.first.second && y >= square.second.first) { 
    x = get_x(v1, step);
    y = get_y(v2, step);
    best_y = max(best_y, y);
    if (square_contains(square, x, y)) {
      valid = true;
    }
    step++;
  }

  if (valid) {
    return best_y;
  }

  return -INF;
}

int main() {
  
  freopen("./inputs/input_17.txt", "r", stdin);

  int x_st, x_en, y_st, y_en;
  scanf("target area: x=%d..%d, y=%d..%d", &x_st, &x_en, &y_st, &y_en);

  pair<interval, interval> square = make_pair(make_pair(x_st, x_en), make_pair(y_st, y_en));

  int valid_velocities = 0; 

  for (int v1 = 0; v1 < MAX_VEL; v1++) {
    for (int v2 = -MAX_VEL; v2 < MAX_VEL; v2++) {
      if (simulate(v1, v2, square) != -INF) {
        valid_velocities++;
      }
    }
  }

  cout << valid_velocities;

  return 0;
}
