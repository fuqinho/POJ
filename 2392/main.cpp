#include <iostream>
#include <sstream>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
using namespace std;

typedef vector<int> VI;
typedef vector<VI> VVI;
typedef vector<string> VS;
typedef pair<int, int> PII;
typedef long long LL;
#define ALL(a)  (a).begin(),(a).end()
#define RALL(a) (a).rbegin(), (a).rend()
#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  FOR(i,0,n)
const double EPS = 1e-10;
const double PI  = acos(-1.0);
#define dump(x)  cerr << #x << " = " << (x) << endl;
#define dumpv(x) cerr << #x << " = "; REP(q,(x).size()) cerr << (x)[q] << " "; cerr << endl;
template<typename T1, typename T2>
ostream& operator<<(ostream& s, const pair<T1, T2>& d){return s<<"("<<d.first<<","<<d.second<<")";}

const int MAX_K = 400;
const int MAX_A = 40000;
int h[MAX_K];
int c[MAX_K];
int a[MAX_K];
int K;

int dp[MAX_K+1][MAX_A+1];

int solve(vector<pair<int, pair<int, int> > >& data) {
  sort(data.begin(), data.end());
  memset(dp, -1, sizeof(dp));
  
  for (int i = 0; i < K; i++) {
    int a = data[i].first;
    int h = data[i].second.first;
    int c = data[i].second.second;
    dp[i][0] = c;
    for (int j = 0; j <= MAX_A; j++) {
      if (j <= a) {
        if (i > 0 && dp[i-1][j] != -1) {
          dp[i][j] = c;
        } else if (j >= h && dp[i][j-h] != -1) {
          dp[i][j] = dp[i][j-h] - 1;
        }
      }
    }
  }
  int res = 0;
  for (int i = 0; i <= MAX_A; i++) if (dp[data.size()-1][i] != -1) res = i;
  return res;
}

int main() {
  scanf("%d", &K);
  vector<pair<int, pair<int, int> > > data(K);
  for (int i = 0; i < K; i++) {
    scanf("%d %d %d", &data[i].second.first, &data[i].first, &data[i].second.second);
  }

  int ans = solve(data);
  printf("%d\n", ans);
}

