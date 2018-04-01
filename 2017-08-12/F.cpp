#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
#define ll long long
#define M 1000000007
#define all(a) a.begin(), a.end()

int main(){
	int n, k;
	while(scanf("%d%d", &n, &k), n){
		int t = n % (k + 1);
		printf("%s\n", t == 1 ? "Jiang" : "Tang");
	}

	return 0;
}
