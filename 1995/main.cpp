// Used : 740K	235MS
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <algorithm>
#include <numeric>
#include <cstdio>
#include <cmath>
#include <cstring>
using namespace std;

typedef vector<int> VI;
typedef vector<VI> VVI;
typedef vector<string> VS;
typedef pair<int, int> PII;
typedef long long LL;
#define ALL(a)  (a).begin(),(a).end()
#define REP(i,n) for(int i=0;i<(n);++i)
const double EPS = 1e-10;
const double PI  = acos(-1.0);
#define dump(x) cerr << "  (L" << __LINE__ << ") " << #x << " = " << (x) << endl;
#define dumpv(x) cerr << "  (L" << __LINE__ << ") " << #x << " = "; REP(q,(x).size()) cerr << (x)[q] << " "; cerr << endl;
template<typename T1, typename T2>
ostream& operator<<(ostream& s, const pair<T1, T2>& d) {return s << "(" << d.first << "," << d.second << ")";}

LL mod_pow(LL a, LL b, LL m) {
  LL res = 1;
  LL exp = a;
  while (b) {
    if (b & 1) res = (res * exp) % m;
    exp = (exp * exp) % m;
    b >>= 1;
  }
  return res;
}

int main() {
  cin.tie(0);
  ios::sync_with_stdio(false);

  int Z; cin >> Z;
  REP(z, Z) {
    int M; cin >> M;
    int H; cin >> H;
    LL sum = 0;
    REP(i, H) {
      LL a, b; cin >> a >> b;
      sum += mod_pow(a, b, M);
      sum %= M;
    }
    cout << sum << endl;
  }
}

