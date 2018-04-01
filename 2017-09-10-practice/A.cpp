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
int a[110];
int tag[1000100], idx;

int main(){
	scanf("%d", &T);
	while(T--){
		scanf("%d", &n); ++idx; bool flag = 1;
		for(int i = 1; i <= n; ++i) scanf("%d", a + i);
		sort(a + 1, a + n + 1);
		for(int i = 1; i < n; ++i){
			if(a[i] == a[i + 1]) flag = 0;
			for(int j = i + 1; j <= n; ++j)
				tag[a[j] - a[i]] = idx;
		}
		if(!flag) printf("NO\n");
		else{
			for(int i = 1; ; ++i){
				bool fflag = 1;
				for(int j = 1; j < n && fflag; ++j)
					if(tag[j * i] == idx) fflag = 0;
				if(fflag){
					printf("YES\n");
					for(int j = 0; j < n; ++j)
						printf("%d ", j * i + 1);
					printf("\n");
					break;
				}
			}
		}
	}
	
#ifndef ONLINE_JUDGE
	system("pause");
#endif
	return 0;
}

