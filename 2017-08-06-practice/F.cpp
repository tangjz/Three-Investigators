#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
#define ll long long
#define M 1000000007
#define all(a) a.begin(), a.end()
#define clean(x) memset(x, 0, sizeof(x));

const int inf = M;
const int maxn = 100100;
int size[maxn], son[maxn][2];
int ctag[maxn], atag[maxn];
bool rev[maxn];
int fa[maxn];
int t1[maxn], t2[maxn], num1[maxn], num2[maxn];
int n, m;
vector<int> g[maxn];
int num[maxn];

inline void down(int x){
    if (!x) return;
    if (rev[x]){
        swap(son[x][0],son[x][1]);
        if (son[x][0]) rev[son[x][0]]^=1;
        if (son[x][1]) rev[son[x][1]]^=1;
    }
    if (ctag[x]>-inf){
        num[x]=ctag[x];
        if(son[x][0]) ctag[son[x][0]]=ctag[x],atag[son[x][0]]=0;
        if(son[x][1]) ctag[son[x][1]]=ctag[x],atag[son[x][1]]=0;
    }
    if (atag[x]){
        num[x]+=atag[x];
        if (son[x][0]) atag[son[x][0]]+=atag[x];
        if (son[x][1]) atag[son[x][1]]+=atag[x];
    }
    rev[x]=0,ctag[x]=-inf,atag[x]=0;
}

inline void update(int x,int v,int t){
    if(v>t1[x]) t2[x]=t1[x],num2[x]=num1[x],t1[x]=v,num1[x]=t;
    else if(v==t1[x]) num1[x]+=t;
    else if(v>t2[x]) t2[x]=v,num2[x]=t;
    else if(v==t2[x]) num2[x]+=t;
}

inline void update(int x,int y){
    if(ctag[y]>-inf)
        update(x,ctag[y]+atag[y],size[y]);
    else{
        update(x,t1[y]+atag[y],num1[y]);
        if(t2[y] > -inf) update(x,t2[y]+atag[y],num2[y]);
    }
}

inline void updata(int x){
    size[x]=size[son[x][0]]+size[son[x][1]]+1; 
    t1[x]=t2[x]=-inf;
    assert(ctag[x]<=-inf&&atag[x]==0);
    update(x, num[x], 1);
    if (son[x][0]) update(x,son[x][0]);
    if (son[x][1]) update(x,son[x][1]);
}

inline bool truefa(int x){
    return (fa[x] && (x==son[fa[x]][0] || x==son[fa[x]][1]));
}

inline void rotate(int x){
    int y=fa[x],z=fa[y],k=x==son[y][1];
    if (truefa(y)) son[z][y==son[z][1]]=x; fa[x]=fa[y];
    if (son[x][k^1]) fa[son[x][k^1]]=y; son[y][k]=son[x][k^1];
    son[x][k^1]=y,fa[y]=x; updata(y);
}

inline void splay(int x){
    while (truefa(x)){
        int y=fa[x],z=fa[y];
        if (!truefa(y)) down(y),down(x),rotate(x);else{
            down(z),down(y),down(x);
            if ((x==son[y][0])^(y==son[z][0])) rotate(x),rotate(x);
            else rotate(y),rotate(x);
        }
    }down(x),updata(x);
}

inline int access(int x){
    int p=x,q=0;
    for (;p;p=fa[q]) splay(p),son[p][1]=q,updata(q=p);
    return q;
}

inline int findroot(int x){
    for (x=access(x);down(x),updata(x),son[x][0];x=son[x][0]); 
    splay(x); return x;
}

inline void makeroot(int x){    
    int p=access(x); rev[p]^=1; splay(x);
}

inline void link(int x,int y){
    if (findroot(x)==findroot(y)) return;
    makeroot(x); fa[x]=y; access(x);
}

inline void cut(int x,int y){
    if (findroot(x)!=findroot(y)) return;
    makeroot(x); access(y); splay(y);
    fa[son[y][0]]=0,son[y][0]=0; updata(y);
}

inline void modify_change(int x,int y,int data){
    makeroot(x),access(y),splay(x),atag[x]=0,ctag[x]=data;
}

inline void modify_add(int x,int y,int data){
    makeroot(x),access(y),splay(x),atag[x]+=data;
}

inline pair<int,int> query(int x,int y){
    if (findroot(x)!=findroot(y)) return mkp(-1,-1);
    makeroot(x),access(y),splay(x); return mkp(t2[x],num2[x]);
}

void DFS(int t){
    size[t]=1;
    for(auto v : g[t])
        if(fa[t]!=v) fa[v]=t,DFS(v);
}

int main(){
    int T, ca = 0;
    scanf("%d", &T);
    while(T--){
        clean(son);
        clean(fa);
        clean(rev);
        memset(ctag, 128, sizeof(ctag));
        clean(atag);
        clean(size);
        memset(t1, 128, sizeof(t1));
        memset(t2, 128, sizeof(t2));

        scanf("%d%d", &n, &m);
        for(int i = 1; i <= n; ++i) scanf("%d", num + i), g[i].clear();
        for(int i = 1; i < n; ++i){
            static int u, v;
            scanf("%d%d", &u, &v);
            g[u].pb(v);
            g[v].pb(u);
        }
        DFS(1);
        
        printf("Case #%d:\n", ++ca);
        while(m--){
            static int ty, x, y, a, b;
            scanf("%d%d%d", &ty, &x, &y);
            if(ty == 1){
                scanf("%d%d", &a, &b);
                cut(x, y);
                link(a, b);
            }else if(ty == 2){
                scanf("%d", &a);
                modify_change(x,y,a);
            }else if(ty == 3){
                scanf("%d", &a);
                modify_add(x,y,a);
            }else{
                auto res = query(x, y);
                if(res.fi <= -inf) printf("ALL SAME\n");
                else printf("%d %d\n", res.fi, res.se);
            }
        }
    }
    
    return 0;
}

