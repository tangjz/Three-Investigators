#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
#define ll long long
#define M 1000000007
#define all(a) a.begin(), a.end()

int T, n;
string ty[50], s;
unsigned num[50];
bool ok[2][1 << 20];
unsigned f[2][1 << 20];

int main(){
	cin >> T;
	while(T--){
		cin >> n;
		for(int i = 1; i <= n; ++i){
			cin >> ty[i] >> s;
			num[i] = 0;
			unsigned base = 1;
			for(int j = 7; j >= 0; --j){
				num[i] += unsigned(s[j] <= '9' ? s[j] - '0' : s[j] - 'a' + 10) * base;
				base <<= 4;
			}			
			if(ty[i] == "-="){
				ty[i] = "+=";
				num[i] = -num[i];
			}			
		}
		int nn = 0, m = 0;
		for(int i = 1, j = 1; i <= n; i = j){
			++j;
			if(ty[i] == "+="){
				while(j <= n && ty[j] == "+=") num[i] += num[j++];
				++m;
			}
			ty[++nn] = ty[i];
			num[nn] = num[i];
		}
		n = nn;
		
		memset(ok, 0, sizeof(ok));
		memset(f, 0, sizeof(f));
		ok[0][0] = 1;
		int now = 0, pre = 1;
		for(int i = 0; i < 32; ++i){
			swap(now, pre);
			memset(ok[now], 0, sizeof(ok[now]));
			memset(f[now], 0, sizeof(f[now]));
			for(int S = 0; S < 1 << m; ++S){
				if(!ok[pre][S]) continue;
				int x0 = 0, x1 = 1, S0 = 0, S1 = 0;
				for(int j = 1, k = 0; j <= n; ++j){
					int y = num[j] >> i & 1;
					if(ty[j] == "+="){
						int x = S >> k & 1;
						S0 |= (x + x0 + y > 1) << k;
						S1 |= (x + x1 + y > 1) << k;
						x0 = (x + x0 + y) & 1;
						x1 = (x + x1 + y) & 1;
						++k;
					}else if(ty[j] == "&="){
						x0 &= y, x1 &= y;
					}else if(ty[j] == "|="){
						x0 |= y, x1 |= y;
					}else if(ty[j] == "^="){
						x0 ^= y, x1 ^= y;
					}
				}
				ok[now][S0] = 1, ok[now][S1] = 1;
				f[now][S0] = max(f[now][S0], f[pre][S] + ((unsigned)x0 << i));
				f[now][S1] = max(f[now][S1], f[pre][S] + ((unsigned)x1 << i));
			}
		}
		unsigned ans = 0;
		for(int S = 0; S < 1 << m; ++S)
			if(ok[now][S]) ans = max(ans, f[now][S]);
		printf("%u\n", ans);
	}
	return 0;
}
