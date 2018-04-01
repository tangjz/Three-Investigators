#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
#define ll long long
#define pii pair<int, int>
#define M 1000000007
#define all(a) a.begin(), a.end()

const int inf = 1e9;
int n, m;
int d[10005], f[10005][2], ty, aim;
int ans = 0;

int main(){
	scanf("%d%d", &n, &m);
	scanf("%d%d", &d[1], &d[n + 1]);
	int last = 1;
	for(int i = 2; i <= n + 1; ++i){
		if(i <= n) scanf("%d%d", &ty, d + i);
		else ty = 1;
		if(ty == 2) continue;
		int tmp = 0, tmp2 = 0, tl = min(d[last], d[i]), tr = max(d[last], d[i]);
		for(int j = last + 1; j < i; ++j){
			if((d[j] >= tl && d[j] <= tr) || (m - d[j] + 1 >= tl && m - d[j] + 1 <= tr)) continue;
			int pl = min(d[j], m - d[j] + 1), pr = max(d[j], m - d[j] + 1);
			if(pl < tl && pr > tr){
				int tt = min(tl - pl, pr - tr);
				tmp = max(tmp, tt);	
			}else if(pl > tr){
				int tt = pl - tr;
				tmp2 = max(tmp2, tt);
			}else{
				int tt = tl - pr;
				tmp2 = max(tmp2, tt);
			}
		}
		last = i;
		ans += tmp * 2 + tmp2 * 2 + tr - tl;
	}
	printf("%d\n", ans);

#ifndef ONLINE_JUDGE
	system("pause");
#endif
	return 0;
}
