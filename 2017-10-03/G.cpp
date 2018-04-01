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

const int N = 500000;

int n;
int r[N + 5];

int main(){
	scanf("%d", &n);
	int now = 0;
	r[1] = 2;
	while(n--){
		static int x;
		scanf("%d", &x);
		if(x > N) puts("Yes");
		else{
			if(x <= now) puts("No");
			else{
				int y = x;
				while(!r[y]) --y;
				--r[y];
				for(int i = y + 1; i <= x; ++i) ++r[i];
				while(!r[now + 1]) ++now;
				puts("Yes");
			}
		}
	}
	
#ifndef ONLINE_JUDGE
	system("pause");
#endif
	return 0;
}

