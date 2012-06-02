// Limit: 65536K  1000ms
// Used :   748K    94ms
#include <iostream>
#include <vector>
#include <map>
using namespace std;

typedef long long LL;
typedef pair<int, int> PII;
const int MAX_PRIME = 1 << 20;
vector<int> primes;

map<int, int> prime_factor(int n) {
  map<int, int> res;
  for (int i = 2; i * i <= n; i++) {
    while (n % i == 0) {
      ++res[i];
      n /= i;
    }
  }
  if (n != 1) res[n] = 1;
  return res;
}

LL get_gcd(LL a, LL b) {
  if (a < b) swap(a, b);
  while (b) {
    swap(a, b);
    b %= a;
  }
  return a;
}

PII solve(int n) {
  map<int, int> factors = prime_factor(n);

  int facnum = 0;
  for (map<int, int>::iterator it = factors.begin(); it != factors.end(); it++) {
    facnum += it->second;
  }

  LL deno = 1, nume = 1;
  int curn = facnum;
  for (map<int, int>::iterator it = factors.begin(); it != factors.end(); it++) {
    for (int i = it->second; i >= 1; i--) {
      nume *= curn;
      curn --;
      deno *= i;
      int gcd = get_gcd(deno, nume);
      deno /= gcd;
      nume /= gcd;
    }
  }
  return PII(facnum, nume);
}

int main() {
  cin.tie(0);
  ios::sync_with_stdio(false);

  int n;
  while (cin >> n) {
    PII ans = solve(n);
    cout << ans.first << " " << ans.second << endl;
  }
}
