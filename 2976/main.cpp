// Used: 748K	125MS
#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
using namespace std;

typedef vector<int> VI;
typedef vector<VI> VVI;
typedef pair<int, int> PII;
typedef long long LL;
#define REP(i,n) for(int i=0;i<(n);++i)
#define REP_R(i,n) for(int i=(n)-1;i>=0;--i)

bool C(int k, VI& a, VI& b, int x) {
  vector<LL> c(a.size());
  REP(i, a.size()) {
    c[i] = 200LL * a[i] - (x != 0 ? 2LL * x - 1 : 0LL) * b[i];
  }
  sort(c.rbegin(), c.rend());
  
  int used_n = a.size() - k;
  LL sum = accumulate(c.begin(), c.begin() + used_n, 0LL);
  
  return sum >= 0;
}

int solve(int k, VI& a, VI& b) {
  int lb = 0, ub = 101;
  while (ub - lb > 1) {
    int mid = (lb + ub) / 2;
    if (C(k, a, b, mid)) lb = mid;
    else ub = mid;
  }
  return lb;
}

int main() {
  cin.tie(0);
  ios::sync_with_stdio(false);

  while (true) {
    int n, k; cin >> n >> k;
    if (n == 0 && k == 0) break;

    VI a(n), b(n);
    REP(i, n) cin >> a[i];
    REP(i, n) cin >> b[i];

    int ans = solve(k, a, b);
    cout << ans << endl;
  }
}
