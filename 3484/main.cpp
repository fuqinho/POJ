// Used: 1732K	641MS
#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

typedef vector<int> VI;
typedef vector<VI> VVI;
typedef pair<int, int> PII;
typedef long long LL;
#define REP(i,n) for(int i=0;i<(n);++i)
#define REP_R(i,n) for(int i=(n)-1;i>=0;--i)

#define dump(x) cerr << "  (L" << __LINE__ << ") " << #x << " = " << (x) << endl;
#define dumpv(x) cerr << "  (L" << __LINE__ << ") " << #x << " = "; REP(q,(x).size()) cerr << (x)[q] << " "; cerr << endl;
template<typename T1, typename T2>
ostream& operator<<(ostream& s, const pair<T1, T2>& d) {return s << "(" << d.first << "," << d.second << ")";}

vector<LL> X, Y, Z;

// return true if numbers(<= k) has odd references 
bool hasOddRef(LL k) {
  int N = X.size();
  LL count = 0;
  REP(i, N) {
    LL num = max(0LL, (min(k, Y[i])-X[i]) / Z[i] + 1);
    count += num;
  }
  return count % 2 != 0;
}

int count(int k) {
  int res = 0;
  REP(i, X.size()) {
    if (k >= X[i] && k <= Y[i] && (k - X[i]) % Z[i] == 0) res++;
  }
  return res;
}

const LL INF = 100000000000;
void solve() {
  LL lb = 0, ub = INF;
  while (ub - lb > 1) {
    LL mid = (lb + ub) / 2;
    if (hasOddRef(mid)) ub = mid;
    else lb = mid;
  }
  hasOddRef(2);
  
  if (ub == INF) {
    cout << "no corruption" << endl;
  } else {
    cout << ub << " " << count(ub) << endl;
  }
}

int main() {
  cin.tie(0);
  ios::sync_with_stdio(false);

  string s;
  int N = 0;
  while (getline(cin, s)) {
    if (s == "") {
      if (X.size() != 0) {
        solve();
        X.clear();
        Y.clear();
        Z.clear();
      }
    } else {
      istringstream iss(s);
      int x, y, z; iss >> x >> y >> z;
      X.push_back(x);
      Y.push_back(y);
      Z.push_back(z);
    }
  }
  if (X.size() != 0) {
    solve();
  }
}
