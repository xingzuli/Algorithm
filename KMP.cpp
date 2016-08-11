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

// ����next��
inline void makeNextTable(const string&T, vector<int>&next)
{
	// pos�ǵ�ǰ��ģʽ����λ�ã�cnd�����ͬ��ǰ׺��λ��
	int pos = 2;
	int cnd = 0;
	next[0] = -1;
	next[1] = 0;
	while (pos < T.size())
	{
		// ��һ��������Ӵ�ƥ��ɹ�����ǰ����
		if (T[pos - 1] == T[cnd]) // ���ڱȽϵ�����ǰ׺��������ǰһ���������Ƚ�
		{
			next[pos] = cnd + 1;
			cnd++;
			pos++;
		}
		// �ڶ���������Ӵ�ƥ��ʧ�ܣ�������ƥ�䵽��С�������硰aabaaa��
		else if (cnd > 0)
		{
			cnd = next[cnd];
		}
		// ������������Ӵ�ƥ��ʧ�ܣ���ʲô��ƥ�䲻��
		else
		{
			next[pos] = 0;
			pos++;
		}
	}
}

// ���ƥ��ɹ���λ�ã�����ĸ��������ֵ��ƥ��ɹ��Ĵ���
int countKMP(const string&S, const string&W)
{
	vector<int> next(W.size());

	makeNextTable(W, next);

	// print next��
	cout << "next��:" << endl;
	for (int i = 0; i < W.size(); ++i) {
		if (i == W.size() - 1) {
			cout << next[i] << endl;
		}
		else {
			cout << next[i] << " ";
		}
	}

	int m = 0; // S����ƥ��ĵ�һ��λ��
	int i = 0; // ģʽ�����Ѿ�ƥ�䵽��λ��
	int count = 0; // ƥ��ɹ��Ĵ���
	while (m+i < S.size())
	{
		if (W[i] == S[m + i]) { // ƥ��ɹ�
			if (i == W.size() - 1) // һ��ƥ�����
			{
				count++;
				cout << "The " << count << "th match at " << m << endl;
				m = m + i - next[i];
				i = next[i];
			}
			else // ƥ���˲��֣�����ƥ��
			{
				i++;
			}
		}
		else // ƥ��ʧ��
		{
			if (next[i] > -1) // ��Ȼ��ǰƥ��ʧ�ܣ����ǿ���ƥ�䵽��С��
			{
				m = m + i - next[i];
				i = next[i];
			}
			else // ��ȫ��ƥ�䣬���ӵ�һ����ĸ��Ͳ�ƥ����
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
	string S;// ԭ��
	string W;// ģʽ�� 
	cout << "input the origin string" << endl;
	cin >> S;
	cout << "intput the search string" << endl;
	cin >> W;
	int count = countKMP(S, W);
	cout << "The times match successfully: " << count << endl;
	system("PAUSE");
	return 0;
}