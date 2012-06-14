// Limit: 30000K  5000ms
// Used :  3132K  2016ms
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <cstring>
using namespace std;

const int INF = 1000000000;
const int MAX_N = 15;

int common[MAX_N][MAX_N];
int dp[1 << MAX_N][MAX_N];
bool ok[1 << MAX_N][MAX_N];

vector<string> remove_ignorable_strings(vector<string>& S) {
  vector<bool> can_remove(S.size());
  for (int i = 0; i < S.size(); i++) {
    for (int j = 0; j < S.size(); j++) {
      if (i != j) {
        if (!can_remove[i] && S[i].find(S[j]) != string::npos) {
          can_remove[j] = true;
        }
      }
    }
  }
  vector<string> res;
  for (int i = 0; i < S.size(); i++) {
    if (!can_remove[i]) res.push_back(S[i]);
  }
  return res;
}

int common_part(string& s_head, string& s_tail) {
  for (int i = 0; i < s_head.size(); i++) {
    if (s_head[i] == s_tail[0]) {
      string s = s_head.substr(i);
      if (s_tail.find(s) == 0) {
        return s.size();
      }
    }
  }
  return 0;
}

void calc_common_part(vector<string>& S) {
  memset(common, 0, sizeof(common));
  for (int i = 0; i < S.size(); i++) {
    for (int j = 0; j < S.size(); j++) {
      if (i != j) {
        common[i][j] = common_part(S[i], S[j]);
      }
    }
  }
}

void dfs(int state, int last, string cur, string& best, vector<string>& S) {
  if (state == (1 << S.size()) - 1) {
    if (cur < best) best = cur;
    return;
  }

  for (int i = 0; i < S.size(); i++) {
    if ((state & (1<<i)) == 0 && ok[state|(1<<i)][i]) {
      if (dp[state][last] + S[i].size() - common[last][i] == dp[state|(1<<i)][i]) {
        string s = cur + S[i].substr(common[last][i]);
        if (s < best) dfs(state|(1<<i), i, s, best, S);
      }
    }
  }
}

string solve(int N, vector<string>& S) {
  // 他の文字列に完全に含まれてる文字列はあっても無くても同じなので消す
  // 深さ優先探索する時の効率化のために、辞書順でソートしておく.
  S = remove_ignorable_strings(S);
  sort(S.begin(), S.end());
  N = S.size();

  // common[i][j]: S[i]の後ろにS[j]を繋げた場合の共通部分の長さ
  // 後の計算でよく使うので事前計算しておく。
  calc_common_part(S);

  // dp[S][i]: Sに含まれる文字列を繋げて最後がS[i]になっている場合の最短の長さ
  for (int i = 0; i < (1<<N); i++) {
    for (int j = 0; j < N; j++) dp[i][j] = INF;
  }
  for (int i = 0; i < N; i++) dp[(1 << i)][i] = S[i].size();

  // bit DPして各状態の最短の長さを求めておく
  for (int s = 0; s < (1 << N); s++) {
    for (int i = 0; i < N; i++) if (dp[s][i] != INF) {
      for (int j = 0; j < N; j++) if ((s & (1 << j)) == 0) {
        int next_s = (s | (1<<j));
        dp[next_s][j] = min(dp[next_s][j],
                            dp[s][i] + (int)S[j].size() - common[i][j]);
      }
    }
  }

  // 答えになる文字列の長さが求まる。残りは文字列を復元する作業
  int min_length = INF;
  for (int i = 0; i < N; i++) min_length = min(min_length, dp[(1<<N)-1][i]);

  // ok[s][i]: sに含まれる文字列を連結して最後がiになっている状態が、
  // 最適解への経路になり得る場合はtrueにする
  memset(ok, 0, sizeof(ok));
  for (int i = 0; i < N; i++) {
    if (dp[(1<<N)-1][i] == min_length) ok[(1<<N)-1][i] = true;
  }
  for (int s = (1<<N)-1; s >= 0; s--) {
    for (int i = 0; i < N; i++) if (ok[s][i]) {
      for (int j = 0; j < N; j++) if (i != j && (s & (1<<i))) {
        if (dp[s & ~(1<<i)][j] == dp[s][i] - S[i].size() + common[j][i]) {
          ok[s & ~(1<<i)][j] = true;
        }
      }
    }
  }

  // 辞書順で最も小さい解を深さ優先探索で求める
  string best = "Z";
  for (int i = 0; i < N; i++) {
    if (ok[1<<i][i]) dfs(1<<i, i, S[i], best, S);
  }
  return best;
}

int main() {
  cin.tie(0);
  ios::sync_with_stdio(false);

  int T; cin >> T;
  for (int t = 0; t < T; t++) {
    int N; cin >> N;
    vector<string> S(N);
    for (int i = 0; i < N; i++) cin >> S[i];

    string ans = solve(N, S);
    cout << "Scenario #" << t+1 << ":\n" << ans << endl << endl;
  }
}
