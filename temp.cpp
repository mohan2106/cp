#include<bits/stdc++.h>
using namespace std;
#define ll long long
void update(ll *tree,ll *lazy,ll start,ll end,ll treen,ll left,ll right,ll val)
{
    if(start>end)
        return;
    if(lazy[treen]!=0)
    {
               tree[treen]+=(end-start+1)*lazy[treen];
                if(start!=end)
                {
                    lazy[treen*2]+=lazy[treen];
                    lazy[treen*2+1]+=lazy[treen];
                }
                lazy[treen]=0;
    }
    if(left>end ||  right< start)
        return;
    else if(left<=start && right>=end)
    {
        tree[treen]+=(end-start+1)*val;
        if(start!=end)
        {
            lazy[treen*2]+=val;
          	lazy[treen*2+1]+=val; 
        }
        return;
    }
    ll mid=(start+end)/2;
    update(tree,lazy,start,mid,2*treen,left,right,val);
    update(tree,lazy,mid+1,end,2*treen+1,left,right,val);
    tree[treen]=tree[treen*2]+tree[treen*2+1];    
    return;
}

ll query(ll *tree,ll *lazy,ll start,ll end,ll treen,ll left,ll right)
{   
    if(start>end)
        return 0;
   if(lazy[treen]!=0)
    {
       	ll val = lazy[treen];
               tree[treen]+=(end-start+1)*val;
                if(start!=end)
                {
                    lazy[treen*2]+=lazy[treen];
                    lazy[treen*2+1]+=lazy[treen];
                }
                lazy[treen]=0;
    }
    if(left>end ||  right< start)
        return 0;
    else if(left<=start && right>=end)
    {
        return tree[treen];
    }
    ll mid=(start+end)/2;
    ll sol1 = query(tree,lazy,start,mid,2*treen,left,right);
    ll sol2 = query(tree,lazy,mid+1,end,2*treen+1,left,right);
    
    // int ans=tree[treen*2]+tree[treen*2+1];
    
    return sol1+sol2;
}
int main() {

	// Write your code here
    int t;
    cin>>t;
    while(t--)
    {
        ll n,q;
        cin>>n>>q;
        ll a[4*n];
        for(ll i=0;i<4*n;i++)
            a[i]=0;
        ll lazy[4*n];
        for(ll i=0;i<4*n;i++)
            lazy[i]=0;
        while(q--)
        {
            ll c,l,r,v;
            cin>>c>>l>>r;
            if(c==0){
                cin>>v;
                update(a,lazy,0,n-1,1,l-1,r-1,v);
            }else{
                ll ans = query(a,lazy,0,n-1,1,l-1,r-1);
            	cout<<ans<<'\n';
            }
        }
    }
}
