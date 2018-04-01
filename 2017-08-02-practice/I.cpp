#include <set>
#include <map>
#include <string>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 50001, maxm = 27, maxs = 21, DT = 20;
int t, n, m, fro, lim, tot;
struct Submission {
	int cid, pid, tim, res;
	bool operator < (Submission const &t) const {
		return tim < t.tim || (tim == t.tim && res < t.res);
	}
} seq[maxn];
struct Team {
	char name[maxs];
	int sol, pen, las[maxm], low, cnt[maxm];
	bool typ[maxm];
	vector<int> frz[maxm];
	void init(char _name[]) {
		strcpy(name, _name);
		sol = pen = low = 0;
		memset(cnt, 0, m * sizeof(int));
		memset(typ, 0, m * sizeof(bool));
	}
	void resort() {
		for(int i = sol - 1; i > 0; --i)
			if(las[i - 1] < las[i])
				break;
			else
				swap(las[i - 1], las[i]);
	}
	bool unfro() {
		for( ; low < m && !frz[low].size(); ++low);
		if(low >= m)
			return 0;
		for(vector<int>::iterator it = frz[low].begin(); it != frz[low].end(); ++it) {
			Submission cur = seq[*it];
			if(cur.res > 0) {
				typ[low] = 1;
				las[sol++] = cur.tim;
				resort();
				pen += cur.tim + DT * cnt[low];
				break;
			} else if(!cur.res)
				++cnt[low];
		}
		vector<int>().swap(frz[low]);
		return 1;
	}
} team[maxn];
struct Comp {
	bool operator () (int const &x, int const &y) const {
		Team u = team[x], v = team[y];
		if(u.sol != v.sol)
			return u.sol < v.sol;
		if(u.pen != v.pen)
			return u.pen > v.pen;
		for(int i = u.sol - 1; i >= 0; --i)
			if(u.las[i] != v.las[i])
				return u.las[i] > v.las[i];
		return strcmp(u.name, v.name) < 0;
	}
} cmp;
set<int, Comp> sp, tp;
map<string, int> Hash;
void print_board(set<int, Comp> const &sp) {
	int rk = 0;
	for(set<int, Comp>::iterator it = sp.end(); it != sp.begin(); ) {
		Team cur = team[*(--it)];
		printf("%s %d %d %d ", cur.name, ++rk, cur.sol, cur.pen);
		for(int i = 0; i < m; ++i) {
			if(cur.typ[i]) {
				if(cur.cnt[i])
					printf("+%d", cur.cnt[i]);
				else
					putchar('+');
			} else if(!cur.frz[i].size()) {
				if(cur.cnt[i])
					printf("-%d", cur.cnt[i]);
				else
					putchar('.');
			} else {
				if(cur.cnt[i])
					printf("-%d", cur.cnt[i]);
				else
					putchar('0');
				printf("/%d", (int)cur.frz[i].size());
			}
			putchar(" \n"[i == m - 1]);
		}
	}
}
int main() {
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case) {
		scanf("%d%d%d%d", &n, &m, &lim, &fro);
		tot = 0;
		map<string, int>().swap(Hash);
		for(int i = 0; i < n; ++i) {
			int cid, tim;
			char buf[maxs], pch[3], res[5];
			scanf("%s%s%d%s", buf, pch, &tim, res);
			if(Hash.count(buf))
				cid = Hash[buf];
			else {
				team[tot].init(buf);
				cid = Hash[buf] = tot++;
			}
			seq[i] = (Submission){cid, (int)(pch[0] - 'A'), tim, (res[0] == 'Y') - (res[0] == 'E')};
		}
		sort(seq, seq + n);
		int pos = 0;
		for( ; pos < n && seq[pos].tim < fro; ++pos) {
			Submission cur = seq[pos];
			int cid = cur.cid, pid = cur.pid;
			if(team[cid].typ[pid])
				continue;
			if(cur.res > 0) {
				team[cid].typ[pid] = 1;
				team[cid].las[team[cid].sol++] = cur.tim;
				team[cid].pen += cur.tim + DT * team[cid].cnt[pid];
			} else if(!cur.res) {
				++team[cid].cnt[pid];
			}
		}
		for( ; pos < n; ++pos) {
			int cid = seq[pos].cid, pid = seq[pos].pid;
			if(team[cid].typ[pid])
				continue;
			team[cid].frz[pid].push_back(pos);
		}
		set<int, Comp>().swap(sp);
		set<int, Comp>().swap(tp);
		for(int i = 0; i < tot; ++i)
			sp.insert(i);
		printf("Case #%d:\n", Case);
		print_board(sp);
		team[tot] = team[*sp.begin()];
		while(1) {
			set<int, Comp>::iterator it = sp.lower_bound(tot);
			if(it == sp.end())
				break;
			int id = *it;
			sp.erase(id);
			team[tot] = team[id];
			while(1) {
				if(!team[id].unfro()) {
					tp.insert(id);
					break;
				}
				set<int, Comp>::iterator jt = sp.lower_bound(id);
				if(sp.size() > 0 && jt != sp.begin() && cmp(tot, *(--jt))) {
					printf("%s %s %d %d\n", team[id].name, team[*jt].name, team[id].sol, team[id].pen);
					sp.insert(id);
					break;
				}
			}
		}
		print_board(tp);
	}
	return 0;
}
