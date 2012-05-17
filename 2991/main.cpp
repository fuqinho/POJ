#include <iostream>
#include <sstream>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <iomanip>
#include <cmath>
#include <cstdio>
#include <string>
using namespace std;

typedef vector<int> VI;
typedef vector<VI> VVI;
typedef vector<string> VS;
typedef pair<int, int> PII;
typedef long long LL;
#define ALL(a)  (a).begin(),(a).end()
#define RALL(a) (a).rbegin(), (a).rend()
#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  FOR(i,0,n)
const double EPS = 1e-10;
const double PI  = acos(-1.0);
#define dump(x)  cerr << #x << " = " << (x) << endl;
#define debug(x) cerr << #x << " = " << (x) << " (L" << __LINE__ << ")" << " " << __FILE__ << endl;
#define check(x) cerr << #x << " = "; REP(q,(x).size()) cerr << (x)[q] << " "; cerr << endl;
#define checkn(x,n) cerr << #x << " = "; for(int i=0;i<(x).size()&&i<(n);++i) cerr << (x)[i] << " "; cerr << endl;

void init(int k, int l, int r, vector<double>& vx, vector<double>& vy, vector<double>& ang, VI& L) {
  ang[k] = vx[k] = 0.0;
  if (r - l == 1) {
    vy[k] = L[l];
  } else {
    int chl = k * 2 + 1;
    int chr = k * 2 + 2;
    init(chl, l, (l+r)/2, vx, vy, ang, L);
    init(chr, (l+r)/2, r, vx, vy, ang, L);
    vy[k] = vy[chl] + vy[chr];
  }
}

void change(int s, double a, int k, int l, int r, vector<double>& vx, vector<double>& vy, vector<double>& ang) {
  if (s > l && s < r) {
    int chl = k * 2 + 1;
    int chr = k * 2 + 2;
    change(s, a, chl, l, (l+r)/2, vx, vy, ang);
    change(s, a, chr, (l+r)/2, r, vx, vy, ang);
    if (s <= (l+r)/2) ang[k] += a;

    double s = sin(ang[k]);
    double c = cos(ang[k]);
    vx[k] = vx[chl] + (c * vx[chr] - s * vy[chr]);
    vy[k] = vy[chl] + (s * vx[chr] + c * vy[chr]);
  }
  //check(vx);
}

void solve(int N, int C, VI& L, VI& S, VI& A) {
  vector<double> vx(N * 4);
  vector<double> vy(N * 4);
  vector<double> ang(N * 4);
  vector<double> prv(N+1);
  
  init(0, 0, N, vx, vy, ang, L);
  REP(i, N) prv[i] = PI;

  REP(i, C) {
    int s = S[i];
    double a = A[i] / 360.0 * 2 * PI;
    change(s, a - prv[s], 0, 0, N, vx, vy, ang);
    prv[s] = a;
    printf("%.2f %.2f\n", vx[0], vy[0]);
  }
  printf("\n");
}

int main() {
  int N, C;
  while(scanf("%d%d",&N,&C) != EOF)
  {
    vector<int> L(N);
    REP(i, N) scanf("%d", &L[i]);

    vector<int> S(C), A(C);
    REP(i, C) {
      scanf("%d%d", &S[i], &A[i]);
    }
    
    solve(N, C, L, S, A);
  } 
}

