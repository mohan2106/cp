#include<bits/stdc++.h>
#include<stdio.h>

using namespace std;


void update(long long *lazy,long long *tree,int node,int start,int end,int left,int right,long long inc){
    if(lazy[node]!=0){
        tree[node] += (end - start +1)*lazy[node];
        if(start!=end){
            lazy[2*node] += lazy[node];
            lazy[2*node+1] += lazy[node];
        }
        lazy[node] = 0;
    }
    if(start > end || left>end || right < start){
        return;
    }
    //compleete overlap
    if(start>=left && end <= right){
        tree[node] += (end - start +1)*inc;
        if(start!=end){
            lazy[2*node] += inc;
            lazy[2*node + 1] += inc;
        }
        return;
    }
    int mid = (start + end)/2;
    update(lazy,tree,2*node,start,mid,left,right,inc);
    update(lazy,tree,2*node +1,mid+1,end,left,right,inc);
    tree[node]  = tree[2*node] + tree[2*node +1];
    return;
}
long long query(long long *lazy,long long *tree,int start,int end,int left,int right,int node){
    if(lazy[node]!=0){
        tree[node] += (end - start +1)*lazy[node];
        if(start!=end){
            lazy[2*node] += lazy[node];
            lazy[2*node+1] += lazy[node];
        }
        lazy[node] = 0;
    }

    if(start>end){
        return 0;
    }
    if(start>right || end<left){
        return 0;
    }
    //complete overlapping
    if(left<=start && right>=end){
        return tree[node];
    }
    int mid = (start + end)/2;
    long long  t1=query(lazy,tree,start,mid,left,right,2*node);
    long long  t2=query(lazy,tree,mid+1,end,left,right,2*node +1);
    
    return t1+t2;
    
}
void solve(){
    int n,c;
    cin>>n>>c;
    int t = 1;
    while(t<n){
        t = t<<1;
    }
    long long tree[2*t];
    long long lazy[2*t];
    for(int i=0;i<2*t;i++){
        tree[i] = 0;
        lazy[i] = 0;
    }


    while(c--){
        int z;
        cin>>z;
        if(z==0){
            long long l,r,v;
            cin>>l>>r>>v;
            update(lazy,tree,1,0,n-1,l-1,r-1,v);
        }else{
            int l,r;
            cin>>l>>r;
            long long ans = query(lazy,tree,0,n-1,l-1,r-1,1);
            cout<<ans<<'\n';
        }
    }
}

int main() {

    int t;
    cin>>t;
    while(t--){
        solve();
    }
    
    return 0;
	// Write your code here
}
