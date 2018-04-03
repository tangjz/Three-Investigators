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

void work1(int len){
	assert(len % 2 == 0);
	for(int i = 1; i <= len / 2; ++i)
		printf("()");
}

void work2(int len){
	assert(len % 2 == 0);
	for(int i = 1; i <= len / 2; ++i)
		printf("[]");
}

int main(){
	int n, l, r;
	scanf("%d%d%d", &n, &l, &r);
	assert((r - l) & 1);
	if(l & 1){
		work1(l - 1);
		work2(r - l + 1);
		work1(n - r);
	}else{
		work1(l - 2);
		printf("(");
		work2(r - l + 1);
		printf(")");
		work1(n - r - 1);
	}
	
#ifndef ONLINE_JUDGE
	system("pause");
#endif
	return 0;
}
