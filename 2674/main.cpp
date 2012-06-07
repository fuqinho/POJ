// POJではWAをくらう。
// が、Webで探した解答そのままつっこんでもPOJではWAくらった。
// http://acm.tju.edu.cn/toj/showp1849.html では下記解答でAccepted
#include <cstdio>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <algorithm>
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

const double EPS = 1e-10;

struct Person {
  bool dir;
  double pos;
  char name[300];
};

void solve(double L, double V, vector<Person>& persons) {
  double max_time = 0.0;
  REP(i, persons.size()) {
    double dist = (persons[i].dir ? (L - persons[i].pos) : persons[i].pos);
    if (dist / V > max_time) {
      max_time = dist / V;
    }
  }

  vector<double> lastpos(persons.size());
  REP(i, persons.size()) {
    lastpos[i] = persons[i].pos + V * (persons[i].dir ? 1.0 : -1.0) * max_time;
  }
  sort(lastpos.begin(), lastpos.end());

  int survived_index = 0;
  REP(i, lastpos.size()) {
    if (lastpos[i] >= 0 - EPS && lastpos[i] <= L + EPS) survived_index = i;
  }

  printf("%13.2lf %s\n", (int)(max_time * 100) / 100.0, persons[survived_index].name);
}

int main() {
  cin.tie(0);
  ios::sync_with_stdio(false);

  while (true) {
    int N; scanf("%d", &N);
    if (N == 0) break;

    double L, V; scanf("%lf %lf", &L, &V);

    vector<Person> persons(N);
    REP(i, N) {
      char dir[2];
      scanf("%s %lf %s", dir, &persons[i].pos, persons[i].name);
      persons[i].dir = (dir[0] == 'p' || dir[0] == 'P');
    }

    solve(L, V, persons);
  }
}
