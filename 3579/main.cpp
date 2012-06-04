// Used: 824K	907MS
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
using namespace std;

typedef vector<int> VI;
typedef vector<VI> VVI;
typedef pair<int, int> PII;
typedef long long LL;
#define REP(i,n) for(int i=0;i<(n);++i)
#define REP_R(i,n) for(int i=(n)-1;i>=0;--i)

#define dump(x) cerr << "  (L" << __LINE__ << ") " << #x << " = " << (x) << endl;
#define dumpv(x) cerr << "  (L" << __LINE__ << ") " << #x << " = "; REP(q,(x).size()) cerr << (x)[q] << " "; cerr << endl;
template<typename T1, typename T2>
ostream& operator<<(ostream& s, const pair<T1, T2>& d) {return s << "(" << d.first << "," << d.second << ")";}

const int MAX_N = 100000;
int N;
int X[MAX_N];

bool C(int m) {
  LL total = (LL)N * (N-1) / 2;

  // count the number of patterns which are no less than m;
  LL num = 0;
  for (int i = 0; i < N; i++) {
    num += (X+N) - lower_bound(X+i+1, X+N, X[i]+m);
  }
  return total - num  <= (total - 1) / 2;
}

int solve() {
  sort(X, X + N);
  int lb = 0, ub = 1000000000;
  while (ub - lb > 1) {
    int mid = (ub + lb) / 2;
    if (C(mid)) lb = mid;
    else ub = mid;
  }
  return lb;
}

int main() {
  while (scanf("%d", &N) != EOF) {
    REP(i, N) scanf("%d", &X[i]);

    int ans = solve();
    printf("%d\n", ans);
  }
}
