#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <algorithm>
#include <deque>

using namespace std;

struct Sign
{
	char opt;
	int level;
	int pos;
};

struct Number
{
	int value;
	int level;
	int pos;
};

inline int priority(char opt)
{
	int res = 0;
	switch(opt)
	{
		case 'n':
			res += 1;
		case '*':
			res += 1;
		case '+':
		case '-':
			res += 1;
		case 'e':
			res += 1;
		case ')':
			res += 1;
		case '(':
			break;
	}
	return res;
}

bool expel(deque<Sign> &sign, deque<Number> &number, const int level, char opt)
{
	int p = priority(opt);
	Number num1, num2;
	Sign tmpSign;
	char tmp;
	while(!sign.empty() && sign.back().level == level && priority(sign.back().opt) >= p)
	{
		tmpSign = sign.back();
		tmp = tmpSign.opt;
		sign.pop_back();
		switch(tmp)
		{
			case '+':
				if(number.size() < 2)
					return false;
				num2 = number.back();
				number.pop_back();
				num1 = number.back();
				number.pop_back();
				if(num1.level != level || num2.level != level || num1.pos > tmpSign.pos || num2.pos < tmpSign.pos)
					return false;
				number.push_back((Number){num1.value + num2.value, level, num1.pos});
				break;
			case '-':
				if(number.size() < 2)
					return false;
				num2 = number.back();
				number.pop_back();
				num1 = number.back();
				number.pop_back();
				if(num1.level != level || num2.level != level || num1.pos > tmpSign.pos || num2.pos < tmpSign.pos)
					return false;
				number.push_back((Number){num1.value - num2.value, level, num1.pos});
				break;
			case 'n':
				if(number.size() < 1)
					return false;
				num1 = number.back();
				number.pop_back();
				if(num1.level != level || num1.pos < tmpSign.pos)
					return false;
				number.push_back((Number){-num1.value, level, tmpSign.pos});
				break;
			case '*':
				if(number.size() < 2)
					return false;
				num2 = number.back();
				number.pop_back();
				num1 = number.back();
				number.pop_back();
				if(num1.level != level || num2.level != level || num1.pos > tmpSign.pos || num2.pos < tmpSign.pos)
					return false;
				number.push_back((Number){num1.value * num2.value, level, num1.pos});
				break;
		}
	}
	return true;
}

bool eval(char str[], int l, int r, int &res)
{
	int cur, level, num, mCnt;
	bool neg = true, flag = true;
	Number tmpNum;
	deque<Sign> sign;
	deque<Number> number;

	level = 0;
	for(cur = l;cur < r && flag;cur += 1)
	{
		if(isdigit(str[cur]))
		{
			num = str[cur] - '0';
			for(cur += 1;cur < r && isdigit(str[cur]);cur += 1)
				num = (num<<1) + str[cur] - '0';
			cur -= 1;
			number.push_back((Number){num, level, cur});
			neg = false;
		}
		else if(str[cur] == '(')
		{
			level += 1;
			sign.push_back((Sign){str[cur], level, cur});
			neg = true;
		}
		else if(str[cur] == ')')
		{
			flag = flag && expel(sign, number, level, str[cur]);
			if(sign.empty() || sign.back().opt != '(' || sign.back().level != level)
				flag = false;
			else
				sign.pop_back();
			if(number.empty() || number.back().level != level)
				flag = false;
			else
			{
				tmpNum = number.back();
				number.pop_back();
				tmpNum.level -= 1;
				number.push_back(tmpNum);
			}
			level -= 1;
			neg = false;
		}
		else
		{
			if(!neg || str[cur] != '-')
			{
				flag = flag && expel(sign, number, level, str[cur]);
				sign.push_back((Sign){str[cur], level, cur});
			}
			else
			{
				for(mCnt = 0;cur < r && str[cur] == '-';cur += 1, mCnt += 1);
				cur -= 1;
				if(mCnt & 1)
					sign.push_back((Sign){'n', level, cur});
			}
			neg = true;
		}
	}
	flag = flag && expel(sign, number, level, 'e');
	flag = flag && sign.empty() && number.size() == 1;
	if(flag)
		res = number.back().value;
	return flag;
}

int N, ans;
char expr[50], table[1000];
char fin[50], lookup[9] = {'=', '+', '-', '*', '0', '1', '(', ')'};
bool use[1000];

bool check()
{
	int i, j, ecnt = 0, epos;
	int res1, res2;
	bool flag = true;
	for(i = 0;i < N && flag;i += 1)
	{
		if(i + 1 < N && fin[i] == fin[i + 1] && (fin[i] == '+' || fin[i] == '*'))
			flag = false;
	}
	for(i = 0;i < N && flag;i += 1)
	{
		if(fin[i] != '0' && fin[i] != '1')
			continue;
		for(j = i;j < N && (fin[j] == '0' || fin[j] == '1');j += 1);
		if(j - i > 1 && fin[i] == '0')
			flag = false;
		i = j - 1;
	}
	for(i = 0;i < N && flag;i += 1)
	{
		if(fin[i] == '=')
		{
			epos = i;
			ecnt += 1;
		}
	}
	if(ecnt != 1)
		flag = false;
	if(flag)
	{
		flag = flag && eval(fin, 0, epos, res1);
		flag = flag && eval(fin, epos + 1, N, res2);
		flag = flag && (res1 == res2);
	}
	return flag;
}

void DFS(int cur)
{
	int i;
	if(cur >= N)
	{
		if(check())
			ans += 1;
		return;
	}
	if(('a' <= expr[cur] && expr[cur] <= 'z')
		|| ('A' <= expr[cur] && expr[cur] <= 'Z'))
	{
		if(table[(int)expr[cur]])
		{
			fin[cur] = table[(int)expr[cur]];
			DFS(cur + 1);
		}
		else
		{
			for(i = 0;lookup[i];i += 1)
			{
				if(use[(int)lookup[i]])
					continue;
				table[(int)expr[cur]] = lookup[i];
				use[(int)lookup[i]] = true;
				fin[cur] = lookup[i];
				DFS(cur + 1);
				use[(int)lookup[i]] = false;
				table[(int)expr[cur]] = 0;
			}
		}
	}
	else
	{
		fin[cur] = expr[cur];
		DFS(cur + 1);
	}
}

int main()
{
	scanf("%s", expr);
	N = strlen(expr);
	DFS(0);
	printf("%d\n", ans);
	exit(0);
}
