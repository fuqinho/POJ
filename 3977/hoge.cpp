#include <iostream>
#include <map>
#include <algorithm>
using namespace std;

#define rep(i,n) for(int i=0;i<(n);++i)
#define mp make_pair
#define F first
#define S second
typedef long long ll;

int n;
ll in[35];

ll ABS(ll in){
  if(in<0)return -in;
  return in;
}

pair<ll,int> solve(){
  rep(i,n)
    cin>>in[i];

  ll ans=ABS(in[0]);
  int anum=1;
  
  map<ll,int> app;
  rep(i,(1<<n/2)){
    ll sum=0;
    int num=0;
    rep(j,n/2)
      if(i>>j&1){
        sum+=in[j];
        ++num;
      }
    if(!num)continue;
    pair<ll,int> ta=min(mp(ans,anum),mp(ABS(sum),num));
    ans=ta.F;
    anum=ta.S;

    if(app.count(sum)){
      int t=app[sum];
      app[sum]=min(num,t);
    }else app[sum]=num;
  }


  rep(i,(1<<n-n/2)){
    ll sum=0;
    int num=0;
    rep(j,n-n/2)
      if(i>>j&1){
        sum+=in[j+n/2];
        ++num;
      }
    if(!num)continue;
    pair<ll,int> ta=min(mp(ans,anum),mp(ABS(sum),num));
    ans=ta.F;
    anum=ta.S;    

    map<ll,int>::iterator p=app.lower_bound(-sum);
    if(p!=app.end()){
      ta=min(mp(ans,anum),mp(ABS(sum+p->F),num+p->S));
      ans=ta.F;
      anum=ta.S;
    }

    if(p!=app.begin()){
      --p;
      ta=min(mp(ans,anum),mp(ABS(sum+p->F),num+p->S));
      ans=ta.F;
      anum=ta.S;          
    }
  }
  cout<<ABS(ans)<<' '<<anum<<endl;
  return mp(ABS(ans),anum);
}


int main(){
  while(cin>>n,n){
    solve();
  }
}

