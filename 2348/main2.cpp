#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <algorithm>
#include <cstdio>
#include <cmath>
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

bool solve(int a, int b) {
  bool res = true;

  for (;;) {
    if (a > b) swap(a, b);

    if (b % a == 0) break;
    if (b - a > a) break;

    b -= a;
    res = !res;
  }
  return res;
}

int main() {
  while (true) {
    int a, b; cin >> a >> b;
    if (a == 0 && b == 0) break;
    bool res = solve(a, b);
    cout << (res ? "Stan" : "Ollie") << " wins" << endl;
  }
}

