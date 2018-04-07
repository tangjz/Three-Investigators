#include <bits/stdc++.h>
using namespace std;
const int maxm = (int)1.1e6 + 3, maxc = 39;
int tot, trans[257];
struct Node {
	int cnt, end, nxt[maxc];
} e[maxm];
void insert(int rt, char buf[]) {
	int cur = rt;
	for(int i = 0; buf[i]; ++i) {
		++e[cur].cnt;
		int o = trans[buf[i]];
		if(!e[cur].nxt[o]) {
			memset(e + tot, 0, sizeof e[0]);
			e[cur].nxt[o] = tot++;
		}
		cur = e[cur].nxt[o];
	}
	++e[cur].cnt;
	++e[cur].end;
}
int conflict(int rt, char buf[]) {
	int cur = rt, ret = 0;
	for(int i = 0; buf[i]; ++i) {
		if(e[cur].end)
			ret |= 4;
		int o = trans[buf[i]];
		if(!e[cur].nxt[o])
			return ret;
		cur = e[cur].nxt[o];
	}
	if(e[cur].cnt) {
		ret |= 2;
		if(e[cur].end)
			ret |= 5;
	}
	return ret;
}
int calc0(int rt, char buf[]) {
	int cur = rt, ret = 0;
	for(int i = 0; buf[i]; ++i) {
		if(rt && e[cur].end)
			++ret;
		int o = trans[buf[i]];
		if(!e[cur].nxt[o])
			return ret;
		cur = e[cur].nxt[o];
	}
	if(e[cur].end)
		++ret;
	return ret;
}
bool flag;
int calc1(int rt, char buf[]) {
	int cur = rt, ret = 0;
	for(int i = 0; buf[i]; ++i) {
		if(rt && e[cur].end) {
			++ret;
			flag = 1;
		}
		int o = trans[buf[i]];
		if(!e[cur].nxt[o])
			return ret;
		cur = e[cur].nxt[o];
	}
	flag |= e[cur].end;
	return ret += e[cur].cnt;
}
char dom[maxm], vpn[maxm];
inline bool isLower(char ch) {
	return ch >= 'a' && ch <= 'z';
}
inline bool isDigit(char ch) {
	return ch >= '0' && ch <= '9';
}
int main() {
	memset(trans, -1, sizeof trans);
	for(int i = 0; i < 26; ++i)
		trans['a' + i] = i;
	for(int i = 0; i < 10; ++i)
		trans['0' + i] = 26 + i;
	trans['.'] = 36;
	trans['-'] = 37;
	int n;
	while(scanf("%d", &n) == 1) {
		tot = 0;
		for(int i = 0; i < 3; ++i)
			memset(e + (tot++), 0, sizeof e[0]);
		int cnt = 0;
		while(n--) {
			scanf("%s%s", dom, vpn);
			int dlen = strlen(dom), dtyp = dom[0] == '*' ? 1 : (dom[0] == '#' ? 2 : 0);
			bool chk = isLower(dom[0]) || isDigit(dom[0])
				|| ((dom[0] == '*' || dom[0] == '#') && (!dom[1] || dom[1] == '.'));
			for(int i = 1; chk && dom[i]; ++i)
				chk &= isLower(dom[i]) || isDigit(dom[i])
					|| (dom[i] == '-' && i && isLower(dom[i - 1]) && isLower(dom[i + 1]))
					|| (dom[i] == '.' && dom[i + 1] && dom[i + 1] != '.');
			chk &= isLower(vpn[0]);
			for(int i = 1; chk && vpn[i]; ++i)
				chk &= isLower(vpn[i]) || isDigit(vpn[i])
					|| (vpn[i] == '-' && i && isLower(vpn[i - 1]) && isLower(vpn[i + 1]));
			if(!chk) {
				++cnt;
			} else {
				char *dsta = dom + (dtyp > 0);
				reverse(dsta, dom + dlen);
				if(conflict(0, dsta) & (dtyp == 1 ? 2 : 1)
				|| conflict(1, dsta) & (dtyp == 1 ? 6 : 4)
				|| conflict(2, dsta) & (dtyp > 0 ? (dtyp == 1 ? 2 : 6) : 0)) {
					++cnt;
				} else {
					insert(dtyp, dsta);
				}
			}
		}
		printf("%d\n", cnt);
		scanf("%d", &n);
		while(n--) {
			scanf("%s", dom);
			int dlen = strlen(dom), dtyp = dom[0] == '*' ? 1 : 0;
			if(dtyp) {
				reverse(dom + 1, dom + dlen);
				flag = 0;
				printf("%d\n", calc1(0, dom + 1) + calc1(1, dom + 1) + (flag ? 0 : calc1(2, dom + 1)));
			} else {
				reverse(dom, dom + dlen);
				int ctr = calc0(0, dom) + calc0(1, dom);
				if(!ctr)
					ctr += calc0(2, dom);
				printf("%d\n", ctr);
			}
		}
	}
	return 0;
}
