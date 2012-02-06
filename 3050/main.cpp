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

int dr[] = {0, 0, -1, 1};
int dc[] = {-1, 1, 0, 0};

set<string> s;
int result = 0;

void walk(const vector<vector<char> >& matrix, string& str, int row, int col, int index) {
  if (index == 6) {
    if (s.find(str) == s.end()) {
      result++;
      s.insert(str);
    }
    return;
  }

  REP(i, 4) {
    int r = row + dr[i];
    int c = col + dc[i];
    if (r >= 0 && r < 5 && c >= 0 && c < 5) {
      str[index] = matrix[r][c];
      walk(matrix, str, r, c, index+1);
    }
  }
}

int main() {
  // input
  vector<vector<char> > matrix(5, vector<char>(5));
  REP(i, 5) REP(j, 5) cin >> matrix[i][j];

  REP(i, 5) REP(j, 5) {
    string str = "      ";
    str[0] = matrix[i][j];
    walk(matrix, str, i, j, 1);
  }
  /*
  for(set<string>::iterator i = s.begin(); i != s.end(); i++) {
    cerr << *i << endl;
  }
  */
  cout << result << endl;
}

