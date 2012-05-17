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


const int MAX_V = 4000;
int V;
VI G[MAX_V];
VI rG[MAX_V];
bool used[MAX_V];
VI vs;
int cmp[MAX_V];

void add_edge(int from, int to) {
  G[from].push_back(to);
  rG[to].push_back(from);
}

void dfs(int v) {
  used[v] = true;
  REP(i, G[v].size()) {
    int next_v = G[v][i];
    if (!used[next_v]) dfs(next_v);
  }
  vs.push_back(v);
}

void rdfs(int v, int k) {
  used[v] = true;
  cmp[v] = k;
  REP(i, rG[v].size()) {
    int next_v = rG[v][i];
    if (!used[next_v]) rdfs(next_v, k);
  }
}


int scc() {
  vs.clear();
  fill(used, used+V, false);
  REP(i, V) {
    if (!used[i]) dfs(i);
  }

  //dumpv(vs);
  fill(used, used+V, false);
  int k = 0;
  for (int i = vs.size()-1; i >= 0; i--) {
    int v = vs[i];
    if (!used[v]) rdfs(v, k++);
  }

  return k;
}


int main() {
  // Input
  int N; cin >> N;
  vector<PII> S(N), T(N);


  // S[i]: i番目のカップルの式前の祭典時間
  // S[i+N]: i番目のカップルの式後の祭典時間
  vector<PII> sections(N*2);
  
  REP(i, N) {
    int sh, sm, th, tm, d;
    scanf("%d:%d %d:%d %d", &sh, &sm, &th, &tm, &d);
    sections[i].first = sh * 60 + sm;
    sections[i].second = sh * 60 + sm + d;
    sections[i+N].first = th * 60 + tm - d;
    sections[i+N].second = th * 60 + tm;
    //dump(sections[i]);
    //dump(sections[i+N]);
  }

  // グラフ作成
  // V[i]: 「i番目のカップルが式前の祭典を行う
  // V[i+N]: 「i番目のカップルが式後の祭典を行う
  // V[i+2N]: 「not i番目のカップルが式前の祭典を行う」
  // V[i+3N]: 「not i番目のカップルが式後の祭典を行う」
  V = N * 4;

  // カップルは式の前か後どちらかに祭典を行う制約
  REP(i, N) {
    add_edge(i, i+3*N);
    add_edge(i+3*N, i);
    add_edge(i+N, i+2*N);
    add_edge(i+2*N, i+N);
  }

  // 重なった時間帯には祭典を開催できない制約
  REP(i, sections.size()) {
    REP(j, sections.size()) {
      if (i%N == j%N) continue;
      if (sections[i].second > sections[j].first &&
          sections[j].second > sections[i].first) {
        //cerr << " addEdge: " << i << "->" << j << endl;
        add_edge(i, j + 2*N);
      }
    }
  }

  // 強連結成分分解
  int compNum = scc();

  /*
  REP(i, N) {
    cerr << cmp[i] << " " << cmp[i+2*N] << endl;
    cerr << cmp[i+N] << " " << cmp[i+3*N] << endl;
  }
  */
  
  // 強連結成分の中にAと¬Aが含まれていないかチェックする
  REP(i, N) {
    if (cmp[i] == cmp[i+2*N] || cmp[i+N] == cmp[i+3*N]) {
      cout << "NO" << endl;
      return 0;
    }
  }

  // 解の復元。Aが¬Aよりもトポロジカル順序が後なら、Aを真にする
  cout << "YES" << endl;
  REP(i, N) {
    if (cmp[i] > cmp[i+2*N]) {
      printf("%02d:%02d %02d:%02d\n", sections[i].first / 60, sections[i].first % 60,
          sections[i].second / 60, sections[i].second % 60);
    } else {
      printf("%02d:%02d %02d:%02d\n", sections[i+N].first / 60, sections[i+N].first % 60,
          sections[i+N].second / 60, sections[i+N].second % 60);
    }
  }

}

