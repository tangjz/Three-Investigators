#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
 
const int maxn = 100100;
int T, n, a[maxn], f[maxn], g[maxn];
vector<int> ed[maxn];
 
void dfs(int t, int fa){
    f[t] = g[t] = 0;
    for(int i = 0; i < (int)ed[t].size(); ++i){
        int v = ed[t][i];
        if(v == fa) continue;
        dfs(v, t);
        f[t] ^= g[v];  
        g[t] ^= g[v];
    }
    f[t] ^= 1;
    g[t] ^= f[t];
}
 
int main(){
    scanf("%d", &T);
    while(T--){
        scanf("%d", &n);
        for(int i = 1; i <= n; ++i) scanf("%d", a + i), ed[i].clear();
 
        for(int i = 1; i < n; ++i){
            int u, v;
            scanf("%d%d", &u, &v);
            ed[u].push_back(v);
            ed[v].push_back(u);
        }
        dfs(1, 0);
        int ans = 0;
        for(int i = 1; i <= n; ++i)
            if(a[i]) ans ^= f[i];
        printf("%s\n", ans ? "Alice" : "Bob");
    }
    return 0;  
}
