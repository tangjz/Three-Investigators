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

int n, k;
int x;
int sur, unuse;

int main(){
	scanf("%d%d", &n, &k);
	for(int i = 1; i <= n; ++i){
		scanf("%d", &x);
		if(x > k) unuse += x - k;
		else sur += k - x;
	}
	printf("%d %d\n", unuse, sur);
	return 0;
}
