/*
Segment trees are extremely useful. In particular "Lazy Propagation" (i.e. see here, for example) allows one to 
compute sums over a range in O(lg(n)), and update ranges in O(lg(n)) as well. In this problem you will compute 
something much harder:
The sum of squares over a range with range updates of 2 types:
1) increment in a range
2) set all numbers the same in a range.

=======================INPUT=========================
There will be T (T <= 25) test cases in the input file. First line of the input contains two positive integers,
N (N <= 100,000) and Q (Q <= 100,000). 
The next line contains N integers, each at most 1000. Each of the next Q lines starts with a number, 
which indicates the type of operation:

2 st nd -- return the sum of the squares of the numbers with indices in [st, nd] {i.e., from st to nd inclusive} 
(1 <= st <= nd <= N).

1 st nd x -- add "x" to all numbers with indices in [st, nd] (1 <= st <= nd <= N, and -1,000 <= x <= 1,000).

0 st nd x -- set all numbers with indices in [st, nd] to "x" (1 <= st <= nd <= N, and -1,000 <= x <= 1,000).
======================OUTPUT=========================
For each test case output the “Case <caseno>:” in the first line and from the second line 
output the sum of squares for each operation of type 2. Intermediate overflow will not occur 
with proper use of 64-bit signed integer.

==================SAMPLE CASE=========================
2
4 5
1 2 3 4
2 1 4
0 3 4 1
2 1 4
1 3 4 1
2 1 4
1 1
1
2 1 1
=================SAMPLE OUTPUT=======================
Case 1:
30
7
13
Case 2:
1

*/


#include<bits/stdc++.h>
using namespace std;
struct treeNode{
    int sq;
    int sum;
};

struct lazyNode{
    int val;
    int type;
};

void buildTree(int *arr,treeNode *tree,int start,int end,int node){
    if(start == end){
        tree[node].sum = arr[start];
        tree[node].sq = (arr[start])*arr[start];
        return;
    }
    int mid = (start + end)/2;
    buildTree(arr,tree,start,mid,2*node);
    buildTree(arr,tree,mid+1,end,2*node + 1);
    tree[node].sum = tree[2*node].sum + tree[2*node + 1].sum;
    tree[node].sq = tree[2*node].sq + tree[2*node + 1].sq;
    return;
}
int query(lazyNode *lazy,treeNode *tree,int start,int end,int left,int right,int node){
    if(left > end || right < start){
        return 0;
    }
    if(lazy[node].val != 0){
        if(lazy[node].type == 1){
            tree[node].sq += ((end-start + 1)*(lazy[node].val)*(lazy[node].val) + 2*(tree[node].sum)*((lazy[node].val)));
            tree[node].sum += (end-start +1)*(lazy[node].val);
        }else{
            tree[node].sq = (end-start + 1)*(lazy[node].val)*(lazy[node].val);
            tree[node].sum = (end-start +1)*(lazy[node].val);
        }
        if(start!=end){
            lazy[2*node] = lazy[node];
            lazy[2*node + 1] = lazy[node];
        }
        lazy[node].val = 0;
    }
    if(start >=left && end <= right){
        return tree[node].sq;
    }
    int mid = (start + end)/2;
    int t1 = query(lazy,tree,start,mid,left,right,2*node);
    int t2 = query(lazy,tree,mid+1,end,left,right,2*node+1);
    return t1+t2;
}
void updateTreeLazy1(treeNode *tree,lazyNode *lazy,int start,int end,int node,int left,int right,int inc,int type){
    
    int z;

    if(lazy[node].val!=0){
        if(lazy[node].type == 1){
            tree[node].sq += ((end-start + 1)*(lazy[node].val)*(lazy[node].val) + 2*(tree[node].sum)*((lazy[node].val)));
            tree[node].sum += (end-start +1)*(lazy[node].val);
        }else{
            tree[node].sq = (end-start + 1)*(lazy[node].val)*(lazy[node].val);
            tree[node].sum = (end-start +1)*(lazy[node].val);
        }
        if(start!=end){
            lazy[2*node] = lazy[node];
            lazy[2*node + 1] = lazy[node];
        }
        lazy[node].val = 0;
    }
    
    if(start>end || left > end || right < start){
        return;
    }
    if(left<=start && right>=end){
        if(type == 1){
            tree[node].sq += ((end-start + 1)*(inc)*(inc) + 2*(tree[node].sum)*((inc)));
            tree[node].sum += (end-start +1)*(inc);
            if(start!=end){
                lazy[2*node].val += inc;
                lazy[2*node + 1].val += inc;
                lazy[2*node].type = 1;
                lazy[2*node + 1].type = 1;
            }else{
                //do nothing
                z = 1;
            }
            return;
        }else{
            tree[node].sq = ((end-start + 1)*(inc)*(inc));
            tree[node].sum = (end-start +1)*(inc);
            if(start!=end){
                lazy[2*node] = {inc,2};
                lazy[2*node + 1] = {inc,2};
            }
        }
        
        return;
    }
    int mid = (start + end)/2;
    updateTreeLazy1(tree,lazy,start,mid,2*node,left,right,inc,type);
    updateTreeLazy1(tree,lazy,mid+1,end,2*node + 1,left,right,inc,type);
    tree[node].sq = tree[2*node].sq + tree[2*node  + 1].sq;
    tree[node].sum = tree[2*node].sum + tree[2*node + 1].sum;
    return;
}

void solve(){
    int n,q;
    cin>>n>>q;
    int arr[n];
    for(int i=0;i<n;i++){
        cin>>arr[i];
    }
    int t=1;
    while(t<n){
        t = t<<1;
    }
    treeNode *tree = new treeNode[2*t];
    lazyNode *lazy = new lazyNode[2*t];
    for(int i=0;i<2*t;i++){
        lazy[i] = {0,0};
    }
    buildTree(arr,tree,0,n-1,1);
    while(q--){
        int z;
        cin>>z;
        if(z==2){
            int a,b;
            cin>>a>>b;
            int ans = query(lazy,tree,0,n-1,a-1,b-1,1);
            cout<<ans<<'\n';
        }else{
            int a,b,c;
            cin>>a>>b>>c;
            if(z == 1){
                updateTreeLazy1(tree,lazy,0,n-1,1,a-1,b-1,c,1);
            }else{
                updateTreeLazy1(tree,lazy,0,n-1,1,a-1,b-1,c,2);
            }
        }
    }
}

int main() {

    int t;
    cin>>t;
    int k=1;
    while(t--){
        cout<<"Case "<<k<<":"<<'\n';
        solve();
        k++;
    }
	// Write your code here
}
