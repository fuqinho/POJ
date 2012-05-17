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
#define dumpv(x) {cerr << "  (L" << __LINE__ << ") " << #x << " = "; REP(q,(x).size()) cerr << (x)[q] << " "; cerr << endl;}
template<typename T1, typename T2>
ostream& operator<<(ostream& s, const pair<T1, T2>& d) {return s << "(" << d.first << "," << d.second << ")";}


int stateCount = 0;

const int SIZE_SQRT = 3;
const int SIZE = SIZE_SQRT * SIZE_SQRT;

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

bool modify(int res[SIZE][SIZE], int i_, int j_, int x) {
  int mask = (1 << (x-1));
  static const int donebit = (1 << SIZE);

  // 数字を決めたなら、10bit目を立てる。
  // 以降のビットは、可能性が残っている数字を表す
  res[i_][j_] = donebit | mask;

  REP(i, SIZE) {
    if (i != i_ && !(res[i][j_] & donebit)) {
      res[i][j_] &= ~mask;
      if (res[i][j_] == 0) return false;
    }
  }
  REP(j, SIZE) {
    if (j != j_ && !(res[i_][j] & donebit)) {
      res[i_][j] &= ~mask;
      if (res[i_][j] == 0) return false;
    }
  }
  int group_i = i_ / SIZE_SQRT;
  int group_j = j_ / SIZE_SQRT;
  REP(i, SIZE_SQRT) REP(j, SIZE_SQRT) {
    int cur_i = group_i * SIZE_SQRT + i;
    int cur_j = group_j * SIZE_SQRT + j;
    if ((cur_i != i_ || cur_j != j_) && !(res[cur_i][cur_j] & donebit)) {
      res[cur_i][cur_j] &= ~mask; 
      if (res[cur_i][cur_j] == 0) return false;
    }
  }
  return true;
}

void show(const VVI& grid) {
  REP(i, SIZE) {
    REP(j, SIZE) {
      if (grid[i][j] == 0)
        printf(" ");
      else
        printf("%d", grid[i][j]);
    }
    //printf("\n");
  }
  printf("\n");
}

//State result;
int result[SIZE][SIZE];

bool dfs(int s[SIZE][SIZE]) {
  stateCount++;

  int min_i, min_j, min_c = SIZE+1;
  REP(i, SIZE) {
    REP(j, SIZE) {
      if (!(s[i][j] & (1 << SIZE))) {
        int c = __builtin_popcount(s[i][j]);
        if (c == 0) {
          return false;
        }
        if (c < min_c) {
          min_c = c;
          min_i = i;
          min_j = j;
        }
        if (c == 1) goto OUTER;
      }
    }
  }
  OUTER:

  if (min_c == SIZE+1) {
    //cerr << "============ SUCCESS!! (" << stateCount << ") ========" << endl;
    memcpy(result, s, sizeof(result));
    return true;
  }

  int mask = s[min_i][min_j];
  REP(k, SIZE) {
    if (mask & (1 << k)) {
      int tmp[SIZE][SIZE];
      memcpy(tmp, s, sizeof(tmp));
      if (modify(tmp, min_i, min_j, k+1)) {
        bool res = dfs(tmp);
        if (res) return true;
      }
    }
  }

  return false;
}

VVI solve(const VVI& grid) {
  int s[SIZE][SIZE];
  REP(i, SIZE) REP(j, SIZE) s[i][j] = (1 << SIZE) - 1;
  REP(i, SIZE) REP(j, SIZE) {
    if (grid[i][j] != 0) {
      modify(s, i, j, grid[i][j]);
    }
  }

  dfs(s);

  VVI res(SIZE, VI(SIZE));
  REP(i, SIZE) REP(j, SIZE) {
    REP(k, SIZE) {
      if (result[i][j] & (1 << k)) {
        res[i][j] = k+1;
        break;
      }
    }
  }

  return res;
}

int main() {
  while(true) {
    char buf[100];
    scanf("%s", buf);
    if (strcmp(buf, "end") == 0) break;

    VVI grid(SIZE, VI(SIZE));
    REP(i, SIZE) {
      REP(j, SIZE) {
        if (buf[i*SIZE+j] == '.') grid[i][j] = 0;
        else grid[i][j] = buf[i*SIZE + j] - '0';
      }
    }

    VVI ans = solve(grid);
    show(ans);
    //cerr << stateCount << endl;
    stateCount = 0;
  }
}

