#include<bits/stdc++.h>
using namespace std;
struct node1{
    int sos,sum;
};
struct node2{
    int value,type;
};
void buildtree(int arr[],node1* tree,int start,int end,int tnode)
{
    if(start==end)
    {
        tree[tnode].sos = arr[start]*arr[start];
        tree[tnode].sum = arr[start];
        return;
    }
    int mid = (start+end)/2;
    buildtree(arr,tree,start,mid,2*tnode);
    buildtree(arr,tree,mid+1,end,2*tnode+1);
    tree[tnode].sos = (tree[2*tnode].sos+tree[2*tnode+1].sos);
    tree[tnode].sum = (tree[2*tnode].sum + tree[2*tnode+1].sum);
    
}
node1 query(node1* tree,int start,int end,int tnode,int left,int right,node2* lazy)
{
    if(start>end)
    {
        node1 zero = {0,0};
        return zero;
    }
    //checking if lazy tree has any value at thet tnode
    if(lazy[tnode].value!=0)
    {
        if(lazy[tnode].type==1)
        {	//increment
            tree[tnode].sos += lazy[tnode].value*lazy[tnode].value*(end-start+1)
                                + 2*lazy[tnode].value*(tree[tnode].sum);
            tree[tnode].sum += lazy[tnode].value*(end-start+1);
            if(start!=end) //child nodes hen
            {
                lazy[2*tnode].value += lazy[tnode].value;
                lazy[2*tnode].type = lazy[tnode].type;
                lazy[2*tnode+1].value += lazy[tnode].value;
                lazy[2*tnode+1].type = lazy[tnode].type;
            }
            lazy[tnode].value=0;
            lazy[tnode].type=0;
        }
        if(lazy[tnode].type == 2)
        {	//change
            tree[tnode].sos = lazy[tnode].value*lazy[tnode].value*(end-start+1);
            tree[tnode].sum = lazy[tnode].value * (end-start+1);
            if(start!=end)
            {
                lazy[2*tnode].value = lazy[tnode].value;
                lazy[2*tnode].type = lazy[tnode].type;
                lazy[2*tnode+1].value = lazy[tnode].value;
                lazy[2*tnode+1].type = lazy[tnode].type;
            }
            lazy[tnode].value =0;
            lazy[tnode].type =0;
        }
    }
    //no overlap
    if(end<left||right<start)
    {
        node1 zero = {0,0};
        return zero;
    }
    //full overlap
    if(left<=start&&end<=right)
    {
        return tree[tnode];
    }
    //partial
    int mid = (start+end)/2;
    node1 ans1 = query(tree,start,mid,2*tnode,left,right,lazy);
    node1 ans2 = query(tree,mid+1,end,2*tnode+1,left,right,lazy);
    node1 ans;
    ans.sos = ans1.sos+ans2.sos;
    ans.sum = ans1.sum+ans2.sum;
    return ans;
    
}
    
void updatelazy(node1* tree,node2* lazy,int start,int end,int tnode,int left,int right,int inc,int a)
{

    if(lazy[tnode].value!=0)
    {
        if(lazy[tnode].type==1)
        {	//increment
            tree[tnode].sos += lazy[tnode].value*lazy[tnode].value*(end-start+1)
                                + 2*lazy[tnode].value*(tree[tnode].sum);
            tree[tnode].sum += lazy[tnode].value*(end-start+1);
            if(start!=end) //child nodes hen
            {
                lazy[2*tnode].value += lazy[tnode].value;
                lazy[2*tnode].type = lazy[tnode].type;
                lazy[2*tnode+1].value += lazy[tnode].value;
                lazy[2*tnode+1].type = lazy[tnode].type;
            }
            lazy[tnode].value=0;
            lazy[tnode].type=0;
        }
        if(lazy[tnode].type == 2)
        {	//change
           tree[tnode].sos = lazy[tnode].value*lazy[tnode].value*(end-start+1);
            tree[tnode].sum = lazy[tnode].value*(end-start+1);
            if(start!=end)
            {
                lazy[2*tnode].value = lazy[tnode].value;
                lazy[2*tnode].type = lazy[tnode].type;
                lazy[2*tnode+1].value = lazy[tnode].value;
                lazy[2*tnode+1].type = lazy[tnode].type;
            }
            lazy[tnode].value =0;
            lazy[tnode].type =0;
            
        }
    }
    //find that query to update
    //outside
    if(end<left || start>right)
    {
        return;
    }
    //full overlap
    if(left<=start&&end<=right)
    {
        if(a==1)  //increment
        {
            tree[tnode].sos += inc*inc*(end-start+1)+2*inc*(tree[tnode].sum);
            tree[tnode].sum += inc*(end-start+1);
            //ab bacho pe daal de inc value aur type 1 krde
            if(start!=end)
            {
                lazy[2*tnode].value += inc;
                lazy[2*tnode].type =1;
                lazy[2*tnode+1].value+= inc;
                lazy[2*tnode+1].type=1;
            }
            return;
        }
        if(a==0)
        {
            //we have to change the value
            tree[tnode].sos = inc*inc*(end-start+1);
            tree[tnode].sum = inc*(end-start+1);
            if(start!=end)
            {
                lazy[2*tnode].value = inc;
                lazy[2*tnode].type = 2;
                lazy[2*tnode+1].value = inc;
                lazy[2*tnode+1].type = 2;
            }
            return;
        }
    }
    //partial, call for left and right node
    int mid = (start+end)/2;
    updatelazy(tree,lazy,start,mid,2*tnode,left,right,inc,a);
    updatelazy(tree,lazy,mid+1,end,2*tnode+1,left,right,inc,a);
    tree[tnode].sos = (tree[2*tnode].sos+tree[2*tnode+1].sos);
    tree[tnode].sum = (tree[2*tnode].sum + tree[2*tnode+1].sum);
}
    
int main() 
{
    int t;
    cin>>t;
    int i=1;
    while(t--)
    {
        cout<<"Case "<<i<<":"<<endl;
        i++;
        int n,q;
        cin>>n>>q;
        int arr[n];
        for(int i=0;i<n;i++)
        {
            cin>>arr[i];
        }
        node1* tree = new node1[4*n];
        node2* lazy = new node2[4*n];
        for(int i=1;i<4*n;i++)
        {
            lazy[i].value=0;
            lazy[i].type=0;
            tree[i].sos=0;
            tree[i].sum=0;
        }
        buildtree(arr,tree,0,n-1,1);
        while(q--)
        {
            int a;
            cin>>a;
            if(a==2)
            {
                int l,r;
                cin>>l>>r;
                node1 ans = query(tree,0,n-1,1,l-1,r-1,lazy);
                cout<<ans.sos<<endl;
            }
            if(a==1||a==0)
            {
                int l,r,inc;
                cin>>l>>r>>inc;
                updatelazy(tree,lazy,0,n-1,1,l-1,r-1,inc,a);
            }
        }
    }
	return 0;
}
