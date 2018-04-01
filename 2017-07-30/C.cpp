#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
#define ll long long
#define M 1000000007
#define all(a) a.begin(), a.end()

const double eps = 1e-10;
int T, n;
double p;
double f[2][11111 * 41];
int s[42];

int main(){
	scanf("%d", &T);
	
	while(T--){
		scanf("%d%lf", &n, &p);
		int sum = 0;
		memset(f, 0, sizeof(f));
		f[0][0] = 1;
		int pre = 0, now = 1;
		for(int i = 1; i <= n; ++i){
			memset(f[now], 0, sizeof(f[now]));
			scanf("%d", s + i);
			for(int j = 0; j <= sum; ++j){
				f[now][j] += f[pre][j] * 0.5;
				f[now][j + s[i]] += f[pre][j] * 0.5;
			}
			sum += s[i];
			swap(pre, now);
		}
		if(p == 0) { printf("%d\n", 0); continue; }
		for(int i = 1; i <= sum; ++i){
			f[pre][i] += f[pre][i - 1];
			if(f[pre][i] >= p - eps){
				printf("%d\n", i);
				break;
			}
		}
	}

	return 0;
}
