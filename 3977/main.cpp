// Used: 6896K	4329MS
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
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

const LL INF = 100000000000000000;
inline LL ABS(LL n) { return n < 0 ? -n : n; }

LL sum1[1 << 18];
pair<LL, int> sum2[1 << 18];

int bit_count(int n) {
  int res = 0;
  while (n) {
    if (n & 1) res++;
    n >>= 1;
  }
  return res;
}

pair<LL, int> get_min(int half, int n, vector<LL> &a) {
  LL max_v = INF;
  LL max_c = 0;

  int num1 = 1 << half;
  for (int i = 0; i < num1; i++) {
    sum1[i] = 0;
    for (int j = 0; j < half; j++) if (i & (1 << j)) sum1[i] += a[j];
  }
  
  int num2 = 1 << (n - half);
  for (int i = 0; i < num2; i++) {
    sum2[i].first = 0;
    for (int j = 0; j < (n-half); j++) if (i & (1 << j)) {
      sum2[i].first += a[half + j];
    }
    sum2[i].second = i;
  }
  sort(sum2, sum2 + num2);

  for (int i = 1; i < num1; i++) {
    int j = lower_bound(sum2, sum2 + num2, make_pair(-sum1[i], 0)) - sum2;
    if (j != num2) {
      LL sum = ABS(sum1[i] + sum2[j].first);
      if (sum < max_v) {
        max_v = sum;
        max_c = bit_count(i) + bit_count(sum2[j].second);
      } else if (sum == max_v && bit_count(i) + bit_count(sum2[j].second) < max_c) {
        max_c = bit_count(i) + bit_count(sum2[j].second);
      }
    }
    if (j != 0) {
      j--;
      LL sum = ABS(sum1[i] + sum2[j].first);
      if (sum < max_v) {
        max_v = sum;
        max_c = bit_count(i) + bit_count(sum2[j].second);
      } else if (sum == max_v && bit_count(i) + bit_count(sum2[j].second) < max_c) {
        max_c = bit_count(i) + bit_count(sum2[j].second);
      }
    }
  }

  return make_pair(max_v, max_c);
}

void solve(int n, vector<LL>& a) {
  if (n != 1) {
    int half = n / 2;

    pair<LL, int> ans1 = get_min(half, n, a);
    reverse(a.begin(), a.end());
    pair<LL, int> ans2 = get_min(n-half, n, a);

    pair<LL, int> ans = min(ans1, ans2);
    cout << ans.first << " " << ans.second << endl;
  } else {
    cout << ABS(a[0]) << " " << n << endl;
  }
}


int main() {
  cin.tie(0);
  ios::sync_with_stdio(false);

  while (true) {
    int n; cin >> n;
    if (n == 0) break;

    vector<LL> a(n);
    REP(i, n) cin >> a[i];
    
    solve(n, a);
  }
}
