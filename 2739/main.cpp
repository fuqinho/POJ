// Used: 768K	0MS
#include <iostream>
#include <vector>
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

const int MAX_N = 10000;

vector<int> gen_prime(int max_n) {
  vector<bool> is_prime(max_n + 1, true);
  vector<int> res;
  for (int i = 2; i <= max_n; i++) {
    if (is_prime[i]) {
      res.push_back(i);
      for (int j = i*2; j <= max_n; j+=i) is_prime[j] = false;
    }
  }
  return res;
}

int solve(VI& primes, int n) {
  int count = 0;
  
  int sum = 0;
  int s = 0, t = 0;
  for (;;) {
    while (t < primes.size() && sum < n) sum += primes[t++];
    if (t == primes.size()) break;
    if (sum == n) count++;
    sum -= primes[s++];
  }

  return count;
}

int main() {
  cin.tie(0);
  ios::sync_with_stdio(false);

  VI primes = gen_prime(MAX_N);
  while (true) {
    int n; cin >> n;
    if (n == 0) break;

    int ans = solve(primes, n);
    cout << ans << endl;
  }
}
