#include <iostream>
#include <vector>
#include <cstring>
#include <unordered_set>
#include <unordered_map>
using namespace std;

#define MAX_NODES 100
#define MAX_LEN 100

#define SMALL 0
#define BIG 1
#define START 2
#define END 3

vector<int> graph[MAX_NODES];
int type[MAX_NODES];
int n_nodes = 0;

unordered_map<string, int> label;

pair<string, string> parse(string s) {
  string left, right;
  int i = 0;
  for (; i < s.size(); i++) {
    if (s[i] == '-') {
      break;
    }
    left.push_back(s[i]);
  }
  for (i = i+1; i < s.size(); i++) {
    right.push_back(s[i]);
  }
  return make_pair(left, right);
}

int identify_type(string node) {
  if (node == "start") {
    return START;
  }
  if (node == "end") {
    return END;
  }
  if (islower(node[0])) {
    return SMALL;
  }
  return BIG;
}

int get_label(string node) {
  if (label.find(node) != label.end()) {
    return label[node];
  }
  type[n_nodes] = identify_type(node);
  label[node] = n_nodes++;
  return n_nodes-1;
}

void dfs(int &accum, int node, unordered_set<int> visited) {
  if (type[node] == END) {                                  // end of path
    accum++;
    return;
  }
  if (visited.find(node) != visited.end() 
      && (type[node] == START || type[node] == SMALL)) {   // invalid path
    return;
  }
  // valid path, non-ending.
  visited.insert(node);
  for (int next : graph[node]) {
    unordered_set<int> copy(visited);
    dfs(accum, next, copy);
  }
  return;
}

int main() {

  freopen("./inputs/input_12.txt", "r", stdin);

  string s;

  while (getline(cin, s)) {
    pair<string, string> parsed_str = parse(s);
    string st = parsed_str.first;
    string en = parsed_str.second;
    graph[get_label(st)].push_back(get_label(en));
    graph[get_label(en)].push_back(get_label(st));
  }
  
  int result = 0;
  unordered_set<int> visited;
  dfs(result, get_label("start"), visited);

  cout << result;

  return 0;
}
