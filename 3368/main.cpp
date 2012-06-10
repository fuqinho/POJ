// Used: 7064K	1610MS
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cmath>
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

const int MAX_N = 100000;
const int MAX_Q = 100000;

struct Group { int st, en, count; };

Group groups[MAX_N];
int gindex[MAX_N];

void solve(vector<int>& a, vector<PII>& query) {
  int gnum = 1;
  int cur = a[0];
  groups[0].st = 0;
  gindex[0] = 0;

  for (int i = 1; i <= a.size(); i++) {
    if (i == a.size() || a[i] != cur) {
      groups[gnum-1].en = i;
      groups[gnum-1].count = groups[gnum-1].en - groups[gnum-1].st;
      if (i == a.size()) break;

      cur = a[i];
      gnum++;
      groups[gnum-1].st = i;
    }
    gindex[i] = gnum-1;
  }

  // maxval[i][j]: max value in range [i, i+2^j)
  int max_j = (int)log2(gnum) + 1;
  vector<vector<int> > maxval(gnum, vector<int>(max_j));
  for (int i = 0; i < gnum; i++) {
    maxval[i][0] = groups[i].count;
  }
  for (int j = 1; j < max_j; j++) {
    for (int i = 0; i + (1 << j) <= gnum; i++) {
      maxval[i][j] = max(maxval[i][j-1], maxval[i + (1<<(j-1))][j-1]);
    }
  }

  // process query
  for (int i = 0; i < query.size(); i++) {
    int s = query[i].first - 1;
    int e = query[i].second - 1;

    int res = 0;
    if (gindex[s] == gindex[e]) {
      res = e - s + 1;
    } else {
      int gs = gindex[s];
      int ge = gindex[e];
      int v1 = groups[gs].en - s;
      int v2 = e + 1 - groups[ge].st;
      res = max(v1, v2);
      if (ge - gs > 1) {
        // find max value for [gs, ge]
        int num = ge - gs - 1;
        int j = 0;
        while ((1 << j) * 2 < num) j++;
        int v3 = max(maxval[gs+1][j], maxval[ge-(1<<j)][j]);
        res = max(res, v3);
      }
    }
    printf("%d\n", res);
  }
}

int main() {
  while (true) {
    int n; scanf("%d", &n);
    if (n == 0) break;
    int q; scanf("%d", &q);

    vector<int> a(n);
    REP(i, n) scanf("%d", &a[i]);

    vector<PII> query(q);
    REP(i, q) scanf("%d %d", &query[i].first, &query[i].second);

    solve(a, query);
  }
}
