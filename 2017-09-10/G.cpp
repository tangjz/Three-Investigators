#include <cstdio>
#include <cstring>
const int maxn = 100001, maxd = 17;

namespace fastIO {
	#define BUF_SIZE 100001
    #define OUT_SIZE 100001
	//fread -> read
	bool IOerror = 0;
	inline char nc() {
		static char buf[BUF_SIZE], *p1 = buf + BUF_SIZE, *pend = buf + BUF_SIZE;
		if(p1 == pend) {
			p1 = buf;
			pend = buf + fread(buf, 1, BUF_SIZE, stdin);
			if(pend == p1) {
				IOerror = 1;
				return -1;
			}
		}
		return *p1++;
	}
	inline bool blank(char ch) {
		return ch == ' ' || ch == '\n' || ch == '\r' || ch == '\t';
	}
	inline void read(int &x) {
		char ch;
		while(blank(ch = nc()));
		if(IOerror)
			return;
		for(x = ch - '0'; (ch = nc()) >= '0' && ch <= '9'; x = x * 10 + ch - '0');
	}
    //fwrite->write
    struct Ostream_fwrite{
        char *buf,*p1,*pend;
        Ostream_fwrite(){buf=new char[OUT_SIZE];p1=buf;pend=buf+OUT_SIZE;}
        void out(char ch){
            if (p1==pend){
                fwrite(buf,1,OUT_SIZE,stdout);p1=buf;
            }
            *p1++=ch;
        }
        void print(int x){
            static char s[15],*s1;s1=s;
            if (!x)*s1++='0';if (x<0)out('-'),x=-x;
            while(x)*s1++=x%10+'0',x/=10;
            while(s1--!=s)out(*s1);
        }
        void println(int x){
            static char s[15],*s1;s1=s;
            if (!x)*s1++='0';if (x<0)out('-'),x=-x;
            while(x)*s1++=x%10+'0',x/=10;
            while(s1--!=s)out(*s1); out('\n');
        }
        void print(const char *s){while (*s)out(*s++);}
        void flush(){if (p1!=buf){fwrite(buf,1,p1-buf,stdout);p1=buf;}}
        ~Ostream_fwrite(){flush();}
    }Ostream;
    inline void print(int x){Ostream.print(x);}
    inline void println(int x){Ostream.println(x);}
    inline void print(const char *s){Ostream.print(s);}
    inline void flush(){Ostream.flush();}
	#undef BUF_SIZE
    #undef OUT_SIZE
}
using namespace fastIO;

