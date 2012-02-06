#include <iostream>
#include <sstream>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
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

int main() {
  int N, T;
  scanf("%d %d", &N, &T);
  vector<pair<int, int> > intervals;
  REP(i, N) {
    int S, F;
    scanf("%d %d", &S, &F);
    intervals.push_back(PII(S, F));
  }
  sort(intervals.begin(), intervals.end());
  
  int res = 0;
  int maxGoal = 0;
  int filled = 0;
  for (int i = 0; i < intervals.size(); i++) {
    if (intervals[i].first > filled + 1) {
      if (intervals[i].first <= maxGoal + 1) {
        filled = maxGoal;
        res++;
      } else {
        res = -1;
        break;
      }
    }
    maxGoal = max(maxGoal, intervals[i].second);
  }
  if (filled < T) {
    if (maxGoal == T) res++;
    else res = -1;
  }
  cout << res << endl;
}

