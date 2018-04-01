#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
#define ll long long
#define M 1000000007
#define all(a) a.begin(), a.end()

int n, has[5][100000];
char s[10];
int len;
int ca;
bool flag;

void dfs(int t, int h, int d){
	if(t == len){
		if(has[len - 1][h] == ca) flag = 1;
		return;
	}
	int x = s[t] - '0';
	if(x - d >= 0) dfs(t + 1, h * 10 + (x - d), d);
	if(x + d <= 9 && !flag) dfs(t + 1, h * 10 + (x + d), d);
}

int main(){
	int T;
	scanf("%d", &T);
	while(T--){
		++ca;
		scanf("%d", &n);
		int ans = 0;
		//memset(hass, 0, sizeof(hass));
		for(int i = 0; i < n; ++i){
			scanf("%s", s);
			len = strlen(s);
			int tmin = 9, tmax = 0;
			int h = 0;
			for(int j = 0; j < len; ++j){
				tmin = min(tmin, int(s[j] - '0'));
				tmax = max(tmax, int(s[j] - '0'));
				h = h * 10 + s[j] - '0';
			}
			if(has[len - 1][h] == ca) continue;
			flag = 0;
			for(int j = 1; j <= 9; ++j)
				dfs(0, 0, j);
			if(flag) continue;
			has[len - 1][h] = ca;
			ans++;
		}
		printf("Case %d: %d\n", ca, ans);
	}

	return 0;
}
