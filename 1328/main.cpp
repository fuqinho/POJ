#include <iostream>
#include <sstream>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
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

#define ALL(a)  (a).begin(),(a).end()
#define RALL(a) (a).rbegin(), (a).rend()
#define PB push_back
#define MP make_pair
#define SZ(a) int((a).size())
#define EXIST(s,e) ((s).find(e)!=(s).end())
#define SORT(c) sort((c).begin(),(c).end())
#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  FOR(i,0,n)

const double EPS = 1e-10;
const double PI  = acos(-1.0);

#define dump(x)  cerr << #x << " = " << (x) << endl;
#define debug(x) cerr << #x << " = " << (x) << " (L" << __LINE__ << ")" << " " << __FILE__ << endl;

int solve(int N, long long D, vector<PII >& islands) {
  vector<pair<double, int> > info(N);
  REP(i, N) {
    if (islands[i].second > D) return -1;
    info[i].first = islands[i].first + sqrt(D * D - islands[i].second * islands[i].second);
    info[i].second = i;
  }
  sort(info.begin(), info.end());
  double curT = 0.0;
  int ans = 0;
  for (int i = 0; i < info.size(); i++) {
    int j = info[i].second;
    int x = islands[j].first;
    int y = islands[j].second;
    if (i == 0 || (x-curT)*(x-curT) + y * y > D * D) {
      ans ++;
      curT = info[i].first;
    }
  }
  return ans;
}

int main() {
  int testId = 1;
  while (true) {
    int n, d;
    scanf("%d %d", &n, &d);
    if (n == 0 && d == 0) break;
    vector<PII> islands(n);
    REP(i, n) {
      int x, y;
      scanf("%d %d", &x, &y);
      islands[i] = PII(x, y);
    }
    int answer = solve(n, d, islands);
    cout << "Case " << testId << ": " << answer << endl;
    testId++;
  }
}

