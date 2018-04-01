#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
#define mkp make_pair

const int ML[] = {0, 7, 6, 6, 5, 1,  1,  2,  2,  3,  2,  2,  1,  1,  5, 6, 6, 7};
const int MR[] = {0, 7, 7, 8, 8, 13, 12, 12, 11, 11, 11, 12, 12, 13, 8, 8, 7, 7};

const int dui[] = {0, 2, 1, 4, 3, 6, 5};

inline bool ck(int x, int y){
	return (x >= 1 && x <= 17 && y >= ML[x] && y <= MR[y]);
}

int tot;
int col[200], pcol[200];
int p[20][20];
bool ok[20][5000];
int L[200], R[200], UR[200], UL[200], LL[200], LR[200];
char s[10];
int rx[200], ry[200];

void init(){
	memset(col, 0, sizeof(col));

	for(int i = 1; i <= 4; ++i)
		for(int j = ML[i]; j <= MR[i]; ++j)
			col[p[i][j]] = 1;

	for(int i = 14; i <= 17; ++i)
		for(int j = ML[i]; j <= MR[i]; ++j)
			col[p[i][j]] = 2;
	
	int cur = 1;
	for(int i = 10; i <= 13; ++i, ++cur){
		for(int j = ML[i]; j < ML[i] + cur; ++j)
			col[p[i][j]] = 3;
	}
	
	cur = 1;
	for(int i = 10; i <= 13; ++i, ++cur){
		for(int j = MR[i]; j > MR[i] - cur; --j)
			col[p[i][j]] = 5;
	}

	cur = 4;
	for(int i = 5; i <= 8; ++i, --cur){
		for(int j = MR[i]; j > MR[i] - cur; --j)
			col[p[i][j]] = 4;
	}
		
	cur = 4;
	for(int i = 5; i <= 8; ++i, --cur){
		for(int j = ML[i]; j < ML[i] + cur; ++j)
			col[p[i][j]] = 6;
	}
	
	memcpy(pcol, col, sizeof(col));
}

int main(){
	ok[0][0] = 1;
	for(int l = 1; l <= 11; ++l){
		for(int mask = 1; mask < 1 << l; ++mask){
			ok[l][mask] = 1;
			for(int i = 0; i < l; ++i)
				ok[l][mask] &= (mask >> i & 1) == (mask >> (l - i - 1) & 1);
		}
	}
	
	for(int i = 1; i <= 17; ++i)
		for(int j = ML[i]; j <= MR[i]; ++j){
			p[i][j] = ++tot;
			rx[tot] = i;
			ry[tot] = j - ML[i] + 1;
		}
	
	for(int i = 1; i <= 17; ++i)
		for(int j = ML[i]; j <= MR[i]; ++j){
			
			int x = p[i][j];
			//L
			if(ck(i, j - 1)) L[x] = p[i][j - 1];
			//R
			if(ck(i, j + 1)) R[x] = p[i][j + 1];

			if(i & 1){
				//UL
				if(ck(i - 1, j - 1)) UL[x] = p[i - 1][j - 1];
				//UR
				if(ck(i - 1, j)) UR[x] = p[i - 1][j];
				//LL
				if(ck(i + 1, j - 1)) LL[x] = p[i + 1][j - 1];
				//LR
				if(ck(i + 1, j)) LR[x] = p[i + 1][j];
			}else{
				//UL
				if(ck(i - 1, j)) UL[x] = p[i - 1][j];
				//UR
				if(ck(i - 1, j + 1)) UR[x] = p[i - 1][j + 1];
				//LL
				if(ck(i + 1, j)) LL[x] = p[i + 1][j];
				//LR
				if(ck(i + 1, j + 1)) LR[x] = p[i + 1][j + 1];				
			}
		}
	
	
	int N;
	while(~scanf("%d", &N)){
		init();
		for(int i = 0; i < N; ++i){
			int x, y;
			scanf("%d%d%s", &x, &y, s);
			y = ML[x] + y - 1;
			int now = p[x][y], c = col[p[x][y]], pre = p[x][y], nex = p[x][y];

			if(c != i % 6 + 1) continue;
		
			if(s[0] == 'L'){
				if(s[1] == 'L'){ //LL
					int len = 0, num = 0;
					while(LL[now]){
						now = LL[now];
						
						if(!col[now] && (!pcol[now] || pcol[now] == c || pcol[now] == dui[c]) && ok[len][num])
							nex = now;
						
						num = (num << 1) | (col[now] > 0);
						len++;
					}
				}else if(s[1] == 'R'){ //LR
					int len = 0, num = 0;
					while(LR[now]){
						now = LR[now];
						
						if(!col[now] && (!pcol[now] || pcol[now] == c || pcol[now] == dui[c]) && ok[len][num])
							nex = now;
						
						num = (num << 1) | (col[now] > 0);
						len++;
					}
				}else{ //L
					int len = 0, num = 0;
					while(L[now]){
						now = L[now];
						
						if(!col[now] && (!pcol[now] || pcol[now] == c || pcol[now] == dui[c]) && ok[len][num])
							nex = now;
						
						num = (num << 1) | (col[now] > 0);
						len++;
					}
				}
			}else if(s[0] == 'U'){
				if(s[1] == 'L'){ //UL
					int len = 0, num = 0;
					while(UL[now]){
						now = UL[now];
						
						if(!col[now] && (!pcol[now] || pcol[now] == c || pcol[now] == dui[c]) && ok[len][num])
							nex = now;
						
						num = (num << 1) | (col[now] > 0);
						len++;
					}
				}else{ //UR
					int len = 0, num = 0;
					while(UR[now]){
						now = UR[now];
						
						if(!col[now] && (!pcol[now] || pcol[now] == c || pcol[now] == dui[c]) && ok[len][num])
							nex = now;
						
						num = (num << 1) | (col[now] > 0);
						len++;
					}
				}
			}else{ //R
				int len = 0, num = 0;
					while(R[now]){
						now = R[now];
						
						if(!col[now] && (!pcol[now] || pcol[now] == c || pcol[now] == dui[c]) && ok[len][num])
							nex = now;
						
						num = (num << 1) | (col[now] > 0);
						len++;
					}
			}
			col[pre] = 0;
			col[nex] = c;
			
			//printf("%d %d -> %d %d\n", rx[pre], ry[pre], rx[nex], ry[nex]);
		}
		
		vector<pair<int, int> > res[7];
		for(int i = 1; i <= 17; ++i)
			for(int j = ML[i]; j <= MR[i]; ++j)
				if(col[p[i][j]])
					res[col[p[i][j]]].pb(mkp(i, j - ML[i] + 1));
		
		for(int i = 1; i <= 6; ++i){
			assert(res[i].size() == 10);
			for(int j = 0; j < 10; ++j)
				printf("%d %d%c", res[i][j].first, res[i][j].second, " \n"[j == 9]);
		}
	}
	return 0;
}
