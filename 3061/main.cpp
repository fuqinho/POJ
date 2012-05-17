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
#include <cmath>
#include <cstdio>
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
#define debug(x) cerr << #x << " = " << (x) << " (L" << __LINE__ << ")" << " " << __FILE__ << endl;
#define check(x) cerr << #x << " = "; REP(q,(x).size()) cerr << (x)[q] << " "; cerr << endl;
#define checkn(x,n) cerr << #x << " = "; for(int i=0;i<(x).size()&&i<(n);++i) cerr << (x)[i] << " "; cerr << endl;

/*
int solve(int n, int S, vector<int>& a) {
  int res = n + 1;
  int s = 0, t = 0, sum = 0;
  for (;;) {
    while (t < n && sum < S) {
      sum += a[t++];
    }
    if (sum < S) break;
    res = min(res, t - s);
    sum -= a[s++];
  }
  if (res > n) res = 0;
  return res;
}
*/

int solve(int n, int S, vector<int>& a) {
  int head = 0;
  int tail = 0;
  int min_length = a.size() + 1;
  int sum = a[0];
  while (true) {
    if (sum >= S) {
      min_length = min(min_length, tail - head + 1);
      sum -= a[head];
      head++;
    } else {
      if (tail >= a.size() - 1) break;
      tail++;
      sum += a[tail];
    }
  }
  if (min_length == a.size() + 1) {
    return 0;
  } else {
    return min_length;
  }
}

int main() {
  int T; scanf("%d", &T);
  REP(i, T) {
    int N, S;
    scanf("%d %d", &N, &S);
    vector<int> a(N);
    REP(j, N) {
      int temp;
      scanf("%d", &temp);
      a[j] = temp;
    }

    int answer = solve(N, S, a);
    cout << answer << endl;
  }
}

