/*
	This Algorithm is reference from the wikipedia,
	It is used to find the searching string in a long string.
	Author: lizuxing
	2016-08-11 07:58:07
*/
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// 计算next表
inline void makeNextTable(const string&T, vector<int>&next)
{
	// pos是当前在模式串的位置，cnd是最长相同真前缀的位置
	int pos = 2;
	int cnd = 0;
	next[0] = -1;
	next[1] = 0;
	while (pos < T.size())
	{
		// 第一种情况：子串匹配成功，向前继续
		if (T[pos - 1] == T[cnd]) // 由于比较的是真前缀，这里是前一个数字来比较
		{
			next[pos] = cnd + 1;
			cnd++;
			pos++;
		}
		// 第二种情况，子串匹配失败，但可以匹配到更小串，比如“aabaaa”
		else if (cnd > 0)
		{
			cnd = next[cnd];
		}
		// 第三种情况，子串匹配失败，且什么都匹配不了
		else
		{
			next[pos] = 0;
			pos++;
		}
	}
}

// 输出匹配成功的位置（首字母），返回值是匹配成功的次数
int countKMP(const string&S, const string&W)
{
	vector<int> next(W.size());

	makeNextTable(W, next);

	// print next表
	cout << "next表:" << endl;
	for (int i = 0; i < W.size(); ++i) {
		if (i == W.size() - 1) {
			cout << next[i] << endl;
		}
		else {
			cout << next[i] << " ";
		}
	}

	int m = 0; // S串中匹配的第一个位置
	int i = 0; // 模式串中已经匹配到的位置
	int count = 0; // 匹配成功的次数
	while (m+i < S.size())
	{
		if (W[i] == S[m + i]) { // 匹配成功
			if (i == W.size() - 1) // 一次匹配完毕
			{
				count++;
				cout << "The " << count << "th match at " << m << endl;
				m = m + i - next[i];
				i = next[i];
			}
			else // 匹配了部分，继续匹配
			{
				i++;
			}
		}
		else // 匹配失败
		{
			if (next[i] > -1) // 虽然当前匹配失败，但是可以匹配到更小串
			{
				m = m + i - next[i];
				i = next[i];
			}
			else // 完全不匹配，即从第一个字母起就不匹配了
			{
				m++;
				i = 0;
			}
		}
	}
	
	return count;
}

int main()
{
	string S;// 原串
	string W;// 模式串 
	cout << "input the origin string" << endl;
	cin >> S;
	cout << "intput the search string" << endl;
	cin >> W;
	int count = countKMP(S, W);
	cout << "The times match successfully: " << count << endl;
	system("PAUSE");
	return 0;
}