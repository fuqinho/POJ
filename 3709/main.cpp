#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <algorithm>
#include <cstdio>
#include <cmath>
using namespace std;

typedef vector<int> VI;
typedef vector<VI> VVI;
typedef vector<string> VS;
typedef pair<int, int> PII;
typedef long long LL;
#define ALL(a)  (a).begin(),(a).end()
#define REP(i,n) for(int i=0;i<(n);++i)
const double EPS = 1e-10;
const double PI  = acos(-1.0);
#define dump(x) cerr << "  (L" << __LINE__ << ") " << #x << " = " << (x) << endl;
#define dumpv(x) cerr << "  (L" << __LINE__ << ") " << #x << " = "; REP(q,(x).size()) cerr << (x)[q] << " "; cerr << endl;
template<typename T1, typename T2>
ostream& operator<<(ostream& s, const pair<T1, T2>& d) {return s << "(" << d.first << "," << d.second << ")";}

const int MAX_N = 500000;
const LL INF = 100000000000000;
vector<LL> dp;
vector<LL> S;
vector<LL> a;

// 直線f_jのxにおける値
LL f(int j, int x) {
  return -a[j] * x + dp[j] - S[j] + a[j] * j;
}

// f2が最小値を取る可能性があるかどうか判定する
bool check(int f1, int f2, int f3) {
  LL a1 = -a[f1];
  LL b1 = dp[f1] - S[f1] + a[f1] * f1;
  LL a2 = -a[f2];
  LL b2 = dp[f2] - S[f2] + a[f2] * f2;
  LL a3 = -a[f3];
  LL b3 = dp[f3] - S[f3] + a[f3] * f3;
  return (a2 - a1) * (b3 - b2) >= (b2 - b1) * (a3 - a2);
}

LL solve(int n, int k) {
  dp = vector<LL>(n+1, INF);
  dp[0] = 0;
  S = vector<LL>(n+1);

  // 和の計算
  S[0] = 0;
  REP(i, n) {
    S[i+1] = S[i] + a[i];
  }

  // デックの初期化
  // deq[s]が先頭、deq[t-1]が末尾、t-sが要素数
  static int deq[MAX_N];
  int s = 0, t = 0;
  deq[t++] = 0;

  for (int i = k; i <= n; i++) {
    if (i - k >= k) {
      // 末尾から最小値を取る可能性がなくなったものを取り除く
      while (t-s >= 2 && check(deq[t-2], deq[t-1], i-k)) t--;
      
      // デックにi-kを追加
      deq[t++] = i-k;
    }

    // 先頭が最小値で無ければ取り除く
    while (t-s >= 2 && f(deq[s], i) >= f(deq[s+1], i)) s++;

    // dp更新
    int j = deq[s];
    dp[i] = S[i] + f(j, i);
  }
  
  return dp[n];
}

int main() {
  int T; scanf("%d", &T);
  REP(t, T) {
    int n, k; scanf("%d %d", &n, &k);
    a = vector<LL>(n);
    REP(i, n) scanf("%d", &a[i]);

    LL ans = solve(n, k);
    cout << ans << endl;
  }
}

