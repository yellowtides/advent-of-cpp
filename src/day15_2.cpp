#include <iostream>
#include <set>
#include <vector>
#include <unordered_map>
#include <queue>
using namespace std;

#define MAX_SIZE 1000
#define INF 2e9

int table[MAX_SIZE][MAX_SIZE];

bool is_oob(int i, int j, int n_rows, int n_cols) {
  return i < 0 || j < 0 || i >= n_rows || j >= n_cols;
}

vector<pair<int, int>> get_neighbours(int i, int j, int n_rows, int n_cols) {
  vector<pair<int, int>> neighbours;
  for (int k = -1; k <= 1; k++) {
    for (int l = -1; l <= 1; l++) {
      // no corners
      if (abs(k + l) != 1) {
        continue;
      }
      if (is_oob(i + k, j + l, n_rows, n_cols)) {
        continue;
      }
      // not out of bounds, so a neighbour!
      neighbours.push_back(make_pair(i + k, j + l));
    }
  }
  return neighbours;
}

bool visited[MAX_SIZE][MAX_SIZE];
int dist[MAX_SIZE][MAX_SIZE];

void dijk(int i, int j, int n_rows, int n_cols) {
  priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, 
                 greater<tuple<int, int, int>>> node_queue;

  // initialise queue
  for (int i = 0; i < n_rows; i++) {
    for (int j = 0; j < n_cols; j++) {
      int score = 0;
      if (i != 0 || j != 0) {
        score = INF;
      }
      dist[i][j] = score;
      node_queue.push(make_tuple(score, i, j));
    }
  }

  // dijk 
  while (!node_queue.empty()) {
    
    // current node: must be minimal in terms of distance, must be unvisited
    auto [score, i_curr, j_curr] =  node_queue.top();
    node_queue.pop();
    if (visited[i_curr][j_curr]) {
      continue;
    }
    visited[i_curr][j_curr] = true;

    vector<pair<int, int>> neighbours = get_neighbours(i_curr, j_curr, n_rows, n_cols); 
    for (auto [i_next, j_next] : neighbours) {

      // only consider unvisited neighbours
      if (visited[i_next][j_next]) {
        continue;
      }

      int next_dist = score + table[i_next][j_next];
      if (next_dist < dist[i_next][j_next]) {
        dist[i_next][j_next] = next_dist;
        node_queue.push(make_tuple(next_dist, i_next, j_next));
      }
    }
  }
}

int main() {

  freopen("./inputs/input_15.txt", "r", stdin);

  string s;
  int n_rows = 0;
  int n_cols;
  while (getline(cin, s)) {
    for (int i = 0; i < s.size(); i++) {
      table[n_rows][i] = s[i] - '0';
    }
    n_rows++;
    n_cols = s.size();
  }
 
  for (int i = 0; i < 5 * n_rows; i++) {
    for (int j = 0; j < 5 * n_cols; j++) {
      table[i][j] = (table[i % n_rows][j % n_rows] - 1 + (i / n_rows) + (j / n_rows)) % 9 + 1;
    }
  }
  n_rows = 5 * n_rows;
  n_cols = 5 * n_cols;

  dijk(0, 0, n_rows, n_cols);

  cout << dist[n_rows-1][n_cols-1];

  return 0;
}
