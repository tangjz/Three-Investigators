#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
#define ll long long
#define M 1000000007
#define all(a) a.begin(), a.end()

pair<int, int> id[8][9], tid[8][9], trans[24][8][9];
int cnt;
int p[8][9];

void work(int o, int x, int y, int z, int p, int q, int r){
	printf("%d %d %d %d %d %d %d\n", o, x, y, z, p, q, r);
	//L
	memcpy(tid, id, sizeof(id));
	tid[x][0] = id[y][8];
	tid[y][8] = id[z][4];
	tid[z][4] = id[x][0];

	tid[p][0] = id[q][4];
	tid[p][2] = id[q][5];
	tid[p][1] = id[q][6];
	tid[p][5] = id[q][7];
	tid[p][4] = id[q][8];
		
	tid[q][4] = id[r][8];
	tid[q][5] = id[r][7];
	tid[q][6] = id[r][3];
	tid[q][7] = id[r][2];
	tid[q][8] = id[r][0];
		
	tid[r][8] = id[p][0];
	tid[r][7] = id[p][2];
	tid[r][3] = id[p][1];
	tid[r][2] = id[p][5];
	tid[r][0] = id[p][4];
		
	tid[o][0] = id[o][8];
	tid[o][1] = id[o][3];
	tid[o][2] = id[o][7];
	tid[o][3] = id[o][6];
	tid[o][4] = id[o][0];
	tid[o][5] = id[o][2];
	tid[o][6] = id[o][1];
	tid[o][7] = id[o][5];
	tid[o][8] = id[o][4];
	memcpy(trans[cnt++], tid, sizeof(tid));
	//R		
	memcpy(tid, id, sizeof(id));
	tid[x][0] = id[z][4];
	tid[z][4] = id[y][8];
	tid[y][8] = id[x][0];

	tid[p][0] = id[r][8];
	tid[p][2] = id[r][7];
	tid[p][1] = id[r][3];
	tid[p][5] = id[r][2];
	tid[p][4] = id[r][0];
		
	tid[r][8] = id[q][4];
	tid[r][7] = id[q][5];
	tid[r][3] = id[q][6];
	tid[r][2] = id[q][7];
	tid[r][0] = id[q][8];
		
	tid[q][4] = id[p][0];
	tid[q][5] = id[p][2];
	tid[q][6] = id[p][1];
	tid[q][7] = id[p][5];
	tid[q][8] = id[p][4];

	tid[o][0] = id[o][4];
	tid[o][1] = id[o][6];
	tid[o][2] = id[o][5];
	tid[o][3] = id[o][1];
	tid[o][4] = id[o][8];
	tid[o][5] = id[o][7];
	tid[o][6] = id[o][3];
	tid[o][7] = id[o][2];
	tid[o][8] = id[o][0];
	memcpy(trans[cnt++], tid, sizeof(tid));
}

void work2(int a, int b, int c, int d, int e, int f){
	//L
	memcpy(tid, id, sizeof(id));
	tid[a][3] = id[e][1];
	tid[a][7] = id[e][2];
	tid[a][6] = id[e][3];

	tid[b][3] = id[f][6];
	tid[b][2] = id[f][7];
	tid[b][1] = id[f][3];

	tid[c][6] = id[a][3];
	tid[c][5] = id[a][7];
	tid[c][1] = id[a][6];

	tid[d][1] = id[b][3];
	tid[d][5] = id[b][2];
	tid[d][6] = id[b][1];

	tid[e][1] = id[c][6];
	tid[e][2] = id[c][5];
	tid[e][3] = id[c][1];

	tid[f][6] = id[d][1];
	tid[f][7] = id[d][5];
	tid[f][3] = id[d][6];
	memcpy(trans[cnt++], tid, sizeof(tid));
	//R
	memcpy(tid, id, sizeof(id));
	tid[a][3] = id[c][6];
	tid[a][7] = id[c][5];
	tid[a][6] = id[c][1];

	tid[b][3] = id[d][1];
	tid[b][2] = id[d][5];
	tid[b][1] = id[d][6];

	tid[c][6] = id[e][1];
	tid[c][5] = id[e][2];
	tid[c][1] = id[e][3];

	tid[d][1] = id[f][6];
	tid[d][5] = id[f][7];
	tid[d][6] = id[f][3];

	tid[e][1] = id[a][3];
	tid[e][2] = id[a][7];
	tid[e][3] = id[a][6];

	tid[f][6] = id[b][3];
	tid[f][7] = id[b][2];
	tid[f][3] = id[b][1];
	memcpy(trans[cnt++], tid, sizeof(tid));
}

bool check(int p[8][9]){
	for(int i = 0; i < 8; ++i)
		for(int j = 0; j < 9; ++j)
			if(p[i][j] != p[i][0]) return 0;
	return 1;
}

bool dfs(int step, int p[8][9]){
	if(check(p)) return 1;
	if(step == 3) return 0;
	int pp[8][9];
	for(int i = 0; i < cnt; ++i){
		for(int j = 0; j < 8; ++j)
			for(int k = 0; k < 9; ++k){
				int x = trans[i][j][k].fi, y = trans[i][j][k].se;
				pp[j][k] = p[x][y];
			}
		if(dfs(step + 1, pp)) return 1;
	}
	return 0;
}

int main(){
	for(int i = 0; i < 8; ++i)
		for(int j = 0; j < 9; ++j)
			id[i][j] = mkp(i, j);

	for(int i = 0; i < 4; ++i){
		int o = i;
		int x = (i + 2) % 4, y = (i + 1) % 4 + 4, z = (i + 3) % 4 + 4;
		int p = (i + 1) % 4, q = i + 4, r = (i + 3) % 4;
		work(o, x, y, z, p, q, r);
	}

	for(int i = 0; i < 4; ++i){
		int o = i + 4;
		int x = (i + 2) % 4 + 4, y = (i + 3) % 4, z = (i + 1) % 4;
		int p = (i + 3) % 4 + 4, q = i, r = (i + 1) % 4 + 4;
		work(o, x, y, z, p, q, r);
	}

	for(int i = 0; i < 4; ++i){
		int a = (i + 1) % 4, b = (i + 2) % 4, c = (i + 3) % 4, d = (i + 3) % 4 + 4, e = i + 4, f = (i + 1) % 4 + 4;
		work2(a, b, c, d, e, f);
	}

	int T;
	scanf("%d", &T);
	while(T--){
		for(int i = 0; i < 8; ++i)
			for(int j = 0; j < 9; ++j)
				scanf("%d", p[i] + j);
		if(dfs(0, p)) printf("YES\n");
		else printf("NO\n");
	}
	
#ifndef ONLINE_JUDGE
	system("pause");
#endif
	return 0;
}
