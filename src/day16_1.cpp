#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

#define LITERAL 4

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

int parse_literal_body(string packet, int &i) {
  int cont_read;
  int val = 0;
  do {
    cont_read = decode_part(packet, i, 1);
    val = val * 16 + decode_part(packet, i, 4);
  } while (cont_read);

  return val;
}

int parse(string &packet, int &i, int &ver_sum) {
  int len_offset = i; 

  ver_sum += decode_part(packet, i, 3);
  int type = decode_part(packet, i, 3);

  int parsed_val;
  switch (type) {
    
    case LITERAL:
      parsed_val = parse_literal_body(packet, i);
      break;

    default:    // operator
      int mode = decode_part(packet, i, 1);
      switch (mode) {
        case 0: {
          int subpackets_len = decode_part(packet, i, 15);
          while (subpackets_len) {
            subpackets_len -= parse(packet, i, ver_sum);
          }
          break;
        }
        case 1: {
          int subpacket_count = decode_part(packet, i, 11);
          for (int p = 0; p < subpacket_count; p++) {
            parse(packet, i, ver_sum);
          }
          break;
        }
      }
  }
  return i - len_offset;
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
  parse(packet, i, ver_sum);

  cout << ver_sum;

  return 0;
}
