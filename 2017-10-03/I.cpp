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

void exgcd(ll a, ll b, ll &d, ll &x, ll &y){
	if (!b) d = a, x = 1, y = 0;
	else exgcd(b, a % b, d, y, x), y -= x * (a / b);
}//ax+by=d

int main(){
	int n;
	scanf("%d", &n);
	while(n--){
		ll a, b, d, x, y;
		scanf("%lld%lld", &a, &b);
		exgcd(a, b, d, x, y);
		y = -y;
		//x*a-y*b=d
		if(d <= 50000){
			for(bool flag = 1; flag; ){
				flag = 0;
				if(x < 0){
					ll t = abs(x) / b;
					x += t * b;
					y += t * a;
					if(x < 0) x += b, y += a;
					flag = 1;
				}
				if(x > b){
					ll t = abs(x) / b;
					x -= t * b;
					y -= t * a;
					if(x > a) x -= b, y -= a;
					flag = 1;
				}
				if(y < 0){
					ll t = abs(y) / a;
					x += t * b;
					y += t * a;
					if(y < 0) x += b, y += a;
					flag = 1;
				}
				if(y > a){
					ll t = abs(y) / a;
					x -= t * b;
					y -= t * a;
					if(y > b) x -= b, y -= a;
					flag = 1;
				}
				break;
			}
			printf("3\n");
			printf("0 0\n");
			printf("%lld %lld\n", a, b);
			printf("%lld %lld\n", y, x);
		}else{
			printf("4\n");
			printf("0 0\n");
			printf("%lld %lld\n", a - 1, b);
			printf("%lld %lld\n", a / d, b / d);
			printf("%lld %lld\n", a, b - 1);
		}
	}
	
#ifndef ONLINE_JUDGE
	system("pause");
#endif
	return 0;
}
