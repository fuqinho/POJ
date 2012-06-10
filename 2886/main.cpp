// Used: 16084K	1563MS
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

typedef pair<int, int> PII;

// constants
const int MAX_N = 500000;
const int antiprime[]={1,2,4,6,12,24,36,48,60,120,180,240,360,720,840,1260,1680,2520,5040,7560,10080,15120,20160,25200,27720,45360,50400,55440,83160,110880,166320,221760,277200,332640,498960,554400,665280};
const int factorNum[]={1,2,3,4,6,8,9,10,12,16,18,20,24,30,32,36,40,48,60,64,72,80,84,90,96,100,108,120,128,144,160,168,180,192,200,216,224};

// input
char names[MAX_N][11];
int nums[MAX_N];
int N, K;

// variables
vector<int> primes;
int facnum[MAX_N];
int luckiest[MAX_N];

struct SegTree {
  int size;
  vector<int> dat;
  SegTree(int n) {
    size = 1;
    while (size < n) size <<= 1;
    dat = vector<int>(size * 2 - 1);

    for (int i = 0; i < n; i++) dat[i+(size-1)] = 1;
    init(0);
  }
  int init(int k) {
    if (k >= (size-1)) return dat[k];
    return dat[k] = init(k*2+1) + init(k*2+2);
  }
  void update(int k, int a) {
    k += size - 1;
    dat[k] = a;
    while (k > 0) {
      k = (k-1) / 2;
      dat[k] = dat[k*2+1] + dat[k*2+2];
    }
  }
  // [a, b)の合計を求める
  int query(int a, int b) { return query(a, b, 0, 0, size); }
  int query(int a, int b, int k, int l, int r) {
    if (b <= l || a >= r) return 0;
    if (a <= l && r <= b) return dat[k];
    
    int v1 = query(a, b, k*2+1, l, (l+r)/2);
    int v2 = query(a, b, k*2+2, (l+r)/2, r);
    return v1 + v2;
  }
  // 最初の要素からの合計がsumになる最初の要素のindexを返す
  int find(int sum) { return find(sum, 0); }
  int find(int sum, int k) {
    if (dat[k] < sum) return 1000000000;
    if (k >= size-1) return k - (size - 1);

    if (dat[k*2+1] >= sum) return find(sum, k*2+1);
    else return find(sum-dat[k*2+1], k*2+2);
  }
};

int find_kth(int cur, int rem, int k, SegTree& tree) {
  int tgt = tree.query(0, cur) + (k > 0 ? k-1 : k);

  if (tgt < 0) tgt += rem * (-tgt / rem + 1);
  tgt %= rem;

  int next = tree.find(tgt+1);
  return next;
}

PII get_luckiest(int n) {
  PII ans;
  for (int i = 0; ; i++) {
    if (antiprime[i] <= n) {
      ans.first = antiprime[i]-1;
      ans.second = factorNum[i];
    } else {
      break;
    }
  }
  return ans;
}

PII solve() {
  int cur = K-1;
  int rem = N;

  SegTree tree(N);
  PII luckiest = get_luckiest(N);

  for (int i = 0; i < luckiest.first; i++) {
    tree.update(cur, 0);
    rem--;
    cur = find_kth(cur, rem, nums[cur], tree);
  }
  
  return PII(cur, luckiest.second);
}

int main() {
  while (scanf("%d %d", &N, &K) == 2) {
    for (int i = 0; i < N; i++) {
      scanf("%s %d", names[i], &nums[i]);
    }
    PII ans = solve();
    printf("%s %d\n", names[ans.first], ans.second); 
  }
}
