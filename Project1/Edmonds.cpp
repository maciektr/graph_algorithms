#include<bits/stdc++.h>
using namespace std;

#define all(X) begin(X),end(X)
#define sz(X) (int)(X).size()
typedef long long ll;
typedef vector<bool> vb;
typedef vector<int> vi;
typedef vector<vector<int> > vvi;

void read(vvi &G);

// Debug

#define DEBUG 1 
#define COUT if(DEBUG) cout<<"\e[36m"
#define ENDL "\e[39m"<<endl;
template<typename t>
void print_vec(vector<t> v){
#if DEBUG 

    cout<<"\e[36m";
    for(auto i : v)
        cout<<(int)i<<' ';
    cout<<"\e[39m"<<endl;
#endif
}


//FindUnion - kactl

struct UF{
    vi e;
    UF (int n) : e(n,-1){}
    bool same_set(int a, int b){return find(a) == find(b);}
    int size(int x){return -e[find(x)];}
    int find(int x) { return e[x] < 0 ? x : e[x]=find(e[x]);}
    bool join(int a, int b){
        a = find(a); b = find(b);
        if(a==b) return false;
        if(e[a] > e[b]) swap(a,b);
        e[a]+=e[b]; e[b] = a;
        return true;
    }

    void select(int x){
        // COUT<<"FOING "<<x<<ENDL
        // print_vec(e);
        int y = find(x);
        if(x==y) return;
        // COUT<<"ING "<<x<<" : "<<y<<" : "<<e[x]<<" : "<<e[y]<<ENDL
        e[x] = e[y];
        e[y] = x;
    }
};

// Alternating forest with blossom shrinking

const bool even = true, odd = false;
const int alone = -1;

vi find_path(int s, int t, vb &label, vi &mate, vi &pred, vi *bridge){
    if(s==t){
        vi res = {s};
        return res;
    }
    if(label[s] == even){
        vi res = {s,mate[s]};
        vi v = find_path(pred[mate[s]],t, label, mate, pred, bridge);
        v.insert(v.begin(), all(res));
        return v;
    }
    int v = bridge[0][s];
    int w = bridge[1][s];
    vi a = find_path(v,mate[s],label,mate,pred,bridge);
    reverse(all(a));
    vi b = find_path(w,t,label,mate,pred,bridge);
    vi c = {s};
    a.insert(a.begin(), all(c));
    a.insert(a.end(), all(b));
    return a;
}

bool alt_tree(int v, vvi &G, vb &label, UF &uf, vi &pred, vi &mate, vi &path, vb &seen){
    COUT<<"CALL"<<v<<ENDL
    label[v] = even;
    queue<int> Q;
    Q.push(v);
    

    vi bridge[2];
    bridge[0].resize(sz(G));
    bridge[1].resize(sz(G));

    auto shrink_path = [mate, &Q, &uf, &bridge, &pred](int b, int v, int w){
        int u = uf.find(v);
        while(u != b){
            uf.join(b,u);
            u = mate[u];
            uf.join(b,u);
            uf.select(b);
            Q.push(u);
            bridge[0][u] = v;
            bridge[1][u] = w;
            COUT<<"HOHO"<<u<<pred[u]<<ENDL
            u = uf.find(pred[u]);
            COUT<<"lo"<<ENDL

        }
    };

    auto find_base = [&pred](int v, int w){
        unordered_set<int> seen;
        // COUT<<"PB ";
        while(v!=alone){
            seen.insert(v);
            // COUT<<v<<' ';
            v = pred[v];
        }
        // COUT<<ENDL
        // COUT<<"P ";
        while(seen.find(w)==seen.end()){
            w = pred[w];
            // COUT<<w<<" ";
        }
        // COUT<<ENDL
        return w;
    };
    bool flag = false;
    while(!Q.empty()){
        v = Q.front();
        Q.pop();
        if(seen[v])
            continue;
        seen[v] = true;
        COUT<<"V "<<v<<ENDL
        for(auto w:G[v]){
            v = uf.find(v);
            w = uf.find(w);
            if(seen[w])
                continue;
            // COUT<<"F: "<<v<<" ? "<<(label[v]==even ? "even" :"odd")<<" : "<<w<<" ? "<<(label[w] == even ? "even" :"odd")<<ENDL
            // COUT<<"F: "<<v<<" ? "<<pred[v]<<" : "<<w<<" ? "<<pred[w]<<ENDL
            COUT<<"F: "<<v<<" : "<<w<<ENDL
            print_vec(label);
            print_vec(pred);
            print_vec(mate);
            COUT<<"++++"<<ENDL

            if(v!=w){
                if(pred[w] == alone){
                    if(mate[w] == alone){
                        COUT<<"A"<<ENDL
                        int r = v;
                        while(pred[r]!=alone)
                            r = pred[r];
                        COUT<<"X "<<v<<" : "<<r<<ENDL
                        path = find_path(v,r,label, mate, pred, bridge);
                        path.insert(path.begin(),w);
                            // COUT<<"RET "<<sz(path)<<ENDL
                            // // print_vec(label);
                            // for(int i = 1; i<sz(path); i+=2){
                            //     mate[path[i-1]] = path[i];
                            //     mate[path[i]] = path[i-1];
                            // }
                            
                            // print_vec(path);
                            // // print_vec(label);
                            // COUT<<"----"<<ENDL
                        // return true;
                        flag = true;
                    }else{
                        COUT<<"doinSTAFF "<<mate[w]<<ENDL
                        label[w] = odd;
                        pred[w] = v;
                        label[mate[w]] = even;
                        pred[mate[w]] = w;
                        Q.push(mate[w]);
                    }
                }else if(label[w] == even){
                    COUT<<"SHRINK "<<v<<" "<<w<<ENDL
                    int b = find_base(v,w);
                    COUT<<"BASED "<<b<<ENDL
                    shrink_path(b,v,w);
                    COUT<<"FIRST" <<ENDL
                    shrink_path(b,w,v);
                    COUT<<"SECOND"<<ENDL
                }
            }
        }
    }
    return flag;//false;
}

bool alt_forest(vvi &G, vi &mate){//, vi &pred, vb &label, UF &uf){
    print_vec(mate);
    vi pred(sz(G),-1);
    vb label(sz(G),false);
    UF uf(sz(G));
    vb seen(sz(G),false);
    
    bool flag = false;
    for(int i = 0; i<sz(G); i++)
        if(mate[i] == alone){
            // COUT<<"A "<<i<<ENDL
            vi res;
            if(alt_tree(i,G,label,uf, pred, mate, res, seen)){
                COUT<<"RET "<<sz(res)<<ENDL
                // print_vec(label);
                for(int i = 1; i<sz(res); i+=2){
                    mate[res[i-1]] = res[i];
                    mate[res[i]] = res[i-1];
                }
                
                print_vec(res);
                // print_vec(label);
                COUT<<"----"<<ENDL
                flag = true;
            }
            // flag = alt_tree(i,G,label,uf, pred, mate, res);
        }
    return flag;
}

//Solution

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
    mate.resize(sz(G), -1);

    tryDummMatching(G,mate);

    bool flag = true;
    while(flag){
        flag = alt_forest(G,mate);//, pred, label, uf);
        COUT<<"========"<<ENDL
    }
}

void answer(vi &mate){
    // print_vec(mate);
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
    COUT<<"START"<<ENDL
    solve(G, mate);
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