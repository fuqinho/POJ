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

int main() {
  while (true) {
    vector<int> order(6);
    scanf("%d %d %d %d %d %d", &order[0], &order[1], &order[2], &order[3], &order[4], &order[5]);
    if (order[0] == 0 && order[1] == 0 && order[2] == 0 && order[3] == 0 && order[4] == 0 && order[5] == 0) break;

    int num = 0;
    int s1 = 0;
    int s2 = 0;

    // 6
    num += order[5];

    // 5
    num += order[4];
    s1 += order[4] * 11;

    // 4
    num += order[3];
    s2 += order[3] * 5;

    // 3
    num += (order[2] + 3) / 4;
    switch (order[2] % 4) {
    case 1:
      s2 += 5;
      s1 += 7;
      break;
    case 2:
      s2 += 3;
      s1 += 6;
      break;
    case 3:
      s2 += 1;
      s1 += 5;
      break;
    default:
      break;
    }
    
    // 2
    if (order[1] >= s2) {
      order[1] -= s2;
      s2 = 0;
      num += (order[1] + 8) / 9;
      if (order[1] % 9 != 0) s1 += (9 - order[1] % 9) * 4;
    } else {
      s1 += (s2 - order[1]) * 4;
    }

    // 1
    if (order[0] >= s1) {
      num += ((order[0] - s1) + 35) / 36;
    }

    cout << num << endl;
  }
}

