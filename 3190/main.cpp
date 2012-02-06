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
#define EACH(i,c) for(typeof((c).begin()) i=(c).begin(); i!=(c).end(); ++i)
#define EXIST(s,e) ((s).find(e)!=(s).end())
#define SORT(c) sort((c).begin(),(c).end())
#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  FOR(i,0,n)

const double EPS = 1e-10;
const double PI  = acos(-1.0);

#define dump(x)  cerr << #x << " = " << (x) << endl;
#define debug(x) cerr << #x << " = " << (x) << " (L" << __LINE__ << ")" << " " << __FILE__ << endl;

int solve(int N, vector<pair<PII, int> >& intervals, vector<int>& answer) {
  sort(intervals.begin(), intervals.end());
  priority_queue<PII, vector<PII>, greater<PII> > q;
  int maxSize = 0;
  for (int i = 0; i < intervals.size(); i++) {
    if (!q.empty() && q.top().first < intervals[i].first.first) {
      //dump(q.top().first);
      //dump(q.top().second);
      int stallNum = q.top().second;
      q.pop();
      answer[intervals[i].second] = stallNum;
      
      q.push(PII(intervals[i].first.second, stallNum));
      //dump(intervals[i].second);
    } else {
      int stallNum = q.size() + 1;
      answer[intervals[i].second] = stallNum;
      q.push(PII(intervals[i].first.second, stallNum));
    }
  }
  //debug(q.top().first);
  return q.size();
}

int main() {
  int N;
  scanf("%d", &N);
  vector<pair<PII, int> > intervals(N);
  REP(i, N) {
    int s, e;
    scanf("%d %d", &s, &e);
    intervals[i].first = PII(s, e);
    intervals[i].second = i;
  }

  vector<int> ans(N);
  int result = solve(N, intervals, ans);
  cout << result << endl;
  REP(i, ans.size()) cout << ans[i] << endl;
}

