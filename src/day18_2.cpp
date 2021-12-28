#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

#define EXPLODE_THRESH 5
#define SPLIT_THRESH 10
#define INF 2e18

typedef long long ll;

// value, level
typedef vector<pair<ll, int>> snailfish_t;

bool split(snailfish_t &s) {
  for (int i = 0; i < s.size(); i++) {
    if (s[i].first >= SPLIT_THRESH) {
      // slice!
      auto [sliced_val, sliced_level] = s[i];
      s[i].first = sliced_val / 2;
      s[i].second = sliced_level + 1;
      s.insert(s.begin() + i + 1, make_pair((sliced_val + 1) / 2, sliced_level + 1));
        return true;
    }
  }
  return false;
}


// note to self: use structs next time; compare:
// s[i].level++;    vs    s[i].second++;
bool explode(snailfish_t &s) {
  for (int i = 0; i < s.size(); i++) {
    if (s[i].second >= EXPLODE_THRESH) {
      // boom!
      if (i+2 < s.size()) {
        s[i+2].first += s[i+1].first;
      }
      if (i-1 >= 0) {
        s[i-1].first += s[i].first;
      }
      s.erase(s.begin() + i + 1);
      // destroy pair, reset value 
      s[i].second--;
      s[i].first = 0;
      return true;
    }
  }
  return false;
}


void reduce(snailfish_t &s) {
  if (explode(s)) {
    reduce(s);
  }
  if (split(s)) {
    reduce(s);
  }
}

void add(snailfish_t &s1, snailfish_t &s2) {
  // neutral element
  if (s1.size() == 0) {
    s1 = s2;
    return;
  }

  // s1 := s1 + s2
  for (auto val_level : s2) {
    s1.push_back(val_level);
  }

  // increment all levels
  for (int i = 0; i < s1.size(); i++) {
    s1[i].second++;
  }
}

void full_add(snailfish_t &s1, snailfish_t &s2) {
  add(s1, s2);
  reduce(s1);
}

snailfish_t parse(string snail_str) {
  snailfish_t sf;
  int level = 0;
  for (char c : snail_str) {
    if (c == '[') {
      level++;
    }
    if (c == ']') {
      level--;
    }
    if (isdigit(c)) {
      sf.push_back(make_pair(c - '0', level));
    }
  }
  return sf;
}

ll snail_hash(snailfish_t sf) {

  if (sf.size() == 1) {
    return sf[0].first;
  }
  
  int max_level = max_element(sf.begin(), sf.end(), 
      [](pair<ll, int> el1, pair<ll, int> el2) {
        return el1.second < el2.second;
      }) - sf.begin();
  
  sf[max_level].first = 3 * sf[max_level].first + 2 * sf[max_level+1].first;
  sf[max_level].second--;
  sf.erase(sf.begin() + max_level + 1);

  return snail_hash(sf);
}

int main() {
  
  freopen("./inputs/input_18.txt", "r", stdin);

  vector<snailfish_t> sfs;
  string snail_str;
 
  while (getline(cin, snail_str)) {
    sfs.push_back(parse(snail_str));
  }

  ll best_hash = -INF;

  for (int i = 0; i < sfs.size(); i++) {
    for (int j = 0; j < sfs.size(); j++) {
      if (i == j) {
        // must be different sailfish
        continue;
      }
      snailfish_t sf1 = sfs[i];
      snailfish_t sf2 = sfs[j];
      full_add(sf1, sf2);
      best_hash = max(best_hash, snail_hash(sf1));
    } 
  }
 
  cout << best_hash;

  return 0;
}
