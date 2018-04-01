#include <set>
#include <stdio.h>
#include <algorithm>
using namespace std;
const int maxq = 60001, maxm = 5, maxs = 1 << maxm | 1;
int q, m, pos[maxq][maxm];
multiset<int> sp[maxs];
bool vis[maxq];
int main() {
	while(scanf("%d%d", &q, &m) == 2) {
		for(int i = 0; i < 1 << m; ++i)
			multiset<int>().swap(sp[i]);
		for(int i = 1; i <= q; ++i) {
			int typ;
			scanf("%d", &typ);
			if(typ == 0) {
				int *seq = pos[i];
				for(int j = 0; j < m; ++j)
					scanf("%d", seq + j);
				for(int j = 0; j < 1 << m; ++j) {
					int val = 0;
					for(int k = 0; k < m; ++k)
						((j >> k) & 1) ? val += seq[k] : val -= seq[k];
					sp[j].insert(val);
				}
				vis[i] = 1;
			} else {
				int idx;
				scanf("%d", &idx);
				if(vis[idx]) {
					vis[idx] = 0;
					int *seq = pos[idx];
					for(int j = 0; j < 1 << m; ++j) {
						int val = 0;
						for(int k = 0; k < m; ++k)
							((j >> k) & 1) ? val += seq[k] : val -= seq[k];
						sp[j].erase(sp[j].find(val));
					}
				}
			}
			if(sp[0].size() > 0) {
				int all = (1 << m) - 1;
				long long ans = 0;
				for(int i = 0; i <= (all >> 1); ++i) {
					ans = max(ans, abs((long long)*sp[i].begin() + *sp[all - i].begin()));
					ans = max(ans, abs((long long)*sp[i].rbegin() + *sp[all - i].rbegin()));
				}
				printf("%I64d\n", ans);
			} else {
				puts("0");
			}
		}
	}
	return 0;
}
