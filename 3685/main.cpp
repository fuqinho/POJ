// Used: 724K	688MS
#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;

typedef vector<int> VI;
typedef vector<VI> VVI;
typedef pair<int, int> PII;
typedef long long LL;
#define REP(i,n) for(int i=0;i<(n);++i)
#define REP_R(i,n) for(int i=(n)-1;i>=0;--i)


LL N, M;

int lower_bound(LL j, LL x) {
  int lb = -1, ub = N;
  while (ub - lb > 1) {
    int mid = ((ub + lb) >> 1);
    LL i = mid + 1;
    if (i*i + (100000+j)*i + j*j - 100000*j >= x) {
      ub = mid;
    } else {
      lb = mid;
    }
  }
  return ub;
}

bool C(LL x) {
  LL sum = 0;
  for (int j = 0; j < N; j++) {
    sum += N - lower_bound(j+1, x);
  }
  return sum > N*N-M;
}

LL solve() {
  LL lb = -5000000000, ub = 20000000000;
  while (ub - lb > 1) {
    LL mid = (ub + lb) / 2;
    if (C(mid)) lb = mid;
    else ub = mid;
  }
  return lb;
} 

int main() {
  int T; cin >> T;
  REP(t, T) {
    cin >> N >> M;
    LL ans = solve();
    printf("%lld\n", ans);
  }
}
