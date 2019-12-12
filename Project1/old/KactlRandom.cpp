// Randomized algorithm
// https://github.com/kth-competitive-programming/kactl
// https://www.mimuw.edu.pl/~mucha/pub/mucha_sankowski_focs04.pdf

#include<bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(int i = a; i<(b); ++i)
#define trav(a,x) for(auto &a : x)
#define all(X) begin(X),end(X)
#define sz(X) (int)(X).size()
#define st first
#define nd second
typedef long long ll;
typedef vector<bool> vb;
typedef vector<int> vi;
typedef vector<vector<int> > vvi;
typedef pair<int,int> pii;
typedef vector<ll> vll; 
typedef vector<pii> vpi;

const ll mod = 1000000007;

ll modpow(ll b, ll e){
    ll ans = 1;
    for(;e;b=b*b%mod, e/=2)
        if(e & 1) ans = ans * b % mod;
    return ans;
}

int matInv(vector<vector<ll>>& A) {
	int n = sz(A); vi col(n);
	vector<vector<ll>> tmp(n, vector<ll>(n));
	rep(i,0,n) tmp[i][i] = 1, col[i] = i;

	rep(i,0,n) {
		int r = i, c = i;
		rep(j,i,n) rep(k,i,n) if (A[j][k]) {
			r = j; c = k; goto found;
		}
		return i;
found:
		A[i].swap(A[r]); tmp[i].swap(tmp[r]);
		rep(j,0,n) swap(A[j][i], A[j][c]), swap(tmp[j][i], tmp[j][c]);
		swap(col[i], col[c]);
		ll v = modpow(A[i][i], mod - 2);
		rep(j,i+1,n) {
			ll f = A[j][i] * v % mod;
			A[j][i] = 0;
			rep(k,i+1,n) A[j][k] = (A[j][k] - f*A[i][k]) % mod;
			rep(k,0,n) tmp[j][k] = (tmp[j][k] - f*tmp[i][k]) % mod;
		}
		rep(j,i+1,n) A[i][j] = A[i][j] * v % mod;
		rep(j,0,n) tmp[i][j] = tmp[i][j] * v % mod;
		A[i][i] = 1;
	}

	for (int i = n-1; i > 0; --i) rep(j,0,i) {
		ll v = A[j][i];
		rep(k,0,n) tmp[j][k] = (tmp[j][k] - v*tmp[i][k]) % mod;
	}

	rep(i,0,n) rep(j,0,n)
		A[col[i]][col[j]] = tmp[i][j] % mod + (tmp[i][j] < 0 ? mod : 0);
	return n;
}


vector<pii> generalMatching(int N, vector<pii>& ed) {
	vector<vector<ll>> mat(N, vector<ll>(N)), A;
	trav(pa, ed) {
		int a = pa.first, b = pa.second, r = rand() % mod;
		mat[a][b] = r, mat[b][a] = (mod - r) % mod;
	}

	int r = matInv(A = mat), M = 2*N - r, fi, fj;
	assert(r % 2 == 0);

	if (M != N) do {
		mat.resize(M, vector<ll>(M));
		rep(i,0,N) {
			mat[i].resize(M);
			rep(j,N,M) {
				int r = rand() % mod;
				mat[i][j] = r, mat[j][i] = (mod - r) % mod;
			}
		}
	} while (matInv(A = mat) != M);

	vi has(M, 1); vector<pii> ret;
	rep(it,0,M/2) {
		rep(i,0,M) if (has[i])
			rep(j,i+1,M) if (A[i][j] && mat[i][j]) {
				fi = i; fj = j; goto done;
		} assert(0); done:
		if (fj < N) ret.emplace_back(fi, fj);
		has[fi] = has[fj] = 0;
		rep(sw,0,2) {
			ll a = modpow(A[fi][fj], mod-2);
			rep(i,0,M) if (has[i] && A[i][fj]) {
				ll b = A[i][fj] * a % mod;
				rep(j,0,M) A[i][j] = (A[i][j] - A[fi][j] * b) % mod;
			}
			swap(fi,fj);
		}
	}
	return ret;
}

int read(vpi &G){
    string name;
    cin>>name;
    int n,k,m; 
    cin>>n>>k;

    for(int i = 0; i<k ;i++){
        int tmp;
        cin>>tmp;
    }
    
    cin>>m;
    for(int i = 0; i<m ;i++){
        int a,b;
        cin>>a>>b;
        G.push_back(make_pair(a,b));
    }
    return n;
}
void answer(vpi res){
    cout<<sz(res)<<endl;
    trav(i,res){
        cout<<i.st<<' '<<i.nd<<endl;
    }
}

int main(){
    ios_base::sync_with_stdio(0);
    vpi G;
    answer(generalMatching(read(G),G));
}