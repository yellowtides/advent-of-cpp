#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

typedef long long ll;

#define LITERAL 4

#define SUM 0
#define PROD 1
#define MIN 2
#define MAX 3
#define GT 5
#define LT 6
#define EQ 7

#define INF 2e18

string to_bin(char c) {
  int int_form;
  if (c >= '0' and c <= '9') {
    int_form = c - '0';
  }
  else {
    int_form = tolower(c) - 'a' + 10;
  }
  string bin_form;
  while (int_form) {
    bin_form.push_back((int_form % 2) + '0');
    int_form /= 2;
  }
  for (int i = bin_form.size(); i < 4; i++) {
    bin_form.push_back('0');
  }
  reverse(bin_form.begin(), bin_form.end());
  return bin_form;
}

int decode_part(string &s, int &st, int len) {
  int code = 0;
  int en = st + len;
  for (; st < en; st++) {
    code = code * 2 + s[st] - '0';
  }
  return code;
}

ll parse_literal_body(string packet, int &i) {
  int cont_read;
  ll val = 0;
  do {
    cont_read = decode_part(packet, i, 1);
    val = val * 16 + decode_part(packet, i, 4);
  } while (cont_read);

  return val;
}

ll perform_op(vector<ll> literals, int op) {
  ll res;
  switch (op) {
    case SUM:
      res = 0;
      for (ll x : literals) {
        res += x;
      }
      return res;
    case PROD:
      res = 1;
      for (ll x : literals) {
        res *= x;
      }
      return res;
    case MIN:
      res = INF;
      for (ll x : literals) {
        res = min(res, x);
      }
      return res;
    case MAX:
      res = -INF;
      for (ll x : literals) {
        res = max(res, x);
      }
      return res;
    case GT:
      return literals[0] > literals[1];
    case LT:
      return literals[0] < literals[1];
    case EQ:
      return literals[0] == literals[1];
  }

  // invalid op
  return -INF;
}

// length of packet, value of packet
pair<int, ll> parse(string &packet, int &i, int &ver_sum) {
  int len_offset = i; 
  ll value = 0;

  ver_sum += decode_part(packet, i, 3);
  int type = decode_part(packet, i, 3);

  switch (type) {
    
    case LITERAL:
      value = parse_literal_body(packet, i);
      break;

    default:    // operator
      int mode = decode_part(packet, i, 1);
      vector<ll> literals;
      switch (mode) {
        case 0: {
          int subpackets_len = decode_part(packet, i, 15);
          while (subpackets_len) {
            auto [s_len, s_val] = parse(packet, i, ver_sum);
            subpackets_len -= s_len;
            literals.push_back(s_val); 
          }
          break;
        }
        case 1: {
          int subpacket_count = decode_part(packet, i, 11);
          for (int p = 0; p < subpacket_count; p++) {
            auto [s_len, s_val] = parse(packet, i, ver_sum);
            literals.push_back(s_val);
          }
          break;
        }
      }

      value = perform_op(literals, type); 
      break;
  }
  return make_pair(i - len_offset, value);
}

int main() {
  
  freopen("./inputs/input_16.txt", "r", stdin);
  
  string packet_hex;
  cin >> packet_hex;
  
  string packet;
  for (char hex_ch : packet_hex) { 
    packet.append(to_bin(hex_ch));
  }

  int ver_sum = 0, i = 0;
  cout << parse(packet, i, ver_sum).second;

  return 0;
}
