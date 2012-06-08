// Used: 1276K	250MS
#include <iostream>
#include <vector>
#include <algorithm>
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

const int MAX_N = 20000;

int count[MAX_N+1];
int dist[MAX_N+1];

struct BIT {
  vector<LL> bit;
  BIT(int n) {
    bit = vector<LL>(n+1);
  }
  LL sum(int i) {
    LL res = 0;
    while (i > 0) {
      res += bit[i];
      i -= (i & -i);
    }
    return res;
  }
  LL sum(int i, int j) {
    return sum(j) - sum(i-1);
  }
  void add(int i, LL x) {
    while (i < bit.size()) {
      bit[i] += x;
      i += (i & -i);
    }
  }
};

LL solve(int N, vector<PII>& vx) {
  sort(vx.begin(), vx.end());

  BIT counts(MAX_N);
  BIT dists(MAX_N);

  LL sum = 0;
  for (int i = 0; i < vx.size(); i++) {
    int v = vx[i].first;
    int x = vx[i].second;
    sum += v * (x * counts.sum(1, x-1) - dists.sum(1, x-1));
    sum += v * (dists.sum(x+1, MAX_N) - x * counts.sum(x+1, MAX_N));
    counts.add(x, 1);
    dists.add(x, x);
  }

  return sum;
}

int main() {
  cin.tie(0);
  ios::sync_with_stdio(false);

  int N; cin >> N;
  vector<PII> vx(N);
  REP(i, N) cin >> vx[i].first >> vx[i].second;

  LL ans = solve(N, vx);
  cout << ans << endl;
}
