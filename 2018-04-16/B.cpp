#include<bits/stdc++.h>
using namespace std;
#define all(x) x.begin(), x.end()
#define pb push_back

const int maxn = 200005;
int cal_tmp;
vector<int> g[maxn];
vector<int> res;
int n, m;
bool tag[maxn];
int lim;

inline bool check_link(int p, int q){
    int t = lower_bound(all(g[p]), q) - g[p].begin();
    return t < g[p].size() && g[p][t] == q;
}

bool check(int t){
    cal_tmp = g[t].size();
    int n = g[t].size();
    for(int i = 0; i < n; ++i){
        int p = g[t][i], q;
        for(int j = i + 1; j < n; ++j){
            q = g[t][j];
            if(!check_link(p, q)) return 0;
        }
        cal_tmp += g[p].size();
    }
    cal_tmp = (cal_tmp - n * (n + 1) / 2) == m;
    return 1;
}

bool check_tuan(){
    for(int i = 1; i <= n; ++i)
        if(tag[i]) res.pb(i);
    if(res.size() > lim) return 0;
    int n = res.size();
    cal_tmp = 0;
    for(int i = 0; i < n; ++i){
        int p = res[i], q;
        for(int j = i + 1; j < n; ++j){
            q = res[j];
            if(!check_link(p, q)) return 0;
        }
        cal_tmp += g[p].size();
    }
    return (cal_tmp - n * (n - 1) / 2) == m;
}

bool solve(){
    for(int i = 1; i <= n; ++i){
        if(g[i].size() >= lim) tag[i] = 1;
        else{
            if(check(i)){
                if(cal_tmp){
                    tag[i] = 1;
                    for(int v : g[i]) tag[v] = 1;
                    return check_tuan();
                }
            }else tag[i] = 1;
        }
    }
    return check_tuan();
}

int main(){
    scanf("%d%d", &n, &m);

    map<pair<int, int>, bool> mp;
    for(int i = 1, x, y; i <= m; ++i){
        scanf("%d%d", &x, &y);
        if(x == y){
            --i; --m;
            continue;
        }
        if (x > y) swap(x, y);
        if(mp.count(make_pair(x, y))){
            --i; --m;
            continue;
        }mp[make_pair(x, y)] = 1;
        g[x].pb(y);
        g[y].pb(x);
    }
    lim = 1;
    while(lim * (lim + 1) / 2 <= m) ++lim;
    //printf("%d\n", m);
    for(int i = 1; i <= n; ++i)
        sort(all(g[i]));

    if(!solve()) puts("0");
    else{
        //for(int v : res) printf("p:%d\n", v);
        
        for(int v : res) tag[v] = 1;
        vector<int> fk;
        for(int i = 1; i <= n; ++i)
            if(!tag[i]) fk.pb(i);

        int ans = 1;
        for(int v : res)
            if(g[v].size() == res.size() - 1) ++ans;;
        for(int v : fk)
            if(g[v].size() == res.size()) ++ans;
        for(int v : fk)
            if(g[v].size() >= res.size() - 1)
                for(int u : res)
                    if(g[v].size() >= res.size() - !check_link(u, v) &&
                         g[u].size() == res.size() - 1 + check_link(u, v)){
                        ++ans;
                    }
        printf("%d\n", ans);                    
    }
    return 0;
}
