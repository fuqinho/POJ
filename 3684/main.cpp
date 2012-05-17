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

double getPos(int H, int T) {
  if (T <= 0) return H;

  double t = sqrt(2.0 * H / 10);
  int k = static_cast<int>(floor(T / t));
  double y = H;
  if (k % 2 == 0) {
    y -= (T - k*t) * (T - k*t) * 10 / 2;
  } else {
    y -= (t - (T - k*t)) * (t - (T - k*t)) * 10 / 2;
  }
  return y;
}

vector<double> solve(int N, int H, int R, int T) {
  vector<double> posList(N);
  for (int i = 0; i < N; i++) {
    double y = getPos(H, T-i);
    posList[i] = y;
  }
  sort(ALL(posList));
  for (int i = 0; i < N; i++) {
    posList[i] += 2.0 * i * R / 100;
  }
  return posList;
}

int main() {
  int C;
  cin >> C;
  REP(i, C) {
    int N, H, R, T;
    cin >> N >> H >> R >> T;
    vector<double> ans = solve(N, H, R, T);
    REP(j, ans.size()) printf("%0.2f ", ans[j]); cout << endl;
  }
}

