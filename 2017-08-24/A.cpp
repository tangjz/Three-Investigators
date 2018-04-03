#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
#define ll long long
#define M 1000000007
#define all(a) a.begin(), a.end()

vector<ll> csgo[11];
int a[7][7];
ll b[7][7];
unordered_map<ll, int> mp;

void init(){
	ll bg = 0;
	ll base = 1;
	for(int i = 0; i <= 5; ++i)
		for(int j = 0; j <= i; ++j){
			bg += i * base;
			b[i][j] = base;
			base = base * 6;
		}
	csgo[0].pb(bg); mp[bg] = 0;
	for(int step = 0; step < 10; ++step){
		for(ll v : csgo[step]){
			ll now = v;
			for(int i = 0; i <= 5; ++i)
				for(int j = 0; j <= i; ++j)
					a[i][j] = now % 6, now /= 6;
			
			for(int i = 0; i < 5; ++i)
				for(int j = 0; j <= i; ++j){
					if(!a[i][j] || !a[i + 1][j]){
						ll has = v;
						has -= a[i][j] * b[i][j];
						has -= a[i + 1][j] * b[i + 1][j];
						has += a[i + 1][j] * b[i][j];
						has += a[i][j] * b[i + 1][j];
						if(!mp.count(has)){
							csgo[step + 1].pb(has);
							mp[has] = step + 1;
						}
					}
					
					if(!a[i][j] || !a[i + 1][j + 1]){
						ll has = v;
						has -= a[i][j] * b[i][j];
						has -= a[i + 1][j + 1] * b[i + 1][j + 1];
						has += a[i + 1][j + 1] * b[i][j];
						has += a[i][j] * b[i + 1][j + 1];
						if(!mp.count(has)){
							csgo[step + 1].pb(has);
							mp[has] = step + 1;
						}
					}
				}
		}
	}
	/*
	for(int i = 0; i <= 10; ++i)
		printf("%d %d\n", i, (int)csgo[i].size());
	*/
}

int solve(){
	int res = 1000;
	map<ll, int> mmp;
	for(int step = 0; step < 10; ++step){
		for(ll v : csgo[step]){
			ll now = v;
			for(int i = 0; i <= 5; ++i)
				for(int j = 0; j <= i; ++j)
					a[i][j] = now % 6, now /= 6;
			
			for(int i = 0; i < 5; ++i)
				for(int j = 0; j <= i; ++j){
					if(!a[i][j] || !a[i + 1][j]){
						ll has = v;
						has -= a[i][j] * b[i][j];
						has -= a[i + 1][j] * b[i + 1][j];
						has += a[i + 1][j] * b[i][j];
						has += a[i][j] * b[i + 1][j];
						if(mp.count(has))
							res = min(res, mp[has] + step + 1);
						else
							if(!mmp.count(has)){
								mmp[has] = 1;
								csgo[step + 1].pb(has);
							}
					}
					
					if(!a[i][j] || !a[i + 1][j + 1]){
						ll has = v;
						has -= a[i][j] * b[i][j];
						has -= a[i + 1][j + 1] * b[i + 1][j + 1];
						has += a[i + 1][j + 1] * b[i][j];
						has += a[i][j] * b[i + 1][j + 1];
						if(mp.count(has))
							res = min(res, mp[has] + step + 1);
						else
							if(!mmp.count(has)){
								mmp[has] = 1;
								csgo[step + 1].pb(has);
							}
					}
				}
		}
	}
	return res <= 20 ? res : -1;
}

int main(){
	freopen("1001.in", "r", stdin);
	freopen("1001.out", "w", stdout);
	init();
	int T;
	scanf("%d", &T);	
	while(T--){
		ll ed = 0;
		for(int i = 0; i <= 5; ++i)
			for(int j = 0; j <= i; ++j){
				int x = 0;
				scanf("%d", &x);
				ed = ed + x * b[i][j];
			}
		if(mp.count(ed)){
			printf("%d\n", mp[ed]);
		}else{
			for(int i = 0; i <= 10; ++i) csgo[i].clear();
			csgo[0].pb(ed);
			int res = solve();
			if(res != -1) printf("%d\n", res);
			else printf("too difficult\n");
		}
	}
	
	return 0;
}
