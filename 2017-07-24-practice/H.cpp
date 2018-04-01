#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
#define ll long long
#define M 1000000007
#define all(a) a.begin(), a.end()

const int maxn = 300100;
int n;
char s[40];

int go[maxn][26], fail[maxn], cnt[maxn], root = 1, tot = 1;
int fa[maxn], deg[maxn], len[maxn];

void insert(char *str){
	int cur = root, i = 0;
	while(str[i]){
		int idx = str[i] - 'a';
		if(!go[cur][idx]) go[cur][idx] = ++tot, fa[tot] = cur;
		len[go[cur][idx]] = len[cur] + 1;
		cur = go[cur][idx];
		i++;
	}
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
				deg[fail[go[t][i]] = t == root ? 1 : go[fail[t]][i]]++;
				q.push(go[t][i]);
			}
	}
}

int main(){
	while(scanf("%d", &n), n){
		memset(go, 0, sizeof(go));
		memset(deg, 0, sizeof(deg));
		tot = 1;
		while(n--){
			scanf("%s", s);
			insert(s);
		}
		build();

		queue<int> q;
		for(int i = 2; i <= tot; ++i){
			if(!deg[i]) q.push(i);
			cnt[i] = 1;
		}
		while(!q.empty()){
			int x = q.front(); q.pop();
			cnt[fail[x]] += cnt[x];
			if(!(--deg[fail[x]])) q.push(fail[x]);
		}
		
		ll ans = (ll)(tot - 1) * (tot - 1);
		for(int i = 2; i <= tot; ++i){
			int p = len[fail[i]], x = i;
			while(p--) x = fa[x];
			ans -= fail[i] == 1 ? 0 : (cnt[x] - 1);
		}
		
		printf("%lld\n", ans);
	}
	
	return 0;
}
