#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
#define ll long long
#define M 1000000007
#define all(a) a.begin(), a.end()

int T;
int n;

int main(){
	scanf("%d", &T);
	while(T--){
		scanf("%d", &n);
		int l = 1, r = sqrt(n) + 10;
		while(l + 1 < r){
			int d = (l + r) >> 1;
			if((ll)d * d * 2 <= n) l = d;
			else r = d;
		}
		
		if((ll)l * l * 2 >= n) printf("%d\n", 4 * l);
		else{
			if((ll)l * l * 2 + l > n) printf("%d\n", 4 * l + 1);
			else{
				if((ll)l * (l + 1) * 2 >= n) printf("%d\n", 4 * l + 2);
				else if((ll)l * (l + 1) * 2 + (l + 1) > n)
					printf("%d\n", 4 * l + 3);
				else printf("%d\n", 4 * (l + 1));
			}
		}
	}
	return 0;
}
