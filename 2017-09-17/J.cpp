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
int T, n;
int pre[maxn], nex[maxn];
int a[maxn], q[maxn], del[maxn], m;
bool inq[maxn], haddel[maxn];

int main(){
	scanf("%d", &T);
	while(T--){
		scanf("%d", &n);
		for(int i = 1; i <= n; ++i){
			scanf("%d", a + i);
			pre[i] = i - 1;
			nex[i] = i + 1;
			inq[i] = 1;
			q[i] = i;
			haddel[i] = 0;
		}
		int nn = n;
		nex[0] = 1;
		pre[n + 1] = n;
		a[n + 1] = 100100;
		
		while(n){
			m = 0;
			for(int i = 1; i <= n; ++i){
				int x = q[i];
				inq[x] = 0;
				if(a[x] >= a[pre[x]] && a[x] <= a[nex[x]]) continue;
				del[++m] = x;
				haddel[x] = 1;
			}
			n = 0;
			for(int i = 1; i <= m; ++i){
				int x = del[i];
				if(pre[x] && !inq[pre[x]]) q[++n] = pre[x], inq[pre[x]] = 1;
				if(nex[x] <= nn && !haddel[nex[x]]) q[++n] = nex[x], inq[nex[x]] = 1;
				nex[pre[x]] = nex[x];
				pre[nex[x]] = pre[x];
			}
		}
		
		int now = nex[0];
		vector<int> ans;
		while(now != nn + 1) ans.pb(now), now = nex[now];
		printf("%d\n", (int)ans.size());
		for(int v : ans)
			printf("%d ", a[v]);
		printf("\n");
	}
	return 0;
}
