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

int n, m, p;
int s[111], r[111];
bool used[111];

bool check(ll T){
	memset(used, 0, sizeof(used));
	for(int i = 1; i <= m; ++i){
		int day = (p + s[i] - 1) / s[i];
		ll cur = T - day + 1;
		for(int j = n; j; --j){
			if(r[j] <= cur && !used[j]){
				cur -= day;
				used[j] = 1;
			}
		}
	}
	for(int i = 1; i <= n; ++i)
		if(!used[i]) return 0;
	return 1;
}

int main(){
	freopen("budget.in", "r", stdin);
	freopen("budget.out", "w", stdout);
	
	scanf("%d%d%d", &m, &n, &p);
	for(int i = 1; i <= m; ++i) scanf("%d", s + i);
	for(int i = 1; i <= n; ++i) scanf("%d", r + i);
	sort(r + 1, r + n + 1);
	
	ll l = 0, r = 1LL << 60;
	while(l + 1 < r){
		ll d = (l + r) >> 1;
		if(check(d)) r = d;
		else l = d;
	}
	
	printf("%lld\n", r);

	return 0;
}
