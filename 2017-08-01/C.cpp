#include <cstdio>
#include <cstdlib>
#include <cstring>

using namespace std;

const int NMAX = 501000, KMAX = 90;

struct Node
{
	int pre;
	int next;
};

int T;
int N, K;
int A[NMAX], pos[NMAX];
long long ans;
Node node[NMAX];

void del(Node n)
{
	node[n.pre].next = n.next;
	node[n.next].pre = n.pre;
}

void insert(Node n, int pos)
{
	node[n.pre].next = pos;
	node[n.next].pre = pos;
}

int toLeft(int pos)
{
	return node[pos].pre;
}

int toRight(int pos)
{
	return node[pos].next;
}

int main()
{
	int t;
	int i, j;
	int left[KMAX], right[KMAX];
	long long tmp;
	scanf("%d", &T);
	for(t = 0;t < T;t += 1)
	{
		ans = 0;
		scanf("%d %d", &N, &K);
		A[0] = pos[0] = 0;
		A[N + 1] = pos[N + 1] = N + 1;
		for(i = 1;i <= N;i += 1)
		{
			scanf("%d", &A[i]);
			pos[A[i]] = i;
		}
		for(i = 1;i <= N;i += 1)
			node[i] = (Node){A[pos[i] - 1], A[pos[i] + 1]};
		node[0] = (Node){0, A[1]};
		node[N + 1] = (Node){A[N], N + 1};
		for(i = 1;i <= N;i += 1)
			del(node[i]);
		for(i = N;i;i -= 1)
		{
			//printf("cal %d\n", i);
			insert(node[i], i);
			left[0] = i;
			for(j = 1;j <= K;j += 1)
			{
				left[j] = toLeft(left[j - 1]);
				//printf("%d%c", left[j], " \n"[j + 1 == K?1:0]);
			}
			right[0] = i;
			for(j = 1;j <= K;j += 1)
			{
				right[j] = toRight(right[j - 1]);
				//printf("%d%c", right[j], " \n"[j + 1 == K?1:0]);
			}
			for(j = K, tmp = 0;j;j -= 1)
			{
				//printf("%d * %d\n", pos[left[j - 1]] - pos[left[j]], pos[right[K - j + 1]] - pos[right[K - j]]);
				tmp += (long long)(pos[left[j - 1]] - pos[left[j]]) * (pos[right[K - j + 1]] - pos[right[K - j]]);
			}
			//printf("cnt: %lld\n", tmp);
			ans += tmp * i;
		}
		printf("%lld\n", ans);
	}
	exit(0);
}
