//看看会不会爆int!
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
#define FOR(i, l, r) for(int i = l; i <= r; i++)
#define ROF(i, r, l) for(int i = r; i >= l; i--)
#define all(a) a.begin(), a.end()
inline int ckmax(int &a, int b) { return a < b ? a = b, 1 : 0; }
inline int ckmin(int &a, int b) { return a > b ? a = b, 1 : 0; }
#define clean(a) memset(a, 0, sizeof(a))

const int maxn = 60;
int n, m, e, cur, u, v;
int g[maxn][maxn];
ll mask[maxn], ver[maxn];

vector<pair<ll, ll> >base;
void gauss(){
	base.clear();
	
	for(int i = 0; i < m; ++i){
		ll tmp = mask[i], ver = 1LL << i;
		for(auto&& v : base)
			if((tmp ^ v.fi) < tmp){
				ver ^= v.se;
				tmp ^= v.fi;
			}
		if(tmp){
			base.pb(mkp(tmp, ver));
			sort(all(base));
			reverse(all(base));
		}
	}
}

int main(){
	scanf("%d%d%d%d", &n, &m, &e, &cur); cur--;
	for(int i = 1; i <= e; ++i){
		scanf("%d%d", &u, &v);
		--u, --v;
		mask[v] ^= 1LL << u;
		g[u][v]++;
	}

	while(1){
		int choose = -1;
		for(int i = 0; i < m; ++i)
			if(g[cur][i]){
				choose = i;
				break;
			}
		
		if(choose == -1){
			printf("Player 2 wins");
			fflush(stdout);
			return 0;
		}
		
		gauss();
		ll tmp = 1LL << cur, ch = 0;
		for(auto&& v : base)
			if((tmp ^ v.fi) < tmp){
				ch ^= v.se;
				tmp ^= v.fi;
			}

		for(int i = 0; i < m; ++i)
			if(ch & (1LL << i))
				if(g[cur][i]) choose = i;
		
		printf("%d\n", choose + 1);
		g[cur][choose]--;
		mask[choose] ^= 1LL << cur;
		fflush(stdout);

		bool flag = 0;
		for(int i = 0; i < n; ++i)
			flag |= g[i][choose] > 0;
		if(!flag){
			printf("Player 1 wins\n");
			fflush(stdout);
			return 0;
		}

		scanf("%d", &cur);
		cur--;
		g[cur][choose]--;
		mask[choose] ^= 1LL << cur;
	}
  return 0;
}
/*
                   _ooOoo_
                  o8888888o
                  88" . "88
                  (| -_- |)
                  O\  =  /O
               ____/`---'\____
             .'  \\|     |//  `.
            /  \\|||  :  |||//  \
           /  _||||| -:- |||||-  \
           |   | \\\  -  /// |   |
           | \_|  ''\---/''  |   |
           \  .-\__  `-`  ___/-. /
         ___`. .'  /--.--\  `. . __
      ."" '<  `.___\_<|>_/___.'  >'"".
     | | :  `- \`.;`\ _ /`;.`/ - ` : | |
     \  \ `-.   \_ __\ /__ _/   .-` /  /
======`-.____`-.___\_____/___.-`____.-'======
                   `=---='
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
         佛祖保佑       永无BUG
*/
