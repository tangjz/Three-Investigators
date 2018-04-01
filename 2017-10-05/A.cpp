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

int n, m, k, l;
int a[11], b[11];
int p[11], pb[11];
char has[200];
map<string, int> mp;
char s[25];

int base_time[11];
int time_a[111], time_b[111], w_a[111], w_b[111];

void Inconsistent(){
	puts("Inconsistent");
	exit(0);
}

void Ambiguous(){
	puts("Ambiguous");
	exit(0);
}

int main(){
	freopen("ampm.in", "r", stdin);
	freopen("ampm.out", "w", stdout);

	scanf("%d", &n);
	scanf("%d", &m); for(int i = 0; i < m; ++i) scanf("%d", a + i);
	scanf("%d", &k); for(int i = 0; i < k; ++i) scanf("%d", b + i);
	
	scanf("%d", &l);
	for(int i = 0; i < l; ++i){
		scanf("%s", s);
		if(s[3] != s[11] || s[4] != s[12]) Inconsistent();
		
		time_a[i] = (s[0] - '0') * 10 + (s[1] - '0');
		time_b[i] = (s[8] - '0') * 10 + (s[9] - '0');
		
		w_a[i] = s[6] - 'A';
		w_b[i] = s[14] - 'A';
		

		if(s[5] == s[13]){
			if(time_a[i] != time_b[i] || w_a[i] != w_b[i]) Inconsistent();
			--i, --l;
		}else{
			if(s[5] == 'B') swap(time_a[i], time_b[i]), swap(w_a[i], w_b[i]);
			if(time_a[i] >= a[w_a[i]]) Inconsistent();
			if(time_b[i] >= b[w_b[i]]) Inconsistent();
		}
	}

	for(int i = 0; i < m; ++i) p[i] = i;
	do{
		base_time[p[0]] = 0;
		for(int j = 1; j < m; ++j) base_time[p[j]] = base_time[p[j - 1]] +  a[p[j - 1]];
		for(int j = 0; j < l; ++j){
			int rt = base_time[w_a[j]] + time_a[j];
			has[j * 2] = char('0' + rt / 10);
			has[j * 2 + 1] = char('0' + rt % 10);
		}
		++mp[has];
	}while(next_permutation(p, p + m));
	
	bool flag = 0;
	string has_b;
	for(int i = 0; i < k; ++i) p[i] = i;
	do{
		base_time[p[0]] = 0;
		for(int j = 1; j < k; ++j) base_time[p[j]] = base_time[p[j - 1]] +  b[p[j - 1]];;
		for(int j = 0; j < l; ++j){
			int rt = base_time[w_b[j]] + time_b[j];
			has[j * 2] = char('0' + rt / 10);
			has[j * 2 + 1] = char('0' + rt % 10);
		}
		if(mp.count(has)){
			if(mp[has] > 1 || flag) Ambiguous();
			flag = 1;
			memcpy(pb, p, sizeof(p));
			has_b = has;
		}
	}while(next_permutation(p, p + k));
	
	if(!flag) Inconsistent();
	for(int i = 0; i < m; ++i) p[i] = i;
	do{
		base_time[p[0]] = 0;
		for(int j = 1; j < m; ++j) base_time[p[j]] = base_time[p[j - 1]] +  a[p[j - 1]];
		for(int j = 0; j < l; ++j){
			int rt = base_time[w_a[j]] + time_a[j];
			has[j * 2] = char('0' + rt / 10);
			has[j * 2 + 1] = char('0' + rt % 10);
		}
		if(has == has_b){
			printf("Alde system:");
			for(int j = 0; j < m; ++j) printf(" %d", p[j] + 1); puts("");
			printf("Baran system:");
			for(int j = 0; j < k; ++j) printf(" %d", pb[j] + 1); puts("");
		}
	}while(next_permutation(p, p + m));
		
	return 0;
}
