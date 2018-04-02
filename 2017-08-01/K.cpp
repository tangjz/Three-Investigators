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
	int t, x, cnt = 0;
	scanf("%d", &t);
	for(int i = 1; i <= t; ++i){
		scanf("%d", &x);
		if(x <= 35) cnt++;
	}
	printf("%d\n", cnt);
	return 0;
}
