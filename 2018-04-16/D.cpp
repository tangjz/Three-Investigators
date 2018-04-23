#include<bits/stdc++.h>
using namespace std;

int n, m;
int a[100005], tag[100005];

int main(){
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= m; ++i){
        scanf("%d", a + i);
        tag[a[i]] = 1;
    }
    int i, j;
    for(i = 1, j = 1; i <= m; ++i){
        while(j <= a[i]){
            if(!tag[j]) printf("%d\n", j);
            ++j;
        }
        printf("%d\n", a[i]);
    }
    while(j <= n){
        if(!tag[j]) printf("%d\n", j);
        ++j;
    }
    //system("pause");
    return 0;
}
