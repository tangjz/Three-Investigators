#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
#define ll long long
#define M 1000000007
#define all(a) a.begin(), a.end()

int m, len, Q, maxp;
bitset<1001> b[26], bit[1000001], ok[1000001];
int fa[1000001], ch[1000001];
int ans[1000001];
vector<pair<pair<int, int>, int> > q[1000001];
char ty[10];

int main(){
	while(~scanf("%d", &m)){
		len = Q = maxp = 0;
		for(int i = 0; i < 26; ++i) b[i].reset();
		q[0].clear();
		while(m--){
			scanf("%s", ty);
			if(ty[0] == 'I'){ //INS
				static char p1, p2;
				scanf(" %c %c", &p1, &p2);
				len++;
				for(int i = p1 - 'a'; i <= p2 - 'a'; ++i)
					b[i].set(len);
			}else if(ty[1] == 'D'){ //ADD
				static int u, v;
				static char c;
				scanf("%d%d %c", &u, &v, &c);
				maxp = v;
				q[v].clear();
				fa[v] = u;
				ch[v] = c - 'a';
			}else{ //ASK
				static int p1, p2, t;
				Q++;
				scanf("%d%d%d", &p1, &p2, &t);				
				q[t].pb(mkp(mkp(p1, p2), Q));
			}
		}
		ok[0].set(0), bit[0].set(0);
		for(int i = 0; i <= maxp; ++i){
			if(i){
				bit[i] = bit[fa[i]] << 1 & b[ch[i]];
				bit[i].set(0);
				ok[i] = bit[i] | ok[fa[i]];
			}
			for(auto que : q[i]){
				int l = que.fi.fi, r = que.fi.se, id = que.se;
				auto x = ok[i] << (len - r) >> (len - r + l);
				if(x.any()) ans[id] = 1; else ans[id] = 2;
				//printf("%d: %d\n", id, ans[id]);
			}
		}
		int res = 0;
		for(int i = Q, base = 1; i >= 1; --i, base = (ll)base * 233 % M)
			res = (res + (ll)base * ans[i]) % M;
		printf("%d\n", res);
	}
	
#ifndef ONLINE_JUDGE
	system("pause");
#endif
	return 0;
}
