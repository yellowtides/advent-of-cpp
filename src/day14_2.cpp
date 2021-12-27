#include <iostream>
#include <set>
#include <vector>
#include <unordered_map>
using namespace std;

typedef long long ll;

#define MAX_NODES 100

int n_nodes = 0;
vector<string> graph[MAX_NODES];
unordered_map<string, int> label;
ll freq[256];

int get_label(string node) {
  if (label.find(node) != label.end()) {
    return label[node];
  }
  label[node] = n_nodes++;
  return n_nodes-1;
}

void evolve(unordered_map<int, ll> &node_counts) {
  unordered_map<int, ll> new_node_counts;
  for (auto [node, count] : node_counts) {
    if (graph[node].size() == 0) {
      new_node_counts[node] += count;
      continue;
    }
    freq[graph[node][0][1]] += count;
    for (string next : graph[node]) {
      new_node_counts[get_label(next)] += count;
    }
  }
  node_counts = new_node_counts;
}

int main() {

  freopen("./inputs/input_14.txt", "r", stdin);

  string initial;
  cin >> initial;

  string s;
  while (getline(cin, s)) {
    if (s.size() == 0) {
      continue;
    }
    string st;
    st.push_back(s[0]);
    st.push_back(s[1]);
    string fi1, fi2;
    fi1.push_back(s[0]);
    fi1.push_back(s[s.size()-1]);
    fi2.push_back(s[s.size()-1]);
    fi2.push_back(s[1]);
    graph[get_label(st)].push_back(fi1);
    graph[get_label(st)].push_back(fi2);
  }

  unordered_map<int, ll> node_counts;
  for (int i = 0; i < initial.size() - 1; i++) {
    freq[initial[i]]++;
    string node;
    node.push_back(initial[i]);
    node.push_back(initial[i+1]);
    node_counts[get_label(node)]++;
  }
  freq[initial[initial.size()-1]]++;

  int n_steps = 40;
  for (int i = 0; i < n_steps; i++) {
    evolve(node_counts);
  }

  ll mini = 1e18;
  ll maxi = -1;
  for (int i = 'A'; i <= 'Z'; i++) {
    if (freq[i] > 0) {
      mini = min(freq[i], mini);
      maxi = max(freq[i], maxi);
    }
  }

  cout << maxi - mini;

  return 0;
}
