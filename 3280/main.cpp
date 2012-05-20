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

const int MAX_LEN = 2000;
int N, M;
char S[MAX_LEN+1];
int cost[26];

int memo[MAX_LEN+1][MAX_LEN+1];

int dfs(int s, int t) {
  if (memo[s][t] != -1) return memo[s][t];
  if (t - s <= 1) return 0;
  
  if (S[s] == S[t-1]) {
    return memo[s][t] = dfs(s+1, t-1);
  } else {
    int res1 = dfs(s, t-1) + cost[S[t-1]-'a'];
    int res2 = dfs(s+1, t) + cost[S[s]-'a'];
    return memo[s][t] = min(res1, res2);
  }
}

int solve() {
  memset(memo, -1, sizeof(memo));
  return dfs(0, M);
}

int main() {
  scanf("%d %d", &N, &M);
  scanf("%s\n", S);
  REP(i, N) {
    char c[2]; int add, del;
    scanf("%s %d %d", c, &add, &del);
    cost[c[0] - 'a'] = min(add, del);
  }

  int ans = solve();
  printf("%d\n", ans);
}

