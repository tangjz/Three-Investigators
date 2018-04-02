#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
#define ll long long
#define M 1000000007
#define all(a) a.begin(), a.end()

const int maxn = 100100;
int tot, root, last, par[maxn * 2], go[maxn * 2][26], val[maxn * 2];
char s[maxn];
int bg[maxn];
int T, n;

void clean(int t){
	memset(go[t], 0, sizeof(go[t]));
	val[t] = par[t] = 0;
}

void extend(int w){
	int p = last;
	int np = ++tot; clean(tot);
	val[np] = val[p] + 1;
	while(p && !go[p][w]) go[p][w] = np, p = par[p];
	if(!p) par[np] = root;
	else{
		int q = go[p][w];
		if(val[p] + 1 == val[q]) par[np] = q;
		else{
			int nq = ++tot; clean(tot);
			val[nq] = val[p] + 1;
			memcpy(go[nq], go[q], sizeof(go[q]));
			par[nq] = par[q];
			par[q] = nq;
			par[np] = nq;
			while(p && go[p][w] == q) go[p][w] = nq, p = par[p];
		}
	}
	last = np;
}

int main(){
	scanf("%d", &T);
	while(T--){
		scanf("%d", &n);
		int tmp = 0, mx = 0;
		for(int i = 0; i < n; ++i){
			scanf("%s", s + bg[i]);
			bg[i + 1] = bg[i] + strlen(s + bg[i]);
			int len = bg[i + 1] - bg[i];
			if(len > mx) tmp = i, mx = len;
		}
		last = root = tot = 1;
		clean(1);
		for(int i = bg[tmp]; i < bg[tmp + 1]; ++i)
			extend(s[i] - 'a');
		//printf("%d\n", tmp);
		bool flag = 1;
		for(int i = 0; i < n && flag; ++i){
			int now = root;
			for(int j = bg[i]; j < bg[i + 1] && flag; ++j){
				if(!go[now][s[j] - 'a']) flag = 0;
				now = go[now][s[j] - 'a'];
			}
		}
		if(flag){
			for(int i = bg[tmp]; i < bg[tmp + 1]; ++i)
				putchar(s[i]);
			puts("");
		}else puts("No");
	}
	return 0;
}
