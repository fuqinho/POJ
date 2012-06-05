// Used: 788K	16MS
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

#define dump(x) cerr << "  (L" << __LINE__ << ") " << #x << " = " << (x) << endl;
#define dumpv(x) cerr << "  (L" << __LINE__ << ") " << #x << " = "; REP(q,(x).size()) cerr << (x)[q] << " "; cerr << endl;
template<typename T1, typename T2>
ostream& operator<<(ostream& s, const pair<T1, T2>& d) {return s << "(" << d.first << "," << d.second << ")";}

const int MAX_N = 1000;
const double INF = 1000000.0;
double H[MAX_N];

double dfs(int idx) {
  if (H[idx] != INF) return H[idx];

  H[idx] = (H[idx-1] + dfs(idx+1)) / 2 - 1.0;
  return H[idx];
}

double C(int N, double A, double x) {
  H[0] = A;
  H[1] = x;
  for (int i = 2; i < N; i++) {
    H[i] = 2.0 * H[i-1] - H[i-2] + 2.0;
    if (H[i] < 0.0) return false;
  }
  return true;
}


double solve(int N, double A) {
  double lb = 0.0, ub = A;
  while (ub - lb > 1e-9) {
    double mid = (lb + ub) / 2.0;
    if (C(N, A, mid)) ub = mid;
    else lb = mid;
  }
  C(N, A, ub);
  return H[N-1];
}

int main() {
  cin.tie(0);
  ios::sync_with_stdio(false);

  int N; cin >> N;
  double A; cin >> A;

  double ans = solve(N, A);
  printf("%.2f\n", ans);
}
