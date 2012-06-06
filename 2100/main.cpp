// Used: 736K	2500MS
#include <iostream>
#include <vector>
#include <cmath>
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


int main() {
  cin.tie(0);
  ios::sync_with_stdio(false);

  LL n; cin >> n;

  int max_t = (int)sqrt(n) + 2;

  vector<PII> ans;

  int s=1, t=1;
  LL sum = 0;
  for (;;) {
    while (t < max_t && sum < n) {
      sum += (LL)t * t;
      t++;
    }
    if (sum < n) break;
    if (sum == n) ans.push_back(PII(s, t-1));
    sum -= (LL)s * s;
    s ++;
  }


  cout << ans.size() << endl;
  REP(i, ans.size()) {
    cout << ans[i].second - ans[i].first + 1 << " ";
    for (int j = ans[i].first; j <= ans[i].second; j++) cout << j << " ";
    cout << endl;
  }

}
