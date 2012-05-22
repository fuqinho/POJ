// Limit: 65536K / 1000ms
// Used :   640K /   47ms
#include <vector>
#include <queue>
#include <algorithm>
#include <cstdio>
using namespace std;

typedef pair<int, int> PII;

int solve(int C, int L, vector<PII>& cows, vector<PII>& lotions) {
  // cowはminSPFの昇順に、lotionはSPFの昇順にソートしておく
  sort(cows.begin(), cows.end());
  sort(lotions.begin(), lotions.end());

  int queuedCows = 0;
  priority_queue<int, vector<int>, greater<int> > que;

  int res = 0;
  // 各lotionについて…
  for (int i = 0; i < lotions.size(); i++) {
    // minSPFが注目しているlotionのSPF以下になっている牛のmaxSPFをqueueに追加
    while (queuedCows < C && cows[queuedCows].first <= lotions[i].first) {
      que.push(cows[queuedCows].second);
      queuedCows++;
    }
    // queueからmaxSPFを値が小さい順に取り出し、それが注目しているlotionのSPF値以上であれば
    // lotionを使用する
    while (!que.empty() && lotions[i].second != 0) {
      int maxVal = que.top(); que.pop();
      if (maxVal >= lotions[i].first) {
        res++;
        lotions[i].second--;
      }
    }
  }
  return res;
}

int main() {
  int C, L; scanf("%d %d", &C, &L);
  vector<PII> cows(C);
  for (int i = 0; i < C; i++) scanf("%d %d", &cows[i].first, &cows[i].second);
  vector<PII> lotions(L);
  for (int i = 0; i < L; i++) scanf("%d %d", &lotions[i].first, &lotions[i].second);

  int ans = solve(C, L, cows, lotions);
  printf("%d\n", ans);
}
