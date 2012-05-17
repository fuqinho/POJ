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

int cross(const PII& a, const PII& b) {
  return a.first * b.second - a.second * b.first;
}

PII sub(PII& a, PII& b) {
  return PII(a.first - b.first, a.second - b.second);
}

// グラハムスキャン
vector<PII> convex_hull(vector<PII>& pos) {
  sort(ALL(pos));
  int k = 0; // 凸包の頂点数
  vector<PII> res(pos.size() * 2);
  REP(i, pos.size()) {
    while (k > 1 && cross(sub(res[k-1], res[k-2]), sub(pos[i], res[k-1])) <= 0) {
      k--;
    }
    res[k] = pos[i];
    k++;
  }
  for (int i = pos.size() - 2, t = k; i >= 0; i--) {
    while (k > t && cross(sub(res[k-1], res[k-2]), sub(pos[i], res[k-1])) <= 0) {
      k--;
    }
    res[k] = pos[i];
    k++;
  }
  res.resize(k-1);
  return res;
}

int dist(const PII& a, const PII& b) {
  int dx = a.first - b.first;
  int dy = a.second - b.second;
  return dx * dx + dy * dy;
}

int main() {
  int N; scanf("%d", &N);
  vector<PII> pos(N);
  REP(i, N) scanf("%d %d", &pos[i].first, &pos[i].second);

  vector<PII> ch = convex_hull(pos);

  if (ch.size() == 2) {
    cout << dist(ch[0], ch[1]) << endl;
    return 0;
  } 

  int i = 0;
  int j = 0;
  for (int k = 0; k < ch.size(); k++) {
    if (ch[k] <= ch[i]) i = k;
    if (ch[k] > ch[j]) j = k;
  }

  int res = 0;

  // キャリパー法
  int start_i = i;
  int start_j = j;
  while (i != start_j || j != start_i) {
    res = max(res, dist(ch[i], ch[j]));
    int i_next = (i + 1) % ch.size();
    int j_next = (j + 1) % ch.size();
    if (cross(sub(ch[i_next], ch[i]), sub(ch[j_next], ch[j])) < 0) {
      i = i_next;
    } else {
      j = j_next;
    }
  }

  cout << res << endl;
}

