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

int n, m;
char s[45];
int a[45];
ll sur[45];
int L[45];
int sum[1 << 20];
ll num[1 << 20];
map<ll, int> mp;

inline ll SurrealNumber(int *T){
	int i = 1;
	ll res = 0;
	for(; i <= m && T[i] == T[1]; ++i)
		res += (T[i] ? -1 : 1) * (1LL << 40);
	for(int j = 1; i <= m; ++i, ++j)
		res += (T[i] ? -1 : 1) * (1LL << (40 - j));
	return res;
}

int main(){
	scanf("%d", &n);
	for(int i = 0; i < n; ++i){
		scanf("%s", s + 1);
		m = strlen(s + 1);
		L[i] = m;
		for(int j = 1; j <= m; ++j)
			a[j] = s[j] == 'W';
		sur[i] = SurrealNumber(a);
	}
	int lef = n / 2, rig = n - lef;
	mp[0] = 0;
	for(int i = 1; i < 1 << lef; ++i){
		int t = __builtin_ctz(i);
		sum[i] = sum[i ^ (1 << t)] + L[t];
		num[i] = num[i ^ (1 << t)] + sur[t];
		mp[num[i]] = max(mp[num[i]], sum[i]);
	}
	
	int ans = mp[0];
	for(int i = 1; i < 1 << rig; ++i){
		int t = __builtin_ctz(i);
		sum[i] = sum[i ^ (1 << t)] + L[t + lef];
		num[i] = num[i ^ (1 << t)] - sur[t + lef];		
		if(mp.count(num[i])) ans = max(ans, mp[num[i]] + sum[i]);
	}
	
	printf("%d\n", ans);
	
	
#ifndef ONLINE_JUDGE
	system("pause");
#endif
	return 0;
}
