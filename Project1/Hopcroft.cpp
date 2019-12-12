//Hopcroft–Karp algorithm

#include<bits/stdc++.h>
using namespace std;

#define all(X) begin(X),end(X)
#define sz(X) (int)(X).size()
typedef long long ll;
typedef vector<bool> vb;
typedef vector<int> vi;
typedef vector<vector<int> > vvi;

void read(vvi &G);
const int alone = -1;


// Solution

bool match(int x, vvi &G, vb &visited, vi &mate){
    if(visited[x])
        return false;
    visited[x] = true;
    for(int i = 0; i<sz(G[x]); i++){
        if(!visited[G[x][i]]){
            if(mate[G[x][i]]==alone){
                mate[G[x][i]] = x;
                mate[x] = G[x][i];
                return true;
            }else{
                int z = mate[G[x][i]];
                if(match(z,G,visited,mate)){
                    mate[G[x][i]]=x;
                    mate[x]=G[x][i];
                    return true;
                }
            }
        }
    }
    return false;
}

    
void tryDummMatching(vvi &G, vi &mate){
    for(int i = 0; i < sz(G); i++){
        if(mate[i] == alone){
            for(auto k : G[i]){
                if(mate[k] == alone){
                    mate[k] = i;
                    mate[i] = k;
                    break;
                }
            }
        }
    }
}

void solve(vvi &G, vi &mate){
    mate.clear();
    mate.resize(sz(G),alone);
    
    tryDummMatching(G,mate);

    bool flag=true;
    while(flag){
        flag = false;
        vb visited(sz(G),false);
        for(int i = 0; i<sz(G); i++){
            if(mate[i] == alone){
                flag = flag || match(i,G,visited, mate);
            }
        }
    }
}

void answer(vi &mate){
    vector<pair<int,int> > ans;
    for(int i = 0; i<sz(mate); i++){
        if(mate[i] != -1){
            ans.push_back(make_pair(i,mate[i]));
            mate[mate[i]]=-1;
        }
    }
    cout<<sz(ans)<<endl;
    for(auto i : ans){
        cout<<i.first<<' '<<i.second<<endl;
    }
}

int main(){
    ios_base::sync_with_stdio(0);
    vvi G;
    read(G);
    vi mate;
    solve(G,mate);
    answer(mate);
}

void read(vvi &G){
    string name;
    cin>>name;
    int n,k,m; 
    cin>>n>>k;

    G.clear();
    G.resize(n,vi());

    for(int i = 0; i<k ;i++){
        int tmp;
        cin>>tmp;
    }
    
    cin>>m;
    for(int i = 0; i<m ;i++){
        int a,b;
        cin>>a>>b;
        G[a].push_back(b);
        G[b].push_back(a);
    }
}