#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <vector>
 
using namespace std;
 
const int NMAX = 1001000, MOD = 19260817;
 
int N, ans, tree[NMAX];
vector<pair<int, int> > S;
 
inline int lowbit(int x)
{
    return x & (-x);
}
 
void add(int x, int v)
{
    while(x <= N)
    {
        tree[x] = max(tree[x], v);
        x += lowbit(x);
    }
}
 
int query(int x)
{
    int res = 0;
    while(x)
    {
        res = max(res, tree[x]);
        x -= lowbit(x);
    }
    return res;
}
 
int main()
{
    int i, x;
    while(scanf("%d", &N) != EOF)
    {
        ans = 0;
        memset(tree, 0, sizeof(tree));
        S.clear();
        for(i = 0;i < N;i += 1)
        {
            scanf("%d", &x);
            S.push_back(make_pair(x, i + 1));
        }
        sort(S.begin(), S.end());
        for(i = 0;i < N;i += 1)
        {
            ans = (ans + query(S[i].second)) % MOD;
            add(S[i].second, S[i].first);
        }
        printf("%d\n", ans);
    }
    exit(0);
}
