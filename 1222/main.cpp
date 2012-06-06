// Used: 724K	0MS
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
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

const int DR[] = {0, 0, 0, -1, 1};
const int DC[] = {0, -1, 1, 0, 0};

void push(VVI& P, int i, int j) {
  REP(k, 5) {
    int r = i + DR[k];
    int c = j + DC[k];
    if (r >= 0 && r < 5 && c >= 0 && c < 6) {
      P[r][c] = (P[r][c] ? 0 : 1);
    }
  }
}

void solve(VVI& P) {
  int buttons[5];
  for (int k = 0; k < (1 << 6); k++) {
    VVI v = P;
    memset(buttons, 0, sizeof(buttons));
    buttons[0] = k;
    REP(j, 6) {
      if (k & (1 << j)) push(v, 0, j);
    }
    for (int i = 1; i < 5; i++) {
      for (int j = 0; j < 6; j++) {
        if (v[i-1][j] == 1) {
          push(v, i, j);
          buttons[i] |= (1 << j);
        }
      }
    }
    if (find(v[4].begin(), v[4].end(), 1) == v[4].end()) break;
  }

  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 6; j++) {
      if (buttons[i] & (1 << j)) {
        cout << 1 << " ";
      } else {
        cout << 0 << " ";
      }
    }
    cout << endl;
  }
}

int main() {
  cin.tie(0);
  ios::sync_with_stdio(false);

  int T; cin >> T;
  REP(t, T) {
    VVI P(5, VI(6));
    REP(i, 5) REP(j, 6) cin >> P[i][j];

    cout << "PUZZLE #" << t+1 << endl;
    solve(P);
  }
}
