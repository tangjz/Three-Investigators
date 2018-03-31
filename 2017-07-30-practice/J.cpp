#include <set>
#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 10001, maxm = 11, maxs = 4001, DELTA = 20, BAN = 5, MASK = 1 << 11;
int n, m, pro[maxn], pen[maxn], atp[maxn], acp[maxn], atc[maxn][maxm];
int cnt[maxm + 2], bit[maxm][maxs];
set<pair<int, int> > sp[maxm][maxs];
void bit_add(int bit[], int x, int v) {
	for( ; x < maxs; x += x & -x)
		bit[x] += v;
}
int bit_sum(int bit[], int x) {
	int ret = 0;
	for( ; x > 0; x -= x & -x)
		ret += bit[x];
	return ret;
}
int bit_que(int bit[], int k) {
	int x = 0;
	for(int y = MASK, z; y; y >>= 1)
		if((z = x | y) < maxs && bit[z] < k) {
			x = z;
			k -= bit[z];
		}
	return x + 1;
}
int main() {
	while(scanf("%d%d", &n, &m) == 2) {
		for(int i = 0; i <= m; ++i) {
			cnt[i] = 0;
			for(int j = 1; j < maxs; ++j) {
				bit[i][j] = 0;
				set<pair<int, int> >().swap(sp[i][j]);
			}
		}
		cnt[m + 1] = 0;
		for(int i = 0; i < n; ++i) {
			pro[i] = 0;
			pen[i] = 1;
			atp[i] = -BAN;
			acp[i] = -1;
			for(int j = 0; j < m; ++j)
				atc[i][j] = 0;

			++cnt[pro[i]];
			bit_add(bit[pro[i]], pen[i], 1);
			sp[pro[i]][pen[i]].insert(make_pair(acp[i], i));
		}
		for(int req = 0; ; ++req) {
			char op[9], buf[13];
			scanf("%s%s", op, buf);
			if(op[0] == 'S') {
				int tim, tid, pid, res;
				char pch;
				sscanf(buf, "%d:%d:%c:%d", &tim, &tid, &pch, &res);
				pid = pch - 'A';
				if(tim < atp[tid] + BAN || atc[tid][pid] < 0)
					continue;
				atp[tid] = tim;
				if(res == 1) {
					bit_add(bit[pro[tid]], pen[tid], -1);
					sp[pro[tid]][pen[tid]].erase(make_pair(acp[tid], tid));

					++pro[tid];
					pen[tid] += tim + atc[tid][pid];
					acp[tid] = req;
					atc[tid][pid] = -1;
					printf("[%d][%c]\n", tid, pch);

					++cnt[pro[tid]];
					bit_add(bit[pro[tid]], pen[tid], 1);
					sp[pro[tid]][pen[tid]].insert(make_pair(acp[tid], tid));
				} else {
					atc[tid][pid] += DELTA;
				}
			} else if(op[0] == 'T') {
				int rk, sol, pnt;
				sscanf(buf, "%d", &rk);
				if(rk > n) {
					puts("-1");
					continue;
				}
				for(sol = m; cnt[sol] < rk; --sol);
				pnt = bit_que(bit[sol], rk - cnt[sol + 1]);
				int id = sp[sol][pnt].begin() -> second;
				if(cnt[pro[id] + 1] + bit_sum(bit[pro[id]], pen[id] - 1) + 1 == rk)
					printf("%d\n", id);
				else
					puts("-1");
			} else if(op[0] == 'R') {
				int id;
				sscanf(buf, "%d", &id);
				printf("%d\n", cnt[pro[id] + 1] + bit_sum(bit[pro[id]], pen[id] - 1) + 1);
			} else {
				puts("");
				break;
			}
		}
	}
	return 0;
}
