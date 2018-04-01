#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
#define ll long long
#define M 1000000007
#define all(a) a.begin(), a.end()

const int maxn = 210;
int go[maxn][2], fail[maxn], cnt[maxn], root = 1, tot = 1;

int n, m;
int f[110][110][4][210];
char s[110];
int T;

inline void add(int &x, int y) {
	(x += y) >= M && (x -= M);
}

void insert(char *str, int k){
	int cur = root, i = 0;
	while(str[i]){
		int idx = str[i] == 'R' ? 0 : 1;
		if(!go[cur][idx]) go[cur][idx] = ++tot;
		cur = go[cur][idx];
		i++;
	}
	cnt[cur] |= 1 << k;
}

void build(){
	queue<int> q;
	q.push(root);
	while(!q.empty()){
		int t = q.front(); q.pop();
		for(int i = 0; i < 2; ++i)
			if(!go[t][i]){
				go[t][i] = t == root ? 1 : go[fail[t]][i];
			}else{
				fail[go[t][i]] = t == root ? 1 : go[fail[t]][i];
				cnt[go[t][i]] |= cnt[fail[go[t][i]]];
				q.push(go[t][i]);
			}
	}
}

int main(){
	scanf("%d", &T);
	while(T--){
		scanf("%d%d", &m, &n);
		memset(go, 0, sizeof(go));
		memset(cnt, 0, sizeof(cnt));
		root = tot = 1;
		scanf("%s", s); insert(s, 0);
		scanf("%s", s); insert(s, 1);
		build();
		for(int i = 0; i <= n; ++i)
			for(int j = 0; j <= m; ++j)
				for(int k = 0; k < 4; ++k)
					memset(f[i][j][k], 0, sizeof(int) * (tot + 1));
		f[0][0][0][1] = 1;
		for(int i = 0; i <= n; ++i)
			for(int j = 0; j <= m; ++j)
				for(int k = 0; k < 4; ++k)
					for(int l = 1; l <= tot; ++l)
						if(f[i][j][k][l]){
							if(i <= n){
								add(f[i + 1][j][k | cnt[go[l][1]]][go[l][1]], f[i][j][k][l]);
							}
							if(j <= m){
								add(f[i][j + 1][k | cnt[go[l][0]]][go[l][0]], f[i][j][k][l]);
							}
						}
		int ans = 0;
		for(int i = 1; i <= tot; ++i)
			add(ans, f[n][m][3][i]);
		printf("%d\n", ans);
	}
	
	return 0;
}
