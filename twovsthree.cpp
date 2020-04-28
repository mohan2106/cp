#include<bits/stdc++.h>
using namespace std;

void update(int *tree,int *arr,int * number,int start,int end,int tn,int index){
    if(index<start || index>end || start>end) return;

    if(start==end && start==index){
        if(number[start]==0){
            number[start]  = 1;
            tree[tn]  =1;
        }
        return ;
    }
    int mid = (start +end)/2;
    if(index>mid){
        update(tree,arr,number,mid+1,end,2*tn+1,index);
    }else{
        update(tree,arr,number,start,mid,2*tn,index);
    }
    int k = arr[end - mid];
    
    tree[tn] = (tree[2*tn+1] + (tree[2*tn]*k))%3; 
    return;
}


int query(int *tree,int* arr, int start,int end,int li,int ri,int tn){
        if(start>ri||li>end){
                return 0;
        }
        if(start>=li&&end<=ri){
            return (tree[tn]*arr[ri-end])%3;
        }
        int mid  = (start+end)/2;
        int a = query(tree,arr,start,mid,li,ri,2*tn);
        int b= query(tree,arr,mid+1,end,li,ri,2*tn+1);
         return  (b%3 + a%3)%3;

}
void buildTree(int * number,int *tree,int *arr,int start,int end,int tn){
    
    if(start==end ){
        tree[tn] = number[start];
        return ;
    }
    int mid  = (start+end)/2;

    buildTree(number,tree,arr,start,mid,2*tn);
    buildTree(number,tree,arr,mid+1,end,2*tn+1);
    int k = arr[end - mid];
    tree[tn] = (tree[2*tn+1]%3 + tree[2*tn]*k)%3;
}

int main(){ 

    int n;
    cin>>n;
    string s;
    cin>>s;

    int * number  = new int[n+1];

    for(int i=0;i<n;i++){

        number[i+1] = s[i] - '0';
    }

    int *tree = new int [4*n];

    int *arr = new int[100001];
        arr[0] =1;
        for(int i=1;i<=100000;i++){

                arr[i] = (arr[i-1]*2)%3;
        }
    buildTree(number,tree,arr,1,n,1);

    int t;
    cin>>t;

    while(t--){

        int type;
        cin>>type;

        if(type==0){
            int first,second;
            cin>>first>>second;
            int anss = query(tree,arr,1,n,first+1,second+1,1);
            cout<<anss<<endl;

        }else{
            int index;
            cin>>index;
            update(tree,arr,number,1,n,1,index+1);

        }

    } 
    return 0;
}
