// Limit: 65536K  1000ms
// Used :   724K    16ms
#include <iostream>
using namespace std;

typedef long long LL;

// return a^b % m
LL mod_pow(LL a, LL b, LL m) {
  LL exp = a;
  LL res = 1;
  while (b) {
    if (b & 1) res = (res * exp) % m;
    exp = (exp * exp) % m;
    b >>= 1;
  }
  return res;
}

bool is_prime(int n) {
  for (int i = 2; i * i <= n; i++) {
    if (n % i == 0) return false;
  }
  return true;
}

int main() {
  cin.tie(0);
  ios::sync_with_stdio(false);

  int p, a;
  while (true) {
    cin >> p >> a;
    if (p == 0 && a == 0) break;

    if (!is_prime(p) && mod_pow(a, p, p) == a) cout << "yes" << endl;
    else cout << "no" << endl;
  }
}
