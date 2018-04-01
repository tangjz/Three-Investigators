#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
#define ll long long
#define M 1000000007
#define all(a) a.begin(), a.end()

const int maxn = 110;
int go[maxn][26], fail[maxn], cnt[maxn], root = 1, tot = 1;
int n, m;
char str[15][15];
ll f[30][1024][maxn];
char sstr[30];

void insert(char *str, int id){
	int cur = root, i = 0;
	while(str[i]){
		int idx = str[i] - 'a';
		if(!go[cur][idx]) go[cur][idx] = ++tot;
		cur = go[cur][idx];
		i++;
	}
	cnt[cur] |= 1 << id;
}

void build(){
	queue<int> q;
	q.push(root);
	while(!q.empty()){
		int t = q.front(); q.pop();
		for(int i = 0; i < 26; ++i)
			if(!go[t][i]){
				go[t][i] = t == root ? 1 : go[fail[t]][i];
			}else{
				fail[go[t][i]] = t == root ? 1 : go[fail[t]][i];
				cnt[go[t][i]] |= cnt[fail[go[t][i]]];
				q.push(go[t][i]);
			}
	}
}

void output(int i, int j, int k){
	if(i == n){
		if(j == (1 << m) - 1) printf("%s\n", sstr);
		return;
	}
	for(int l = 0; l < 26; ++l){
		sstr[i] = 'a' + l;
		if(f[i + 1][j | cnt[go[k][l]]][go[k][l]])
			output(i + 1, j | cnt[go[k][l]], go[k][l]);
	}
}

int main(){
	int ca = 0;
	while(scanf("%d%d", &n, &m), n){
		tot = root = 1;
		memset(go, 0, sizeof(go));
		memset(cnt, 0, sizeof(cnt));
		//memset(fail, 0, sizeof(fail));
		for(int i = 0; i < m; ++i){
			scanf("%s", str[i]);
			insert(str[i], i);			
		}
		build();
		memset(f, 0, sizeof(f));
		for(int i = 1; i <= tot; ++i)
			f[n][(1 << m) - 1][i] = 1;
		
		sstr[n] = 0;
		for(int i = n - 1; i >= 0; --i)
			for(int j = 0; j < 1 << m; ++j)
				for(int k = 1; k <= tot; ++k)
					for(int l = 0; l < 26; ++l)
						f[i][j][k] += f[i + 1][j | cnt[go[k][l]]][go[k][l]];
		
		printf("Case %d: %lld suspects\n", ++ca, f[0][0][1]);
		if(f[0][0][1] <= 42) output(0, 0, 1);
	}
	
	return 0;
}
