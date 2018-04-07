#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;

const int TMAX = 2600;
const int INF = ~0u>>2;

int N, M, tid, pre, ans;
vector<int> tower[TMAX];
vector<int> level[TMAX];
map<int, int> v2idx;
int block[TMAX];
int f[TMAX][TMAX], notLast[TMAX];
bool valid[TMAX][TMAX];

int main()
{
	int i, j, k, t, h, x;
	int cas = 0;
	vector<int> value;
	while(scanf("%d", &N) != EOF)
	{
		memset(valid, 0, sizeof(valid));
		memset(block, 0, sizeof(block));
		memset(notLast, 0, sizeof(notLast));
		value.erase(value.begin(), value.end());
		v2idx.clear();
		pre = 0;
		tid = 0;

		cas += 1;
		for(i = 1;i <= N;i += 1)
		{
			tower[i].erase(tower[i].begin(), tower[i].end());
			scanf("%d", &h);
			for(j = 1;j <= h;j += 1)
			{
				scanf("%d", &x);
				tower[i].push_back(x);
				value.push_back(x);
			}
		}
		sort(value.begin(), value.end());
		value.erase(unique(value.begin(), value.end()), value.end());
		M = value.size();
		for(i = 0;i < value.size();i += 1)
		{
			v2idx[value[i]] = i + 1;
			level[i + 1].erase(level[i + 1].begin(), level[i + 1].end());
		}
		for(i = 1;i <= N;i += 1)
		{
			for(j = 0;j < tower[i].size();j += 1)
				tower[i][j] = v2idx[tower[i][j]];
		}
		tid = N;
		for(i = 1;i <= N;i += 1)
		{
			for(j = tower[i].size() - 1;j >= 0;j -= 1)
			{
				if(j - 1 >= 0 && tower[i][j - 1] < tower[i][j] - 1)
				{
					tower[++tid] = vector<int>(tower[i].begin() + j, tower[i].end());
					tower[i].erase(tower[i].begin() + j, tower[i].end());
					pre += 1;
				}
			}
		}

		/*
		for(i = 1;i <= tid;i += 1)
		{
			printf("tower[%d]: ", i);
			for(j = 0;j < tower[i].size();j += 1)
				printf("%d ", tower[i][j]);
			printf("\n");
		}
		*/

		for(i = 1;i <= tid;i += 1)
		{
			block[tower[i][0]] += 1;
			level[tower[i][0]].push_back(i);
			if(tower[i][0] != tower[i][tower[i].size() - 1])
				notLast[tower[i][0]] += 1;
			for(j = 1;j < tower[i].size();j += 1)
			{
				if(tower[i][j] != tower[i][j - 1])
				{
					block[tower[i][j]] += 1;
					level[tower[i][j]].push_back(i);
					if(tower[i][j] != tower[i][tower[i].size() - 1])
						notLast[tower[i][j]] += 1;
				}
			}
		}

		/*
		for(i = 1;i <= M;i += 1)
			printf("notLast[%d]: %d\n", i, notLast[i]);
		*/

		f[1][0] = notLast[1] + block[1] - 1;
		valid[1][0] = true;
		for(i = 0;i < level[1].size();i += 1)
		{
			t = level[1][i];
			f[1][t] = (notLast[1] - (tower[t][tower[t].size() - 1] != 1?1:0)) + block[1] - 1;
			valid[1][t] = true;
		}
		for(i = 2;i <= M;i += 1)
		{
			f[i][0] = INF;
			for(j = 0;j < level[i].size();j += 1)
			{
				if(valid[i - 1][level[i][j]])
					f[i][0] = min(f[i][0], f[i - 1][level[i][j]]);
			}
			f[i][0] += notLast[i] + block[i] - 1;
			f[i][0] = min(f[i][0], f[i - 1][0] + notLast[i] + block[i]);
			valid[i][0] = true;
			//printf("f[%d][t:%d]: %d\n", i, 0, f[i][0]);

			for(j = 0;j < level[i].size();j += 1)
			{
				t = level[i][j];
				f[i][t] = INF;
				for(k = 0;k < level[i].size();k += 1)
				{
					if(level[i][k] == t || !valid[i - 1][level[i][k]])
						continue;
					f[i][t] = min(f[i][t], f[i - 1][level[i][k]]);
				}
				f[i][t] += (notLast[i] - (tower[t][tower[t].size() - 1] != i?1:0)) + block[i] - 1;
				if(block[i] == 1 && valid[i - 1][t])
					f[i][t] = min(f[i][t], f[i - 1][t]);
				f[i][t] = min(f[i][t], f[i - 1][0] + (notLast[i] - (tower[t][tower[t].size() - 1] != i?1:0)) + block[i]);
				valid[i][t] = true;
				//printf("f[%d][t:%d]: %d\n", i, t, f[i][t]);
			}
		}
		ans = INF;
		for(i = 1;i <= tid;i += 1)
		{
			if(valid[M][i])
				ans = min(ans, f[M][i]);
		}
		printf("Case %d: %d\n", cas, pre + ans);
	}
	exit(0);
}
