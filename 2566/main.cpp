// Used: 2692K	250MS
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

const int INF = 2000000000;

vector<PII> p;
int min_dist;

void check(pair<int, PII>& ans, int s, int t, int T) {
  if (t > s) {
    int diff = p[t].first - p[s].first;
    if (abs(diff - T) < min_dist) {
      min_dist = abs(diff - T); 
      ans = make_pair(diff, PII(min(p[s].second, p[t].second) + 1, max(p[s].second, p[t].second)));
    }
  }
}

void solve(VI& V, int T) {
  pair<int, PII> ans(INF, PII(0, 0));

  /*
  int min_dist = INF;

  int s = 0, t = 1;
  while (t < p.size()) {
    int diff = p[t].first - p[s].first;
    if (abs(diff - T) < min_dist) {
      min_dist = abs(diff - T);
      ans = make_pair(diff, PII(min(p[s].second, p[t].second) + 1, max(p[s].second, p[t].second)));
    }
    //check(ans, s, t, T);

    if (diff == T) break;
    if (diff < T) t++;
    if (diff > T) s++;
    if (s == t) t++;
  }
  */
  min_dist = INF;
  int s = 0, t = 1;
  for (;;) {
    while (t < p.size() && p[t].first - p[s].first < T) t++;
    if (t == p.size()) {
      check(ans, s, t-1, T);
      break;
    }
    check(ans, s, t-1, T);
    check(ans, s, t, T);
    s++;
    if (s == t) t++;
  }

  cout << ans.first << " " << ans.second.first << " " << ans.second.second << endl;
}

void init(VI& V) {
  int sum = 0;
  p = vector<PII>(V.size() + 1);
  p[0] = PII(0, 0);
  REP(i, V.size()) {
    sum += V[i];
    p[i+1] = PII(sum, i+1);
  }
  sort(p.begin(), p.end());
}

int main() {
  cin.tie(0);
  ios::sync_with_stdio(false);

  int n, k;
  while (true) {
    cin >> n >> k;
    if (n == 0 && k == 0) break;

    VI v(n); REP(i, n) cin >> v[i];
    VI q(k); REP(i, k) cin >> q[i];
  
    init(v);
    REP(i, k) {
      int t = q[i];
      solve(v, t);
    }
  }
}
