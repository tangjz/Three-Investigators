#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

const int LMAX = 1100000, NODE_MAX = 3100000;
const int ALPHA = 26, MOD = 1000000007;

struct Edge;
struct Node;

struct Edge
{
	int l, r;//[)
	Node *tar;
};

struct Node
{
	char start, out;
	Node *sl, *fa;
	Edge next[ALPHA];
};

int Q, L, cnt, ans;
int pid, eid, did;
Node pool[NODE_MAX], *root = &pool[0], *End[LMAX];
int activeLength, reminder;
char activeEdge;
Node *activeNode = root;
char str[LMAX];

void suffixLink(Node *&cur, char &c, int &len, int left)
{
	int delta;
	len -= cur == root?1:0;
	left += cur == root?1:0;
	c = len?str[left]:0;
	cur = cur->sl?cur->sl:root;
	while(len && len >= (delta = ((cur->next[c - 'a'].r < 0?L:cur->next[c - 'a'].r) - cur->next[c - 'a'].l)))
	{
		len -= delta;
		cur = cur->next[c - 'a'].tar;
		left += delta;
		c = len?str[left]:0;
	}
}

bool trans(Node *&node, char &c, int &len, char x)
{
	bool flag = false;
	if(len)
	{
		if(str[node->next[c - 'a'].l + len] == x)
		{
			len += 1;
			flag = true;
		}
	}
	else
	{
		if(node->next[x - 'a'].tar)
		{
			len += 1;
			c = x;
			flag = true;
		}
	}
	if(flag && node->next[c - 'a'].r == node->next[c - 'a'].l + len)
	{
		node = node->next[c - 'a'].tar;
		c = len = 0;
	}
	return flag;
}

void link(Node *node, int pos)
{
	Node *n = End[++eid] = &pool[++pid];
	Edge *e = &node->next[str[pos] - 'a'];
	n->fa = node;
	n->start = str[pos];
	e->l = pos;
	e->r = -1;
	e->tar = n;

	node->out += 1;
}

Node *split(Node *&node, char &c, int &len)
{
	if(!len)
		return node;

	Node *n = &pool[++pid];
	Edge *faE = &node->next[c - 'a'];

	faE->tar->fa = n;
	faE->tar->start = str[faE->l + len];

	n->next[str[faE->l + len] - 'a'] = (Edge){faE->l + len, faE->r, faE->tar};

	n->fa = node;
	n->start = c;

	*faE = (Edge){faE->l, faE->l + len, n};

	n->out = 1;
	return n;
}

void insert(int pos)
{
	Node *s, *pre = NULL;
	reminder += 1;
	while(reminder)
	{
		if(trans(activeNode, activeEdge, activeLength, str[pos]))
			break;
		reminder -= 1;
		s = split(activeNode, activeEdge, activeLength);
		if(pre)
			pre->sl = s;
		link(s, pos);
		pre = s;
		if(reminder)
		{
			suffixLink(activeNode, activeEdge, activeLength, activeEdge?activeNode->next[activeEdge - 'a'].l:-1);
			if(!activeLength)
				pre->sl = activeNode;
		}
	}
	cnt = (cnt + eid - did) % MOD;
}

void del(Node *node)
{
	Edge *e;
	char last = 0;
	while(!node->out && node != activeNode)
	{
		node->fa->out -= 1;
		(e = &node->fa->next[(last = node->start) - 'a'])->tar = NULL;
		cnt = (cnt - ((e->r < 0?L:e->r) - e->l) + MOD) % MOD;
		node = node->fa;
	}
	if(node == activeNode)
	{
		if(activeLength)
		{
			if(last == activeEdge)
			{
				reminder -= 1;
				link(activeNode, L - activeLength);
				cnt = (cnt + activeLength) % MOD;
				suffixLink(activeNode, activeEdge, activeLength, L - activeLength);
			}
		}
		else if(!node->out)
		{
			reminder -= 1;
			activeNode = activeNode->fa;
			e = &node->fa->next[(activeEdge = node->start) - 'a'];
			e->l = L - (activeLength = (e->r - e->l));
			e->r = -1;
			End[++eid] = node;
			suffixLink(activeNode, activeEdge, activeLength, L - activeLength);
		}
	}
}

int main()
{
	int i;
	char c;
	scanf("%d", &Q);
	for(i = 0;i < Q;i += 1)
	{
		scanf(" %c", &c);
		if(c == '+')
		{
			scanf(" %c", &str[L]);
			insert(L);
			L += 1;
		}
		else
			del(End[++did]);
		ans = (ans + cnt) % MOD;
	}
	printf("%d\n", ans);
	exit(0);
}
