#include <cstdio>
#include <cstring>
#include <algorithm>
const int maxn = 300001, maxm = 500001;
int n, m, qtot, que[maxm], tot, ord[maxm], tmp[maxm], ans[maxm];
struct Query {
	int typ, a, b, c;
	// typ 1 : [a, b] add c
	// typ 2 : [a, b] del c
	// typ 3 : query a
} query[maxm];
int st, tim[maxn], bit[maxn];
void bit_add(int x, int v) {
	for( ; x <= n; x += x & -x) {
		if(tim[x] != st) {
			tim[x] = st;
			bit[x] = 0;
		}
		bit[x] += v;
	}
}
int bit_sum(int x) {
	int ret = 0;
	for( ; x > 0; x -= x & -x)
		if(tim[x] == st)
			ret += bit[x];
	return ret;
}
void solve(int L, int R, int vL, int vR) {
	if(L > R || vL > vR)
		return;
	if(vL == vR) {
		for( ; L <= R; ans[ord[L++]] = vL);
		return;
	}
	int vM = (vL + vR) >> 1;
	++st;
	for(int i = L; i <= R; ++i) {
		Query &cur = query[ord[i]];
		if(cur.typ == 3) {
			ans[ord[i]] = bit_sum(cur.a);
		} else if(cur.c <= vM) {
			int coeff = cur.typ == 1 ? 1 : -1;
			bit_add(cur.a, coeff);
			bit_add(cur.b + 1, -coeff);
		}
	}
	int M = L - 1;
	tot = 0;
	for(int i = L; i <= R; ++i) {
		Query &cur = query[ord[i]];
		if(cur.typ == 3) {
			if(ans[ord[i]])
				ord[++M] = ord[i];
			else
				tmp[++tot] = ord[i];
		} else if(cur.c <= vM) {
			ord[++M] = ord[i];
		} else {
			tmp[++tot] = ord[i];
		}
	}
	for(int i = 1; i <= tot; ++i)
		ord[M + i] = tmp[i];
	solve(L, M, vL, vM);
	solve(M + 1, R, vM + 1, vR);
}
int main() {
	freopen("invazia.in", "r", stdin);
	freopen("invazia.out", "w", stdout);
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; ++i) {
		Query &cur = query[i];
		char op[3];
		scanf("%s", op);
		if(op[0] == 'I') {
			cur.typ = 1;
			scanf("%d%d%d", &cur.a, &cur.b, &cur.c);
			ord[++tot] = i;
			que[++qtot] = cur.c;
		} else if(op[0] == 'E') {
			Query &pre = query[ord[tot--]];
			cur = (Query){2, pre.a, pre.b, pre.c};
		} else { // op[0] == 'R'
			cur.typ = 3;
			scanf("%d", &cur.a);
		}
	}
	std::sort(que + 1, que + qtot + 1);
	qtot = std::unique(que + 1, que + qtot + 1) - que - 1;
	++st;
	tot = 0;
	for(int i = 1; i <= m; ++i) {
		Query &cur = query[i];
		if(cur.typ == 3) {
			if(bit_sum(cur.a))
				ord[++tot] = i;
		} else {
			int coeff = cur.typ == 1 ? 1 : -1;
			bit_add(cur.a, coeff);
			bit_add(cur.b + 1, -coeff);
			cur.c = std::lower_bound(que + 1, que + qtot + 1, cur.c) - que;
			ord[++tot] = i;
		}
	}
	solve(1, tot, 1, qtot);
	for(int i = 1; i <= m; ++i) {
		if(query[i].typ != 3)
			continue;
		if(ans[i])
			printf("%d\n", que[ans[i]]);
		else
			puts("GUITZZZ!");
	}
	return 0;
}
