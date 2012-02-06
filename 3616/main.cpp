#include <iostream>
#include <sstream>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <iomanip>
#include <cmath>
#include <string>
#include <cstdio>
using namespace std;

typedef vector<int> VI;
typedef vector<VI> VVI;
typedef vector<string> VS;
typedef pair<int, int> PII;
typedef long long LL;
#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  FOR(i,0,n)
const double EPS = 1e-10;
const double PI  = acos(-1.0);
#define dump(x)  cerr << #x << " = " << (x) << endl;
#define debug(x) cerr << #x << " = " << (x) << " (L" << __LINE__ << ")" << " " << __FILE__ << endl;

int main() {
  int N, M, R;
  scanf("%d %d %d", &N, &M, &R);
  //vector<int> st(M), en(M), ef(M);
  vector<pair<int, PII> > data(M);
  REP(i, M) {
    scanf("%d %d %d", &data[i].second.first, &data[i].first, &data[i].second.second);
  }

  VI dp(M, 0);
  sort(data.begin(), data.end());
  for (int i = 0; i < M; i++) {
    int start = data[i].second.first;
    int end = data[i].first;
    int efficiency = data[i].second.second;
    dp[i] = efficiency;
    for (int j = 0; j < i; j++) {
      int end2 = data[j].first;
      if (end2 + R <= start) {
        dp[i] = max(dp[i], dp[j] + efficiency);
      }
    }
  }
  int answer = 0;
  REP(i, M) answer = max(answer, dp[i]);
  //REP(i, M) cerr << dp[i] << " "; cerr << endl;
  cout << answer << endl;
}

