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

const int MAX_W = 200;
const int MAX_H = 200;

int memo[MAX_W+1][MAX_H+1];

int grundy(int w, int h) {
  if (memo[w][h] != -1) return memo[w][h];

  set<int> s;
  for (int i = 2; w - i >= 2; i++) {
    s.insert(grundy(i, h) ^ grundy(w-i, h));
  }
  for (int i = 2; h - i >= 2; i++) {
    s.insert(grundy(w, i) ^ grundy(w, h-i));
  }

  int g = 0;
  while (s.find(g) != s.end()) g++;

  return memo[w][h] = g;
}

bool solve(int w, int h) {
  return grundy(w, h) != 0;
}

int main() {
  REP(i, MAX_W+1) REP(j, MAX_H+1) memo[i][j] = -1;

  int w, h;
  while (scanf("%d %d", &w, &h) > 0) {
    bool is1stWin = solve(w, h);
    if (is1stWin) {
      printf("WIN\n");
    } else {
      printf("LOSE\n");
    }
  }
}

