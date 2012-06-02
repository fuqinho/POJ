// Limit: 30000K  1000ms
// Used :   732K     0ms
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long LL;
const LL INF = 1e18;

LL get_gcd(LL a, LL b) {
  if (a < b) swap(a, b);
  while (b) {
    swap(a, b);
    b %= a;
  }
  return a;
}

pair<LL, LL> solve(vector<int>& digits) {
  // pair<{denominator}, {numerator}>
  pair<LL, LL> ans = make_pair(INF, INF);
  for (int rep = 1; rep <= digits.size(); rep++) {
    // calc fraction for non-repeated part
    LL deno1 = 1;
    LL nume1 = 0;
    for (int i = 0; i < digits.size()-rep; i++) {
      nume1 *= 10;
      deno1 *= 10;
      nume1 += digits[i];
    }

    // calc fraction for repeated part
    LL deno2 = 1;
    LL nume2 = 0;
    for (int i = digits.size()-rep; i < digits.size(); i++) {
      nume2 *= 10;
      deno2 *= 10;
      nume2 += digits[i];
    }
    deno2 = deno1 * (deno2-1);

    // reduction
    LL nume = nume1 * deno2 + nume2 * deno1;
    LL deno = deno1 * deno2;
    pair<LL, LL> res = make_pair(deno / get_gcd(nume, deno), nume / get_gcd(nume, deno));

    ans = min(ans, res);
  }
  return ans;
}

int main() {
  cin.tie(0);
  ios::sync_with_stdio(false);

  string s;
  while (true) {
    cin >> s;
    if (s == "0") break;

    vector<int> digit;
    for (int i = 2; ; i++) {
      if (s[i] == '.') break;
      digit.push_back(s[i] - '0');
    }

    pair<LL, LL> ans = solve(digit);
    cout << ans.second << "/" << ans.first << endl;
  }
}
