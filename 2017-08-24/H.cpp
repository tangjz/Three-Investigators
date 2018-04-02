#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
#define ll long long
#define M 1000000007
#define all(a) a.begin(), a.end()

namespace fastIO {
	#define BUF_SIZE 100000
	//fread -> read
	bool IOerror = 0;
	inline char nc() {
		static char buf[BUF_SIZE], *p1 = buf + BUF_SIZE, *pend = buf + BUF_SIZE;
		if(p1 == pend) {
			p1 = buf;
			pend = buf + fread(buf, 1, BUF_SIZE, stdin);
			if(pend == p1) {
				IOerror = 1;
				return -1;
			}
		}
		return *p1++;
	}
	inline bool blank(char ch) {
		return ch == ' ' || ch == '\n' || ch == '\r' || ch == '\t';
	}
	inline void read(int &x) {
		char ch;
		while(blank(ch = nc()));
		if(IOerror)
			return;
		for(x = ch - '0'; (ch = nc()) >= '0' && ch <= '9'; x = x * 10 + ch - '0');
	}
	#undef BUF_SIZE
}
using namespace fastIO; 

int T;
int n, k;
int fa[100009];
bool f[100009];
int cnt;

int main(){
	read(T);
	while(T--){
		read(n), read(k);
		memset(f, 0, sizeof(bool) * (n + 1));
		cnt = 0;
		for(int i = 2; i <= n; ++i)
			read(fa[i]);
		for(int i = n; i >= 2; --i)
			if(!f[fa[i]] && !f[i]) f[fa[i]] = 1, cnt++;
		
		if(cnt * 2 >= k){
			printf("%d\n", (k + 1) / 2);
		}else{
			k -= cnt * 2;
			printf("%d\n", cnt + k);
		}
	}
	return 0;
}
