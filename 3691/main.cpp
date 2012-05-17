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
#include <cstring>
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

const int INF = 100000000;
const int MAX_N = 50;
const int MAX_STATE = 1010;
const int MAX_LEN_S = 1000;
const string AGCT = "AGCT";

int N;
string S;
string P[MAX_N];

int next[MAX_STATE][4];
bool ng[MAX_STATE];

int dp[MAX_LEN_S+1][MAX_STATE];

int solve() {

  vector<string> prefixes;
  prefixes.push_back("");
  REP(i, N) {
    REP(j, P[i].size()) prefixes.push_back(P[i].substr(0, j+1));
  }
  sort(prefixes.begin(), prefixes.end());
  prefixes.erase(unique(prefixes.begin(), prefixes.end()), prefixes.end());

  int K = prefixes.size();

  fill(ng, ng+K, false);
  REP(i, K) {
    REP(j, N) {
      if (P[j].size() <= prefixes[i].size() && 
          prefixes[i].substr(prefixes[i].size() - P[j].size(), P[j].size()) == P[j]) {
        ng[i] = true;
      }
    }
  }

  REP(i, K) {
    REP(j, 4) {
      string s = prefixes[i] + AGCT[j];
      int k = 0;
      while (true) {
        k = lower_bound(prefixes.begin(), prefixes.end(), s) - prefixes.begin();
        if (k < K && prefixes[k] == s) break;
        s = s.substr(1);
      }
      next[i][j] = k;
    }
  }

  REP(i, S.size()+1) fill(dp[i], dp[i]+K, INF);
  dp[0][0] = 0;
  REP(i, S.size()) {
    REP(j, K) {
      if (ng[j]) continue;
      REP(l, 4) {
        int next_j = next[j][l];
        dp[i+1][next_j] = min(dp[i+1][next_j], 
            dp[i][j] + (S[i] == AGCT[l] ? 0 : 1));
      }
    }
  }

  int ans = INF;
  REP(i, K) {
    if (ng[i]) continue;
    ans = min(ans, dp[S.size()][i]);
  }

  if (ans == INF) {
    return -1;
  } else {
    return ans;
  }
}

int main() {
  int t = 1;
  char buf[1024];
  while (true) {
    scanf("%d", &N);
    if (N == 0) break;

    REP(i, N) {
      scanf("%s", buf);
      P[i] = string(buf);
    }
    scanf("%s", buf);
    S = string(buf);

    int ans = solve();
    printf("Case %d: %d\n", t, ans);

    t++;
  }
}

