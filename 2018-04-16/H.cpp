#include<bits/stdc++.h>
using namespace std;

int n, m;
char h[55], r[55];
multiset<int> q;
int mp[55][55];

int main(){
    scanf("%s", h);
    scanf("%s", r);
    n = strlen(h);
    m = strlen(r);

    int zero_h = 0, zero_r = 0;
    for(int i = 0; i < n; ++i)
        if((m & 1) ^ (h[i] - '0')){
            q.insert(i);
            ++zero_h;
        }
    for(int i = 0; i < m; ++i)
        if((n & 1) ^ (r[i] - '0')){
            ++zero_r;
        }

    //printf("%d %d\n", zero_h, zero_r);
    if(abs(zero_r - zero_h) & 1){
        puts("-1");
        return 0;
    }
    while(zero_h < zero_r) q.insert(0), ++zero_h;
    while(zero_r < zero_h){
        int t = *q.begin(); q.erase(q.begin());
        mp[t][0] = 1;
        --zero_h;
    }
    for(int i = 0; i < m; ++i)
        if((n & 1) ^ (r[i] - '0')){
            int t = *q.begin(); q.erase(q.begin());
            mp[t][i] = 1;
        }

    for(int i = 0; i < n; puts(""), ++i)
        for(int j = 0; j < m; ++j)
            printf("%d", mp[i][j] ^ 1);

    return 0;
}
