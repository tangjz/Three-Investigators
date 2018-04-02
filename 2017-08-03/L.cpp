#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
#define ll long long
#define M 998244353
#define all(a) a.begin(), a.end()

namespace fastIO{
	#define BUF_SIZE 100000
	//fread->read
	bool IOerror=0;
	inline char nc(){
		static char buf[BUF_SIZE],*p1=buf+BUF_SIZE,*pend=buf+BUF_SIZE;
		if (p1==pend){
			p1=buf; pend=buf+fread(buf,1,BUF_SIZE,stdin);
			if (pend==p1){IOerror=1;return -1;}
		}
		return *p1++;
	}
	inline bool blank(char ch){return ch==' '||ch=='\n'||ch=='\r'||ch=='\t';}
	inline void read(int &x){
		bool sign=0; char ch=nc(); x=0;
		for (;blank(ch);ch=nc());
		if (IOerror)return;
		if (ch=='-')sign=1,ch=nc();
		for (;ch>='0'&&ch<='9';ch=nc())x=x*10+ch-'0';
		if (sign)x=-x;
	}
	#undef BUF_SIZE
}
using namespace fastIO;

const int maxn = 2001;
int T, n, m;
int a[maxn], b[maxn];
int f[2][maxn], ff[2][maxn];
int c[2][maxn][maxn];
int t;

inline void mod_inc(int &x, int y) {
	(x += y) >= M && (x -= M);
}

inline void add(bool k, int j, int x, int v){
	int *cc = c[k][j];
	if(!k){
		for(; x; x -= x & -x)
			mod_inc(cc[x], v);
	}else{
		for(; x <= t; x += x & -x)
			mod_inc(cc[x], v);
	}
}

inline int ask(bool k, int j, int x){
	int res = 0;
	int *cc = c[k][j];
	if(!k){
		for(; x <= t; x += x & -x)
			mod_inc(res, cc[x]);
	}else{
		for(; x; x -= x & -x)
			mod_inc(res, cc[x]);
	}
	return res;
}

int main(){
	read(T);
	while(T--){
		read(n), read(m);
		t = 0;
		for(int i = 1; i <= n; ++i) read(a[i]), t = max(t, a[i]);
		for(int i = 1; i <= m; ++i){
			read(b[i]);
			memset(c[0][i] + 1, 0, t * sizeof(int));
			memset(c[1][i] + 1, 0, t * sizeof(int));
		}
		int ans = 0;
		for(int i = 1; i <= n; ++i)
			for(int j = 1; j <= m; ++j){				
				if(a[i] == b[j]){
					f[0][j] = ask(1, j - 1, a[i] - 1);
					f[1][j] = ask(0, j - 1, a[i] + 1) + 1;
					mod_inc(ans, f[0][j]);
					mod_inc(ans, f[1][j]);
				}else f[0][j] = f[1][j] = 0;
				
				ff[0][j] = ff[0][j - 1];
				mod_inc(ff[0][j], f[0][j]);
				ff[1][j] = ff[1][j - 1];
				mod_inc(ff[1][j], f[1][j]);
				if(ff[0][j])
					add(0, j, a[i], ff[0][j]);
				if(ff[1][j])
					add(1, j, a[i], ff[1][j]);
				//printf("%d %d: %d %d\n", i, j, f[0][i][j], f[1][i][j]);
			}
		printf("%d\n", ans);
	}
	
	return 0;
}
