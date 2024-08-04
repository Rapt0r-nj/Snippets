
#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<ll, ll>;

const ll N=2e5+5, mod=998244353;

using treenode = ll;
using lazynode = ll;
#define fir(a) for(int i=0; i<a; i++)

treenode treeidn = 0;
lazynode lazyidn = 0;

vector<ll> v(N);
vector<treenode> tree(4*N, treeidn);
vector<lazynode> lazy(4*N, lazyidn);

treenode merge(treenode &a, treenode &b){
  return (a+b);
}
void lazyapply(treenode &to, ll l, ll r, lazynode fr){
  ll s=0;
  fir(fr){
    while(to){
      s+=to%10;
      to/=10;
    }
    to=s; s=0;
  }
}
void lazymerge(lazynode &to, lazynode fr){
  to=to+fr;
}
void build(ll id, ll l, ll r){
  if(l==r){
    tree[id]=v[l];
    lazy[id]=lazyidn;
    return;
  }
  ll m=(l+r)/2;
  build(id*2+1, l, m);
  build(id*2+2, m+1, r);
  tree[id] = merge(tree[id*2+1], tree[id*2+2]);
  lazy[id] = lazyidn;
}
void push(ll id, ll l, ll r){
  if(l-r){
    ll m=(l+r)/2;
    lazyapply(tree[2*id+1], l, m, lazy[id]);
    lazymerge(lazy[2*id+1], lazy[id]);

    lazyapply(tree[2*id+2], m+1, r, lazy[id]);
    lazymerge(lazy[2*id+2], lazy[id]);

    lazy[id]=lazyidn;
  }
}
treenode query(ll id, ll l, ll r, ll ql, ll qr){
  push(id, l, r);
  if(ql<=l && r<=qr) return tree[id];
  if(ql>r || qr<l) return treeidn;
  
  ll m=(l+r)/2;
  treenode tl=query(id*2+1, l, m, ql, qr);
  treenode tr=query(id*2+2, m+1, r, ql, qr);
  return merge(tl, tr);
}
void update(ll id, ll l, ll r, ll ul, ll ur, lazynode uv){
  push(id, l, r);
  if(ul<=l && r<=ur){
    lazyapply(tree[id], l, r, uv);
    lazymerge(lazy[id], uv);
    return;
  }
  if(ul>r || ur<l) return;
  
  ll m=(l+r)/2;
  update(id*2+1, l, m, ul, ur, uv);
  update(id*2+2, m+1, r, ul, ur, uv);
  tree[id]=merge(tree[id*2+1], tree[id*2+2]);
  return;
}

void solve(){
  ll n, q; cin>>n>>q;
  fir(n) cin>>v[i];

  build(0, 0, n-1);

  while(q--){
    ll t; cin>>t;
    if(t==2){
      ll l, r; cin>>l;
      cout<<query(0, 0, n-1, l-1, l-1)<<"\n";
    }else{
      ll l, r, a, b; cin>>l>>r;
      update(0, 0, n-1, l-1, r-1, 1);
    }
  }
  return;
}

int main(){
  ios_base::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);

  int tt=1; cin>>tt;
  while(tt--){
    solve();
  }
  return 0;
}

