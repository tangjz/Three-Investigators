#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
#define ll long long
#define M 1000000007
#define all(a) a.begin(), a.end()

int T, a;

int main(){
	scanf("%d", &T);
	while(T--){
		scanf("%d", &a);
		printf("%d\n", (a - 1) / 2 + 2); 
	}
	
	return 0;
}
