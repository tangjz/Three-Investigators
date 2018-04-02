#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
#define ll long long
#define all(a) a.begin(), a.end()

int n;
char s[1000100];
unsigned long long base[1000100];
unsigned long long has[1000100];

inline int get(int l, int r){
	return has[r] - has[l - 1] * base[r - l + 1];
}

inline int change(int h, int l, int p, int n){
	return h - (p + 1) * base[l] + (n + 1) * base[l];
}

int main(){
	base[0] = 1;
	for(int i = 1; i <= 1000000; ++i)
		base[i] = base[i - 1] * 11;
	while(~scanf("%d", &n)){
		scanf("%s", s + 1);
		for(int i = 1; i <= n; ++i)
			has[i] = has[i - 1] * 11 + (s[i] - '0' + 1);
		for(int p = 1; p <= n; ++p){
			int h1 = get(1, n - p), h2 = get(p + 1, n);
			if(h1 == h2){
				printf("%d %d\n", p, n);
				break;
			}else{
				int l = 0, r = n - p;
				while(l + 1 < r){
					int d = (l + r) >> 1;
					if(get(1, d) == get(p + 1, p + d)) l = d;
					else r = d;
				}
				int res = 0;
				//s[r] -> s[p + r]
				int hh1, hh2;
				hh1 = change(h1, n - p - r, s[r] - '0', s[p + r] - '0');
				if(r > p)
					hh2 = change(h2, n - r, s[r] - '0', s[p + r] - '0');
				else
					hh2 = h2;
				if(hh1 == hh2) ++res;			 				

				//s[p + r] -> s[r]
				hh2 = change(h2, n - p - r , s[p + r] - '0', s[r] - '0');
				if(p + r <= n - p)
					hh1 = change(h1, n - p - (p + r), s[p + r] - '0', s[r] - '0');
				else 
					hh1 = h1;
				if(hh1 == hh2) ++res;
				if(res){
					printf("%d %d\n", p, res);
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
