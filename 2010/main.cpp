// Limit: 30000K / 1000ms
// Used :  2212K /  188ms
#include <vector>
#include <queue>
#include <algorithm>
#include <limits>
#include <cstdio>
using namespace std;

typedef pair<int, int> PII;
const int INF = numeric_limits<int>::max();

int solve(int N, int C, int F, vector<PII>& calves) {
  sort(calves.begin(), calves.end());

  vector<int> lower(C, INF), upper(C, INF);
  int half_N = N / 2;

  priority_queue<int> que;
  int sum = 0;
  for (int i = 0; i < C; i++) {
    if (que.size() == half_N) lower[i] = sum;
    if (que.size() < half_N || que.top() > calves[i].second) {
      sum += calves[i].second;
      que.push(calves[i].second);
      if (que.size() > half_N) {
        sum -= que.top();
        que.pop();
      }
    }
  }

  que = priority_queue<int>();
  sum = 0;
  for (int i = C-1; i >= 0; i--) {
    if (que.size() == half_N) upper[i] = sum;
    if (que.size() < half_N || que.top() > calves[i].second) {
      sum += calves[i].second;
      que.push(calves[i].second);
      if (que.size() > half_N) {
        sum -= que.top();
        que.pop();
      }
    }
  }

  for (int i = C - half_N - 1; i >= half_N; i--) {
    if (lower[i] != INF && upper[i] != INF) {
      int aid = lower[i] + upper[i] + calves[i].second;
      if (aid <= F) return calves[i].first;
    }
  }
  return -1;
}

int main() {
  int N, C, F; scanf("%d %d %d", &N, &C, &F);
  vector<PII> calves(C);
  for (int i = 0; i < C; i++) scanf("%d %d", &calves[i].first, &calves[i].second);

  int ans = solve(N, C, F, calves);
  printf("%d\n", ans);
}
