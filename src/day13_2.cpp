#include <iostream>
#include <set>
#include <vector>
using namespace std;

void fold_along_x(set<pair<int, int>> &coords, int x0) {
  set<pair<int, int>> new_coords;
  for (pair<int, int> xy : coords) {
    auto [x, y] = xy;
    if (x < x0) {
      new_coords.insert(xy);
      continue;
    }
    if (2*x0 >= x) {
      new_coords.insert(make_pair(2*x0 - x, y));
    }
  }
  coords = new_coords;
}

void fold_along_y(set<pair<int, int>> &coords, int y0) {
  set<pair<int, int>> new_coords;
  for (pair<int, int> xy : coords) {
    auto [x, y] = xy;
    if (y < y0) {
      new_coords.insert(xy);
      continue;
    }
    if (2*y0 >= y) {
      new_coords.insert(make_pair(x, 2*y0 - y));
    }
  }
  coords = new_coords;
}

void print_image(set<pair<int, int>> &coords) {
  const int IMG_WIDTH = 50;
  const int IMG_LEN = 10;
  for (int i = 0; i < IMG_LEN; i++) {
    for (int j = 0; j < IMG_WIDTH; j++) {
      if (coords.find(make_pair(j, i)) != coords.end()) {
        cout << '@';
      }
      else {
        cout << '.';
      }
    }
    cout << endl;
  }
} 

int main() {

  freopen("./inputs/input_13.txt", "r", stdin);

  int x, y;
  set<pair<int, int>> coords;
  while (scanf("%d,%d\n", &x, &y)) {
    coords.insert(make_pair(x, y));
  }
  
  char c;
  int val;
  while (scanf("fold along %c=%d\n", &c, &val) != EOF) {
    if (c == 'y') {
      fold_along_y(coords, val);
    }
    else {
      fold_along_x(coords, val);
    }
  }
  
  print_image(coords);

  return 0;
}
