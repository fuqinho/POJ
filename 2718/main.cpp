#include <iostream>
#include <sstream>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <queue>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <iomanip>
#include <cmath>
#include <string>
#include <cstdio>
using namespace std;

typedef vector<int> VI;
typedef vector<VI> VVI;
typedef vector<string> VS;
typedef pair<int, int> PII;
typedef long long LL;

#define ALL(a)  (a).begin(),(a).end()
#define RALL(a) (a).rbegin(), (a).rend()
#define PB push_back
#define MP make_pair
#define SZ(a) int((a).size())
#define EACH(i,c) for(typeof((c).begin()) i=(c).begin(); i!=(c).end(); ++i)
#define EXIST(s,e) ((s).find(e)!=(s).end())
#define SORT(c) sort((c).begin(),(c).end())
#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  FOR(i,0,n)

const double EPS = 1e-10;
const double PI  = acos(-1.0);

#define dump(x)  cerr << #x << " = " << (x) << endl;
#define debug(x) cerr << #x << " = " << (x) << " (L" << __LINE__ << ")" << " " << __FILE__ << endl;

int getNum(vector<int>& v) {
  int res = 0;
  REP(i, SZ(v)) {
    res *= 10;
    res += v[i];
  }
  return res;
}

int solve(vector<int>& v) {
  int res = 1000000;
  if (SZ(v) % 2 == 0) {
    VI a(SZ(v)/2);
    VI b(SZ(v)/2);
    for (int i = 0; i < v.size() - 1; i++) {
      if (v[i] == 0 || v[i+1] == 0) continue;
      a[0] = v[i];
      b[0] = v[i+1];
      int added = 0;
      for (int j = 0; j < v.size(); j++) {
        if (j != i && j != i+1) {
          if (added < SZ(v)/2 - 1) {
            b[1+added] = v[j];
          } else {
            a[SZ(v)-2-added] = v[j];
          }
          added++;
        }
      }
      int an = getNum(a);
      int bn = getNum(b);
      res = min(res, abs(an - bn));
    }
  }
  else {
    VI a(SZ(v)/2+1);
    VI b(SZ(v)/2);
    //dump(a.size());
    //dump(b.size());
    for (int i = 0; i < SZ(v); i++) {
      if (v[i] != 0) {
        a[0] = v[i];
        vector<int>::iterator it = v.begin() + i;
        v.erase(it);
        break;
      }
    }
    int added = 0;
    for (int i = 0; i < v.size(); i++) {
      if (added < SZ(v)/2) {
        a[1+added] = v[i];
      } else {
        b[SZ(v) - 1 - added] = v[i];
      }
      added++;
    }
    int an = getNum(a);
    int bn = getNum(b);
    res = abs(an - bn);
  }
  return res;
}

// !!! NOT ACCEPTED YET (WA)
int main() {
  int T;
  string line;
  getline(cin, line);
  stringstream sin2(line);
  sin2 >> T;
  for (int i = 0; i < T; i++) {
    getline(cin, line);
    //dump(line);
    stringstream sin(line);
    vector<int> v;
    int n;
    while(sin >> n) {
      v.push_back(n);
    }
    //dump(v.size());
    int answer = solve(v);
    cout << answer << endl;
  }
}

