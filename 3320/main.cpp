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

int main() {
  int P; cin >> P;
  vector<int> pages(P);
  REP(i, P) {
    int temp;
    scanf("%d", &temp);
    pages[i] = temp;
  }

  set<int> all;
  REP(i, P) all.insert(pages[i]);
  int n = all.size();

  int s = 0, t = 0, num = 0;
  map<int, int> count;
  int res = P;
  for (;;) {
    while (t < P && num < n) {
      if (count[pages[t]] == 0) {
        num++;
      }
      count[pages[t]]++;
      t++;
    }
    if (num < n) break;
    res = min(res, t - s);
    count[pages[s]]--;
    if (count[pages[s]] == 0) {
      num --;
    }
    s++;
  }
  cout << res << endl;
}

