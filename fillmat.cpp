#include<bits/stdc++.h>
using namespace std;

int root(int v,vector<int> &parent){
    if(v == parent[v]){
        return v;
    }
    return parent[v] = root(parent[v],parent);
}

void union_set(int x,int y,vector<int> &parent,vector<int> &rank){
    x = root(x,parent);
    y = root(y,parent);
    if(x != y){
        if(rank[x]<rank[y]){
            swap(x,y);
        }
        parent[y] = x;
        if(rank[x] == rank[y]){
            rank[x]++;
        }
    }
}

bool checkBipartite(vector<int> g[],int n,int *vis,int *color,int s){
    queue<int> q;
    color[s] = 1;
    q.push(s);
    while(!q.empty()){
        int t = q.front();
        q.pop();
        if(vis[t]) continue;
        vis[t] = 1;
        for(int x:g[t]){
            if(vis[x]){
                if(color[x]==color[t]){
                    return false;
                }
            }else{
                color[x] = 3-color[t];
                q.push(x);
            }
        }
    }
    return true;
}


void solve(){
    int n,q;
    cin>>n>>q;
    vector<int> id(n+1),rank(n+1);
    for(int i=0;i<=n;i++){
        id[i] = i;
    }
    bool flag=true;
    vector<pair<int,int>> vp;
    for(int i=0;i<q;i++){
        int a,b,c;
        cin>>a>>b>>c;
        if(c){
            int x = root(a,id);
            int y = root(b,id);
            if(x==y){
                flag = false;
            }else{
                vp.push_back({x,y});
            }
        }else{
            union_set(a,b,id,rank);
        }
    }
    if(!flag){
        cout<<"no\n";
    }else{
        map<pair<int,int>,int> mp;
        for(auto it:vp){
            int x = root(it.first,id);
            int y = root(it.second,id);
            mp[{x,y}] = 1;
        }
        vector<int> g[n+1];
        for(auto it=mp.begin();it!=mp.end();it++){
            int x = (it->first).first;
            int y = (it->first).second;
            g[x].push_back(y);
            g[y].push_back(x);
        }
        
        int vis[n+1];
        int color[n+1];
        memset(vis,0,sizeof(vis));
        memset(color,0,sizeof(color));
        bool flag = true;
        for(int i=1;i<=n;i++){
            if(!vis[i]){
                bool ans = checkBipartite(g,n,vis,color,i);
                if(!ans){
                    flag = false;
                    break;
                }
            }
        }
        if(flag)
            cout<<"yes\n";
        else{
            cout<<"no\n";
        }
        
    }
    
}

int main()
{
	//code
    int t;
    cin>>t;
    while(t--){
        solve();
    }
    
	return 0;
}
