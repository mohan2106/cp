#include<bits/stdc++.h>
#include<stdio.h>

using namespace std;


void buildTree(char *arr,int *tree,int start,int end,int node){
    if(start>end) return;
    if(start == end){
        tree[node] = arr[start]-'0';
        return;
    }
    int mid = (start + end)/2;
    buildTree(arr,tree,start,mid,2*node);
    buildTree(arr,tree,mid+1,end,2*node + 1);
    int t = 1;
    if((end-mid)%2){
        t = 2;
    }
    tree[node] = (tree[2*node]*t + tree[2*node + 1])%3;
    return;
}
void update(char *arr,int *tree,int start,int end,int index,int node){
    if(start == end && start == index){
        arr[start]  ='1';
        tree[node] = 1;
        return;
    }
    int mid = (start + end)/2;
    if(index <= mid){
        update(arr,tree,start,mid,index,2*node);
    }else{
        update(arr,tree,mid+1,end,index,2*node + 1);
    }
    int t = 1;
    if((end-mid)%2){
        t = 2;
    }
    tree[node] = (tree[2*node]*t + tree[2*node + 1])%3;
    return;
}
pair<int,int> query(int *tree,int start,int end,int left,int right,int node){
    if(start>end){
        return {-1,0};
    }
    if(start>right || end<left){
        return {-1,0};
    }
    //complete overlapping
    if(left<=start && right>=end){
        return {tree[node],end - start +1};
    }
    int mid = (start + end)/2;
    pair<int,int> t1=query(tree,start,mid,left,right,2*node);
    pair<int,int> t2=query(tree,mid+1,end,left,right,2*node +1);
    int t = 1;
    if((t2.second)%2){
        t = 2;
    }
    
    if(t1.first== (-1) && t2.first == -1){
        return {-1,0};
    }else if(t1.first == -1){
        return t2;
    }else if(t2.first == -1){
        return t1;
    }else{
        return {((t1.first)*t + (t2.first))%3,t1.second + t2.second};
        // return comp(arr,t1,t2);
    }
    
}

int main() {
    
    int n;
    cin>>n;
    string str;
    cin>>str;
    char arr[n+1];
    for(int i=0;i<n;i++){
        arr[i] = str[i];
    }
    arr[n] = '\0';
    int t = 1;
    while(t<n){
        t = t<<1;
    }
    int *tree = new int[2*t];
    buildTree(arr,tree,0,n-1,1);
    // for(int i=0;i<2*t;i++){
    //     cout<<tree[i]<<" ";
    // }
    // cout<<'\n';
    
    int q;
    cin>>q;
    while(q--){
        int z;
        cin>>z;
        if(z==0){
            int l,r;
            cin>>l>>r;
            pair<int,int> ans =query(tree,0,n-1,l,r,1);
            cout<<ans.first<<'\n';
        }else{
            int l;
            cin>>l;
            update(arr,tree,0,n-1,l,1);
        }
    }
	// Write your code here
}
