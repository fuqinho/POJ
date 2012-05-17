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

LL solve(int N, VI& H) {
  // L[i]: i番目の棒が最長になるように区間を取るときの、
  // 左端になる棒のインデックス(L[i]-1番目の棒はi番目の棒より短い)
  vector<int> L(N);

  // 注目している棒より短い棒をスタックで管理する
  // STL stack: 172ms (deque使ってるから遅いと思ったら意外と遅くない)
  stack<int> st;

  // 自前stack: 157ms
  //static int st[100000];
  //int sp = 0; // stack pointer

  REP(i, N) {
    while (!st.empty() && H[st.top()] >= H[i]) st.pop();
    if (st.empty()) {
      L[i] = 0;
    } else {
      L[i] = st.top() + 1;
    }
    st.push(i);
    /*
    while (sp != 0 && H[st[sp]] >= H[i]) sp--;
    if (sp == 0) {
      L[i] = 0;
    } else {
      L[i] = st[sp] + 1;
    }
    st[++sp] = i;
    */
  }

  // R[i]: i番目の棒が最長になるように区間を取るときの、
  // 右端になる棒のインデックス(R[i]+1番目の棒はi番目の棒より短い)
  vector<int> R(N);
  while(!st.empty()) st.pop();
  //sp = 0;

  for (int i = N-1; i >= 0; i--) {
    while (!st.empty() && H[st.top()] >= H[i]) st.pop();
    if (st.empty()) {
      R[i] = N-1;
    } else {
      R[i] = st.top() - 1;
    }
    st.push(i);
    /*
    while (sp != 0 && H[st[sp]] >= H[i]) sp--;
    if (sp == 0) {
      R[i] = N - 1;
    } else {
      R[i] = st[sp] - 1;
    }
    st[++sp] = i;
    */
  }

  // 最大の棒が0~N-1番目になるそれぞれの場合の面積計算して最大を返す
  LL max_area = 0;
  REP(i, N) {
    LL area = (LL)H[i] * (R[i] - L[i] + 1);
    max_area = max(max_area, area);
  }

  return max_area;
}

int main() {
  while (true) {
    int N; scanf("%d", &N);
    if (N == 0) break;
    VI H(N);
    REP(i, N) scanf("%d", &H[i]);

    LL ans = solve(N, H);
    cout << ans << endl;
  }
}

