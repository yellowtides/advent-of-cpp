#include <iostream>
using namespace std;

#define MAX_SIZE 1000
#define THRESHHOLD 10

bool flashed[MAX_SIZE][MAX_SIZE];
int table[MAX_SIZE][MAX_SIZE];

void reset_flashes() {
  memset(flashed, 0, sizeof(flashed));
}

void handle_increase(int &counter, int i, int j, int n_rows, int n_cols) {
  if (flashed[i][j]) {
    return;
  }
  table[i][j]++;
  if (table[i][j] >= THRESHHOLD) {
    counter++;
    flashed[i][j] = 1;
    table[i][j] = 0;
    for (int row_index = max(0, i - 1); row_index <= min(n_rows - 1, i + 1); row_index++) {
      for (int col_index = max(0, j - 1); col_index <= min(n_cols - 1, j + 1); col_index++) {
        handle_increase(counter, row_index, col_index, n_rows, n_cols);
      }
    }
  }
}

int main() {

  freopen("./inputs/input_11.txt", "r", stdin);
  
  string s;
  int n_rows = 0;
  while (getline(cin, s)) {
    for (int i = 0; i < s.size(); i++) {
      table[n_rows][i] = s[i] - '0';
    }
    n_rows++;
  }
  int n_cols = n_rows;

  int counter = 0;
  int step = 0;

  do {
    step++;
    reset_flashes();
    counter = 0;
    for (int i = 0; i < n_rows; i++) {
      for (int j = 0; j < n_cols; j++) {
          handle_increase(counter, i, j, n_rows, n_cols);
      }
    }
  } while (counter != n_rows * n_cols);

  cout << step;

  return 0;
}
