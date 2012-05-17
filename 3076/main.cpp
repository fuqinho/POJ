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

const int SIZE_SQRT = 4;
const int SIZE = SIZE_SQRT * SIZE_SQRT;
const int DONEBIT = (1 << SIZE);

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

  int BIT_X = (1 << (x-1));
  // 数字を決めたなら、10bit目を立てる。
  // 以降のビットは、可能性が残っている数字を表す
  res[i_][j_] = DONEBIT | BIT_X;

  REP(i, SIZE) {
    if (i != i_ && !(res[i][j_] & DONEBIT)) {
      res[i][j_] &= ~BIT_X;
      if (res[i][j_] == 0) return false;
    }
  }
  REP(j, SIZE) {
    if (j != j_ && !(res[i_][j] & DONEBIT)) {
      res[i_][j] &= ~BIT_X;
      if (res[i_][j] == 0) return false;
    }
  }
  int group_i = i_ / SIZE_SQRT;
  int group_j = j_ / SIZE_SQRT;
  REP(i, SIZE_SQRT) REP(j, SIZE_SQRT) {
    int cur_i = group_i * SIZE_SQRT + i;
    int cur_j = group_j * SIZE_SQRT + j;
    if ((cur_i != i_ || cur_j != j_) && !(res[cur_i][cur_j] & DONEBIT)) {
      res[cur_i][cur_j] &= ~BIT_X; 
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
        printf("%c", 'A' + grid[i][j] - 1);
    }
    printf("\n");
  }
  printf("\n");
}

void printCount(int s[SIZE][SIZE]) {
  REP(i, SIZE) {
    REP(j, SIZE) {
      if (s[i][j] & DONEBIT) {
        cerr << " ";
      } else {
        cerr << __builtin_popcount(s[i][j]);
      }
    }
    cerr << endl;
  }
}


//State result;
int result[SIZE][SIZE];

bool dfs(int s[SIZE][SIZE]) {
  stateCount++;

AGAIN:
  int min_i, min_j;
  int min_c = SIZE+1;
  REP(i, SIZE) {
    REP(j, SIZE) {
      if (!(s[i][j] & DONEBIT)) {
        int c = __builtin_popcount(s[i][j]);
        if (c == 1) {
          int x;
          REP(k, SIZE) {
            if (s[i][j] & (1 << k)) {
              if (!modify(s, i, j, k+1)) return false;
              goto AGAIN;
            }
          }
        }
        if (c < min_c) {
          min_c = c;
          min_i = i;
          min_j = j;
        }
      }
    }
  }

  // 行ごとに矛盾が無いかチェック
  REP(i, SIZE) {
    // 行でまだ使われていない数字を調べる
    int avail = (1 << SIZE) - 1;
    REP(j, SIZE) {
      if (s[i][j] & DONEBIT) {
        avail &= ~s[i][j];
      }
    }

    // まだこの行の中で使われていない数字それぞれについて、
    // この列の中の空きマスで埋めれる所があるか探す。
    // なければ失敗。
    // １個しかなければすぐ設定してしまう。
    REP(k, SIZE) {
      if (avail & (1 << k)) {
        int cnt = 0, only_col = -1;
        REP(j, SIZE) {
          if (!(s[i][j] & DONEBIT) && (s[i][j] & (1 << k))) {
            cnt++;
            only_col = j;
          }
        }
        if (cnt == 0) {
          return false;
        } else if (cnt == 1) {
          // 設定
          if (!modify(s, i, only_col, k+1)) return false;
          goto AGAIN;
        }
      }
    }
  }

  // 列ごとに矛盾が無いかチェック
  REP(j, SIZE) {
    int avail = (1 << SIZE) - 1;
    REP(i, SIZE) {
      if (s[i][j] & DONEBIT) {
        avail &= ~s[i][j];
      }
    }
    REP(k, SIZE) {
      if (avail & (1 << k)) {
        int cnt = 0, only_row = -1;
        REP(i, SIZE) {
          if (!(s[i][j] & DONEBIT) && (s[i][j] & (1 << k))) {
            cnt++;
            only_row = i;
          }
        }
        if (cnt == 0) {
          return false;
        } else if (cnt == 1) {
          // 設定
          if (!modify(s, only_row, j, k+1)) return false;
          goto AGAIN;
        }
      }
    }
  }

  // ブロックごとに矛盾がないかチェック
  REP(bi, SIZE_SQRT) REP(bj, SIZE_SQRT) {
    int avail = (1 << SIZE) - 1;
    REP(i, SIZE_SQRT) REP(j, SIZE_SQRT) {
      if (s[SIZE_SQRT*bi + i][SIZE_SQRT*bj + j] & DONEBIT) {
        avail &= ~s[SIZE_SQRT*bi + i][SIZE_SQRT*bj + j];
      }
    }
    REP(k, SIZE) {
      if (avail & (1 << k)) {
        int cnt = 0, only_row = -1, only_col = -1;
        REP(i, SIZE_SQRT) REP(j, SIZE_SQRT) {
          int sij = s[SIZE_SQRT*bi + i][SIZE_SQRT*bj + j];
          if (!(sij & DONEBIT) && (sij & (1 << k))) {
            cnt++;
            only_row = SIZE_SQRT*bi + i;
            only_col = SIZE_SQRT*bj + j;
          }
        }
        if (cnt == 0) {
          return false;
        } else if (cnt == 1) {
          // 設定
          if (!modify(s, only_row, only_col, k+1)) return false;
          goto AGAIN;
        }
      }
    }
  }

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
  char buf[100];
  while (true) {
    VVI grid(SIZE, VI(SIZE));
    REP(i, SIZE) {
      if (scanf("%s", buf) == EOF) return 0;;
      REP(j, SIZE) {
        if (buf[j] == '-') grid[i][j] = 0;
        else grid[i][j] = buf[j] - 'A' + 1;
      }
    }

    VVI ans = solve(grid);
    show(ans);
  }
}

