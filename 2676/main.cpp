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


int stateCount = 0;

const int SIZE_SQRT = 3;
const int SIZE = SIZE_SQRT * SIZE_SQRT;

struct State {
  int p[SIZE][SIZE];
};

int bitcount(int n) {
  int c = 0;
  n &= ~(1 << SIZE);
  while (n) {
    ++c;
    n &= (n - 1);
  }
  return c;
}

void printbit(int n) {
  VI v;
  while (n) {
    v.push_back(n & 1);
    n >>= 1;
  }
  reverse(v.begin(), v.end());
  REP(i, v.size()) cerr << v[i];
  cerr << endl;
}

State modify(const State& s, int i_, int j_, int x) {
  State res = s;
  
  // 数字を決めたなら、10bit目を立てる。
  // 以降のビットは、可能性が残っている数字を表す
  res.p[i_][j_] = (1 << SIZE) | (1 << (x-1));

  REP(i, SIZE) {
    if (i != i_) res.p[i][j_] &= ~(1 << (x-1));
  }
  REP(j, SIZE) {
    if (j != j_) res.p[i_][j] &= ~(1 << (x-1));
  }
  int group_i = i_ / SIZE_SQRT;
  int group_j = j_ / SIZE_SQRT;
  REP(i, SIZE_SQRT) REP(j, SIZE_SQRT) {
    int cur_i = group_i * SIZE_SQRT + i;
    int cur_j = group_j * SIZE_SQRT + j;
    if (cur_i != i_ || cur_j != j_) res.p[cur_i][cur_j] &= ~(1 << (x-1)); 
  }

  return res;
}

void show(const VVI& grid) {
  REP(i, SIZE) {
    REP(j, SIZE) {
      if (grid[i][j] == 0)
        printf(" ");
      else
        printf("%d", grid[i][j]);
    }
    printf("\n");
  }
}

State result;
bool dfs(State s) {
  stateCount++;

  vector<PII> cand;
  REP(i, SIZE) {
    REP(j, SIZE) {
      if (!(s.p[i][j] & (1 << SIZE))) {
        int c = bitcount(s.p[i][j]);
        if (c == 0) {
          return false;
        }
        cand.push_back(make_pair(c, i * SIZE + j));
        if (c == 1) goto OUTER;
      }
    }
  }
  OUTER:

  if (cand.size() == 0) {
    //cerr << "============ SUCCESS!! (" << stateCount << ") ========" << endl;
    result = s;
    return true;
  }

  sort(cand.begin(), cand.end());

  int c_i = cand[0].second / SIZE;
  int c_j = cand[0].second % SIZE;
  int mask = s.p[c_i][c_j];
  REP(k, SIZE) {
    if (mask & (1 << k)) {
      bool res = dfs(modify(s, c_i, c_j, k+1));
      if (res) return true;
    }
  }

  return false;
}

VVI solve(const VVI& grid) {
  State s;
  REP(i, SIZE) REP(j, SIZE) s.p[i][j] = (1 << SIZE) - 1;
  REP(i, SIZE) REP(j, SIZE) {
    if (grid[i][j] != 0) {
      s = modify(s, i, j, grid[i][j]);
    }
  }

  dfs(s);

  VVI res(SIZE, VI(SIZE));
  REP(i, SIZE) REP(j, SIZE) {
    REP(k, SIZE) {
      if (result.p[i][j] & (1 << k)) {
        res[i][j] = k+1;
        break;
      }
    }
  }

  return res;
}


int main() {
  int T; scanf("%d", &T);
  REP(t, T) {
    char buf[12];
    VVI grid(SIZE, VI(SIZE));
    REP(i, SIZE) {
      scanf("%s", buf);
      REP(j, SIZE) {
        grid[i][j] = buf[j] - '0';
      }
    }

    VVI ans = solve(grid);
    show(ans);
  }
}

