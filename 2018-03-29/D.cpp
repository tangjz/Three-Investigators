#include<bits/stdc++.h>
using namespace std;
#define y1 y114514
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
#define pii pair<int, int>
#define M 1000000007
#define all(a) a.begin(), a.end()
typedef long long ll;

int T, k;
int cnt;

void work(int p, int mx){
	if(p == mx){
		printf("1");
		++cnt;
		return;
	}
	if(k >> p & 1){
		printf("(1+(1+1)*");
		cnt += 3;
		work(p + 1, mx);
		printf(")");
	}else{
		printf("(1+1)*");
		cnt += 2;
		work(p + 1, mx);		
	}
}

int main(){
	scanf("%d", &T);
	while(T--){
		scanf("%d", &k);
		int mx = 0;
		while((1 << (mx + 1)) <= k) ++mx;
		cnt = 0;
		work(0, mx);
		//if(cnt > 100) printf("wtf!");
		assert(cnt <= 100);
		puts("");
	}

	return 0;
}