int t, n, m, q, lnk[maxn], lst[maxn], pre[maxn], tot, bcc[maxn];
int seq[maxn], in[maxn], out[maxn], dep[maxn], mx, fa[maxd][maxn], bit[maxn], dsu[maxn], pos[maxn];
struct Edge {
	int nxt, v;
} e[maxn << 1 | 1], g[maxn << 1 | 1];
bool vis[maxn];
int tarjan(int u, int Fa) {
	int lowu = pre[u] = ++tot;
	for(int it = lnk[u]; it != -1; it = e[it].nxt) {
		if(Fa == (it ^ 1))
			continue;
		int v = e[it].v;
		if(pre[v] == -1) {
			int lowv = tarjan(v, it);
			if(lowu > lowv)
				lowu = lowv;
			if(pre[u] < lowv)
				vis[it >> 1] = 1;
		} else if(lowu > pre[v])
			lowu = pre[v];
	}
	return lowu;
}
void pfs(int u) {
	bcc[u] = tot;
	for(int it = lnk[u]; it != -1; it = e[it].nxt)
		if(!vis[it >> 1] && bcc[e[it].v] == -1)
			pfs(e[it].v);
}
void bit_add(int x, int v) {
	for( ; x <= n; x += x & -x)
		bit[x] += v;
}
int bit_sum(int x) {
	int ret = 0;
	for( ; x > 0; x -= x & -x)
		ret += bit[x];
	return ret;
}
void dfs(int u) {
	in[u] = ++tot;
	for(int it = lst[u]; it != -1; it = g[it].nxt) {
		int v = g[it].v;
		if(v == fa[0][u])
			continue;
		dep[v] = dep[u] + 1;
		fa[0][v] = u;
		dfs(v);
	}
	out[u] = tot;
	bit_add(in[u], 1);
	bit_add(out[u] + 1, -1);
}
int lca(int u, int v) {
	for(int i = dep[u] - dep[v], j = 0; i > 0; i >>= 1, ++j)
		(i & 1) && (u = fa[j][u]);
	for(int i = dep[v] - dep[u], j = 0; i > 0; i >>= 1, ++j)
		(i & 1) && (v = fa[j][v]);
	if(u == v)
		return u;
	for(int i = mx - 1; i >= 0; --i)
		if(fa[i][u] != fa[i][v]) {
			u = fa[i][u];
			v = fa[i][v];
		}
	return fa[0][u];
}
int dsu_find(int x) {
	return dsu[x] < 0 ? x : (dsu[x] = dsu_find(dsu[x]));
}
void dsu_merge(int u, int v) { // u into v
	u = dsu_find(u);
	v = dsu_find(v);
	if(dsu[u] < dsu[v]) { // but v into u
		dsu[v] = u;
		pos[u] = pos[v];
	} else if(dsu[u] > dsu[v]) {
		dsu[u] = v;
	} else {
		dsu[u] = v;
		--dsu[v];
	}
}
int main() {
	read(t);
	for(int Case = 1; Case <= t; ++Case) {
		read(n), read(m);
		memset(lnk + 1, -1, n * sizeof(int));
		for(int i = 0; i < m; ++i) {
			int u, v;
			read(u), read(v);
			e[i << 1] = (Edge){lnk[u], v};
			lnk[u] = i << 1;
			e[i << 1 | 1] = (Edge){lnk[v], u};
			lnk[v] = i << 1 | 1;
			vis[i] = 0;
		}
		tot = 0;
		memset(pre + 1, -1, n * sizeof(int));
		tarjan(1, -1);
		tot = 0;
		memset(bcc + 1, -1, n * sizeof(int));
		for(int i = 1; i <= n; ++i)
			if(bcc[i] == -1) {
				++tot;
				pfs(i);
			}
		m = 0;
		memset(lst + 1, -1, tot * sizeof(int));
		for(int i = 1; i <= n; ++i)
			for(int it = lnk[i]; it != -1; it = e[it].nxt) {
				int j = e[it].v;
				if(i < j && bcc[i] != bcc[j]) {
					int u = bcc[i], v = bcc[j];
					g[m] = (Edge){lst[u], v};
					lst[u] = m++;
					g[m] = (Edge){lst[v], u};
					lst[v] = m++;
				}
			}
		n = tot;
		tot = 0;
		dep[1] = fa[0][1] = 0;
		memset(bit + 1, 0, n * sizeof(int));
		dfs(1);
		for(mx = 0; 1 << mx <= n; ++mx);
		for(int i = 1; i < mx; ++i)
			for(int j = 1; j <= n; ++j)
				fa[i][j] = fa[i - 1][fa[i - 1][j]];
		memset(dsu + 1, -1, n * sizeof(int));
		for(int i = 1; i <= n; ++i)
			pos[i] = i;
		read(q);
		print("Case #"), print(Case), print(":\n");
		while(q--) {
			int typ, u, v;
			read(typ), read(u), read(v);
			u = bcc[u], v = bcc[v];
			int pp = lca(u, v);
			if(typ == 1) {
				for(int x = pos[dsu_find(u)]; dep[pp] < dep[x]; x = pos[dsu_find(x)]) {
					bit_add(in[x], -1);
					bit_add(out[x] + 1, 1);
					dsu_merge(x, fa[0][x]);
				}
				for(int x = pos[dsu_find(v)]; dep[pp] < dep[x]; x = pos[dsu_find(x)]) {
					bit_add(in[x], -1);
					bit_add(out[x] + 1, 1);
					dsu_merge(x, fa[0][x]);
				}
			} else {
				int ans = bit_sum(in[u]) + bit_sum(in[v]) - (bit_sum(in[pp]) << 1);
				println(ans);
			}
		}
	}
	return 0;
}
