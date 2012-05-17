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
#define dumpv(x) cerr << "  (L" << __LINE__ << ") " << #x << " = "; REP(q,(x).size()) cerr << (x)[q] << " "; cerr << endl;
template<typename T1, typename T2>
ostream& operator<<(ostream& s, const pair<T1, T2>& d) {return s << "(" << d.first << "," << d.second << ")";}

int N;
VI removed;

const int INF = 100000000;
const int MAX_MATCH = 60;
const int MAX_SQUARE = 55;

int M; // 初期状態で残っているマッチの数
int S; // 初期状態で残ってる正方形の数
bool m[MAX_MATCH][MAX_SQUARE]; // m[i][j]] == true <-> マッチiが正方形jに含まれるかどうか
int mmax[MAX_SQUARE]; // 正方形iを壊せるマッチの番号の最大値

// i行j列の四角形の周囲のマッチのIDを返す
int matchIdTop(int i, int j) {
  return i * (N + N + 1) + j;
}
int matchIdLeft(int i, int j) {
  return matchIdTop(i, j) + N;
}
int matchIdRight(int i, int j) {
  return matchIdLeft(i, j) + 1;
}
int matchIdBottom(int i, int j) {
  return matchIdTop(i+1, j);
}

void init() {
  // sum up match
  M = 0;
  M += N * 2 + 2 * N * N;

  // associate match with square
  memset(m, 0, sizeof(m));
  memset(mmax, -1, sizeof(mmax));
  S = 0;
  for (int w = 1; w <= N; w++) {
    for (int i = 0; i + w <= N; i++) {
      for (int j = 0; j + w <= N; j++) {
        for (int k = i; k < i+w; k++) {
          for (int l = j; l < j+w; l++) {
            if (k == i) {
              int matchId = matchIdTop(k, l);
              m[matchId][S] = true;
              mmax[S] = max(mmax[S], matchId);
            }
            if (k == i+w-1) {
              int matchId = matchIdBottom(k, l);
              m[matchId][S] = true;
              mmax[S] = max(mmax[S], matchId);
            }
            if (l == j) {
              int matchId = matchIdLeft(k, l);
              m[matchId][S] = true;
              mmax[S] = max(mmax[S], matchId);
            }
            if (l == j+w-1) {
              int matchId = matchIdRight(k, l);
              m[matchId][S] = true;
              mmax[S] = max(mmax[S], matchId);
            }
          }
        }
        S++;
      }
    }
  }
}

// p以降のマッチを考えた時の解の下限
int hstar(int p, vector<bool> state) {
  vector<PII> ps;
  REP(i, S) {
    if (state[i]) {
      // 残っている正方形に対してマッチの本数を数える
      int num = 0;
      for (int j = p; j < M; j++) {
        if (m[j][i]) num++;
      }
      ps.push_back(make_pair(num, i));
    }
  }

  // マッチの本数が少ない順にソート
  sort(ALL(ps));
  int res = 0;

  // used[i] == true: Xに含まれる正方形でマッチiを含むものが存在する
  vector<bool> used(M, false);
  REP(i, ps.size()) {
    int squareId = ps[i].second;
    bool ok = true;
    // 正方形idをXに追加できるか
    for (int j = p; j < M; j++) {
      if (used[j] && m[j][squareId]) ok = false;
    }
    if (ok) {
      res++;
      for (int j = p; j < M; j++) {
        if (m[j][squareId]) used[j] = true;
      }
    }
  }
  return res;
}

int min_res;
int state_count = 0;

// pは今見ているマッチのID, numはそれまでに除いたマッチの本数
// state[i] = true: 正方形iが残っている
int dfs(int p, int num, vector<bool> state) {
  state_count++;

  // マッチを全て見終われば正方形は全て壊されている
  if (p == M) return min_res = num;

  // すでに見つけた解より大きくなるなら打ち切る
  //if (num >= min_res) return INF;
  if (num + hstar(p, state) >= min_res) return INF;

  bool use = false; // マッチpを必ず除かないといけない場合true
  bool notuse = true; // マッチpを除いても意味が無い場合true
  REP(i, S) {
    // マッチpで正方形iを壊せるなら除いてもよい
    if (state[i] && m[p][i]) notuse = false;

    // マッチpで正方形iを必ず壊さないといけない
    if (state[i] && mmax[i] == p) use = true;
  }

  int res = INF;

  // マッチpを除かない場合
  if (!use) res = min(res, dfs(p + 1, num, state));

  // マッチpを除く場合
  for (int i = 0; i < S; i++) {
    if (m[p][i]) state[i] = false; // 関係する正方形を壊す
  }
  if (!notuse) res = min(res, dfs(p + 1, num + 1, state));

  return res;
}

int solve() {
  init();

  vector<bool> state(S, true);

  REP(i, removed.size()) {
    int matchId = removed[i] - 1;
    REP(j, S) {
      if (m[matchId][j]) {
        state[j] = false;
        m[matchId][j] = false;
      }
    }
  }

  min_res = INF;
  int ans = dfs(0, 0, state);
  //dump(state_count);

  return ans;
}

int main() {
  int T; scanf("%d", &T);
  REP(t, T) {
    scanf("%d", &N);

    int rem_count; scanf("%d", &rem_count);
    removed = VI(rem_count);
    REP(i, rem_count) scanf("%d", &removed[i]);
    
    int ans = solve();
    printf("%d\n", ans);
  }
}

