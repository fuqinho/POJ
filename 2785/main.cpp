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

LL solve(int N, VI& A, VI& B, VI& C, VI& D) {

  vector<int> CD(N*N);
  REP(i, N) REP(j, N) CD[i*N+j] = C[i] + D[j];
  sort(ALL(CD));

  LL res = 0;
  REP(i, N) REP(j, N) {
    int ab = A[i] + B[j];
    res += upper_bound(CD.begin(), CD.end(), -ab) - lower_bound(CD.begin(), CD.end(), -ab);
  }
  return res;
}

int main() {
  int n;
  cin >> n;
  vector<int> A(n), B(n), C(n), D(n);
  REP(i, n) {
    scanf("%d %d %d %d", &A[i], &B[i], &C[i], &D[i]);
  }

  int answer = solve(n, A, B, C, D);
  cout << answer << endl;
  

}

