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

int main() {
  int N; scanf("%d", &N);
  vector<PII> pos(N);
  REP(i, N) scanf("%d %d", &pos[i].first, &pos[i].second);

  vector<PII> ch = convex_hull(pos);
  //dumpv(ch);
  int res = 0;
  for (int i = 0; i < ch.size(); i++) {
    for (int j = 0; j < ch.size(); j++) {
      res = max(res, 
          (ch[i].first - ch[j].first) * (ch[i].first - ch[j].first) +
          (ch[i].second - ch[j].second) * (ch[i].second - ch[j].second));
    }
  }
  cout << res << endl;
}

