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

LL solve(int N, int S, vector<PII>& weeks) {
  for (int i = 1; i < weeks.size(); i++) {
    weeks[i].first = min(weeks[i].first, weeks[i-1].first + S);
  }
  LL cost = 0;
  for (int i = 0; i < weeks.size(); i++) {
    cost += (LL)weeks[i].first * weeks[i].second;
  }
  return cost;
}

int main() {
  int N, S;
  scanf("%d %d", &N, &S);
  vector<PII> weeks(N);
  REP(i, N) {
    int C, Y;
    scanf("%d %d", &C, &Y);
    weeks[i] = make_pair(C, Y);
  }
  LL answer = solve(N, S, weeks);
  cout << answer << endl;
}

