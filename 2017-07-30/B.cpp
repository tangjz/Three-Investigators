#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
#define ll long long
#define M 1000000007
#define all(a) a.begin(), a.end()

int n;
int a[400];

bool check(){
	bool flag = 0;
	for(int i = 1; i <= 200; ++i){
		int t = min(a[i], a[i + 1]);
		a[i + 2] += t;
		a[i] -= t;
		a[i + 1] -= t;
		if(a[i] > 1){
			flag = 1;
			a[i + 1] += a[i] / 2;
			if(i > 3) a[i - 2] += a[i] / 2;
			a[i] &= 1;
		}
	}
	return flag;
}

int main(){
	while(~scanf("%d", &n)){
		memset(a, 0, sizeof(a));
		a[100] = n;
		while(check());	
		int now = 200;
		while(!a[now]) now--;
		for(int i = now; i >= 100; --i) putchar('0' + a[i]);
		now = 1;
		while(!a[now]) now++;
		if(now <= 99) putchar('.');
		for(int i = 99; i >= now; --i) putchar('0' + a[i]);
		puts("");
	}
	
	return 0;
}
