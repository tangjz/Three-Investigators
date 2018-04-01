#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
#define ll long long
#define M 1000000007
#define all(a) a.begin(), a.end()

int ha[2], hd[2], he[2], hs[2], hn[2], hzp[2];
int aa[2][7], ad[2][7], ab[2][7], ram[2][7], am[2][7], as[2][7], nowh[2][7], w[2][7];
bool fan[2][7];
bool kk;

void input(bool k){
	scanf("%d%d%d%d%d%d", ha + k, hd + k, he + k, hs + k, hn + k, hzp + k);
	he[k] *= 10, hs[k] *= 50;
	for(int i = 0; i < hn[k]; ++i) scanf("%d", aa[k] + i), aa[k][i] += ha[k];
	for(int i = 0; i < hn[k]; ++i) scanf("%d", ad[k] + i), ad[k][i] += hd[k];
	for(int i = 0; i < hn[k]; ++i) scanf("%d", ab[k] + i);
	for(int i = 0; i < hn[k]; ++i) scanf("%d", am[k] + i), ram[k][i] = am[k][i];
	for(int i = 0; i < hn[k]; ++i) scanf("%d", as[k] + i);
	for(int i = 0; i < hn[k]; ++i) nowh[k][i] = ab[k][i], w[k][i] = i;
	kk = k;
	sort(w[k], w[k] + hn[k], [](int i, int j) { return (as[kk][i] > as[kk][j]) || (as[kk][i] == as[kk][j] && i < j); });
}

void output(bool k){
	for(int i = 0; i < hn[k]; ++i)
		printf("%d%c", ram[k][i] - am[k][i], " \n"[i == hn[k] - 1]);
}

inline bool check(bool k){
	for(int i = 0; i < hn[k]; ++i)
		if(am[k][i]) return 1;
	return 0;
}

inline int find(bool k){
	int t = 0;
	for(int i = 1; i < hn[k]; ++i)
		if(am[k][i] > am[k][t]) t = i;
	return t;
}

inline void attack(bool from, int x, int y, int inj, bool re){
	bool to = from ^ 1;
	while(am[to][y] && inj){
		if(inj <= ad[to][y]){
			--nowh[to][y];
			if(!nowh[to][y]) nowh[to][y] = ab[to][y], --am[to][y];
			break;
		}else{
			inj -= ad[to][y];
			int tmp = min(nowh[to][y], inj);
			inj -= tmp;
			nowh[to][y] -= tmp;
			if(!nowh[to][y]) nowh[to][y] = ab[to][y], --am[to][y];
		}
	}

	if(re && am[to][y] && !fan[to][y]){
		fan[to][y] = 1;
		attack(to, y, x, aa[to][y] * am[to][y], 0);
	}
}

inline void treat(bool k){
	int t = -1;
	for(int i = 0; i < hn[k]; ++i)
		if(am[k][i] && (t == -1 || ab[k][i] - nowh[k][i] > ab[k][t] - nowh[k][t]))
			t = i;
	nowh[k][t] = min(nowh[k][t] + 20, ab[k][t]);
}

int main(){
	int T;
	scanf("%d", &T);
	while(T--){
		input(0);
		input(1);
		while(check(0) && check(1)){
			memset(fan, 0, sizeof(fan));
			int t;
			if(he[0] >= 12) t = find(1), attack(0, 0, t, hs[0], 0), he[0] -= 12;
			if(!check(1)) break;
			if(he[1] >= 12) t = find(0), attack(1, 0, t, hs[1], 0), he[1] -= 12;
			if(!check(0)) break;
			for(int i = 0, j = 0; i < hn[0] || j < hn[1];){
				while(i < hn[0] && !am[0][w[0][i]]) ++i;
				if(!check(1)) break;
				if(i < hn[0]){
					t = find(1);
					attack(0, w[0][i], t, aa[0][w[0][i]] * am[0][w[0][i]], 1);
					++i;
				}
				if(!check(0)) break;
				while(j < hn[1] && !am[1][w[1][j]]) ++j;
				if(j < hn[1] && check(0)){
					t = find(0);
					attack(1, w[1][j], t, aa[1][w[1][j]] * am[1][w[1][j]], 1);
					++j;
				}
			}
			if(hzp[0] && check(0)) treat(0);
			if(hzp[1] && check(1)) treat(1);
		}
		if(check(0)) printf("Win!\n");
		else printf("Lose!\n");
		output(0);
		output(1);
	}
	
	return 0;
}
