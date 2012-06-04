// Used: 1672K	375MS
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

typedef vector<int> VI;
typedef vector<VI> VVI;
typedef pair<int, int> PII;
typedef long long LL;
#define ALL(a)  (a).begin(),(a).end()
#define REP(i,n) for(int i=0;i<(n);++i)
#define REP_R(i,n) for(int i=(n)-1;i>=0;--i)


int solve(int N, VI& W, VI& S) {
  vector<pair<int, PII> > ttl(N);
  REP(i, N) ttl[i] = make_pair(W[i]+S[i], PII(W[i], S[i]));
  sort(ALL(ttl));
  reverse(ALL(ttl));

  int total_w = accumulate(ALL(W), 0);

  int max_risk = -1000000001;
  REP(i, N) {
    total_w -= ttl[i].second.first;
    int risk = total_w - ttl[i].second.second;
    max_risk = max(max_risk, risk);
  }
  return max_risk;
}

int main() {
  cin.tie(0);
  ios::sync_with_stdio(false);

  int N; cin >> N;
  VI W(N), S(N);
  REP(i, N) cin >> W[i] >> S[i];

  int ans = solve(N, W, S);
  cout << ans << endl;
}
