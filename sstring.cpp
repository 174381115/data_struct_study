#include <iostream>
#include <sys/time.h>
#include <algorithm>
#include <cstdlib>
#include <cstring>

using namespace std;

#define MAX_ELEM 	255


/*
 * ����˳��洢���Ͷ���
 *
 * ע����ЧԪ�ش�SString��1�ŵ�Ԫ��ʼ�洢
 *     SString��0�ŵ�Ԫ�����洢�䳤��
 */
typedef unsigned char SString[MAX_ELEM+1];

int StrCompare(SString s1, SString s2);

void PrintString(SString s)
{
		for(int i=1; i<=s[0]; i++)
		{
			cout << (char)s[i];
		}
		
		cout << endl;
}


//����һ��ֵΪchars�Ĵ�dst��
bool StrAssign(SString dst, const char* src)
{
		if(src == NULL)
		{
				return false;
		}
		
		int len = strlen(src);
		if(len > MAX_ELEM)
		{
				return false;
		}
		
		memset(dst, 0, sizeof(SString));
		dst[0] = len;
		memcpy(dst+1, src, len);
		return true;
}

// ����ַ���
void ClearString(SString s)
{
		s[0] = 0;
}

// �ж��ַ����Ƿ�Ϊ��
bool StrEmpty(SString s)
{
	 return s[0] == 0 ? true : false;
}

// �����ַ����ĳ���
int StrLength(SString s)
{
		return s[0];
}


//pos��1��ʼ�����س���ΪLen���Ӵ�
bool SubString(SString sub, SString s, int pos, int len)
{
		if(pos + len > MAX_ELEM)
		{
				return false;
		}
		
		memcpy(sub+1, s+pos, len);
		sub[0] = len;
		return true;
}

//��pos����ʼ����ģʽ��T������S���״γ��ֵ�λ�ã���������ڣ��򷵻�0��
//������ҳɹ�������ƥ���λ�á�
int Index_1(SString s, SString sub, int pos)
{
		int i = pos;
		SString tmp;
		
		cout << s[0]-sub[0]+1 << endl;
		if(pos < 1 || pos > (s[0]-sub[0]+1) || StrEmpty(sub))
		{
				return -1;
		}
		
		//��λ��1 - (m-n+1)��ʼ�Ƚ��Ӵ��Ƿ����
		int n = StrLength(sub);
		int m = StrLength(s);
		while( i <= m-n+1)
		{
				
				SubString(tmp, s, i, n);
				if(!StrCompare(tmp, sub))
				{
						return i;
				}
				
				i++;
		}
		
		return 0;
}

//��pos����ʼ����ģʽ��T������S���״γ��ֵ�λ�ã���������ڣ��򷵻�0��
//������ҳɹ�������ƥ���λ�á�
int Index_2(SString s, SString sub, int pos)
{
		if(pos < 1 || pos > (s[0]-sub[0]+1) || StrEmpty(sub))
		{
				return -1;
		}
		
		int i = pos;
		int j = 1;
		
		// ���ȷ�Χ�ж�		
		while(i <= s[0] && j <= sub[0])
		{
				// ��������ַ���ȣ�������Ƚ���һ���ַ�
				if(s[i] == sub[j])
				{
						i++;
						j++;
				}
				else
				{
						// ����������ַ�����ȣ�����˵��ϴ�ƥ����λ����һ���ַ�
						i = i-j+2;
						j = 1;
				}	
		}
		
		// ���j�����Ӵ��ĳ��ȣ�˵���������ַ�����ƥ��ɹ���
		if(j > sub[0])
		{
				return i - sub[0];
		}
		
		return -1;
}

//����sub���뵽����S��posλ�ô���
bool StrInsert(SString s, int pos, SString sub)
{
		if(s[0] + sub[0] > MAX_ELEM || pos < 1)
		{
				return false;
		}
		
		// �����Ϊ�մ�
		if(sub[0] == 0)
		{
				return true;
		}
		
		SString tmp;
		
		SubString(tmp, s, pos, s[0]-pos+1);
		
		memcpy(s+pos, sub+1, sub[0]);
		memcpy(s+pos+sub[0], tmp+1, tmp[0]);
		
		s[0] += sub[0];
		return true;
}

// * ɾ��S[pos, pos+len-1]��
bool StrDelete(SString s, int pos, int len)
{
		if(pos < 1 || (pos + len -1) > s[0] || len < 0)
		{
				return false;
		}
		
		if(len == 0)
		{
				return true;
		}
		
		
		// ��ɾ����֮����ַ�����ǰ�ƶ�
		for(int i=pos+len; i<=s[0]; i++)
		{
				s[i-len] = s[i];	
		}
		
		// ���´��ĳ���
		s[0] -= len;
		return true;
}

//����src���Ƶ���dst��
bool StrCopy(SString dst, SString src)
{
		dst[0] = src[0];
		
		memcpy(dst+1, src+1, src[0]);
		return false;
}

//�Ƚϴ�S�ʹ�T�����رȽϽ��
int StrCompare(SString s1, SString s2)
{
		int i=1;
		
		// �Ƚ���̳��ȸ��ַ��������һ���ַ�����ȣ���Ƚ�
		// �μ��ַ�������ȵĶ���
		while(i<s1[0] && i<s2[0])
		{
				if(s1[i] != s2[i])
				{
						return s1[i] - s2[i];
				}
				
				i++;
		}
		
		return s1[0] - s2[0];
}


//��x�滻����s�г��ֵ�������y��ȵ��Ҳ��ص����Ӵ���
bool Replace(SString s, SString x, SString y)
{
		if(StrEmpty(y))
		{
				return false;	
		}
		
		int pos = 1;
		int index = Index_2(s, y, pos);
		
		
		// ��Ҫ�����滻�����������index + StrLength(x) > MAX_ELEM
		while(index>0 && (index + StrLength(x) <= MAX_ELEM))
		{
				// �滻����
				int i=index;
				int j = 1;
		/*		for(; j<=StrLength(x); i++, j++)
				{
						s[i] = x[j];
				} */
				
				// ��ɾ��y
				StrDelete(s, index, StrLength(y));	
				
				// �ڲ���x
				if(!StrInsert(s, index, x))
				{
						cout << "StrInsert failed" << endl;
				}

				pos = index + StrLength(x);
				index = Index_2(s, y, pos);
		}
		
		if(index > 0)
		{
				cout << "Relace failed." << endl;
				return false;
		}
		return true;
}


// ����S1��S2�����洢��T�з��ء�������Ӻ�ĳ����������ֻ����δ����Ĳ��֡�
// ����ֵ��ʾ���Ӻ�Ĵ��Ƿ�������
bool Concat(SString ns, SString s1, SString s2)
{
		int is2_len = 0;
		
		StrCopy(ns, s1);
		
		// ���㻹�ܲ�������ݳ���
		is2_len = MAX_ELEM - StrLength(s1);
		
		if(is2_len > 0)
		{
				// ����ʣ�µ��ַ�
				int i = StrLength(ns) + 1;
				int j = 1;
				for(; j<=is2_len; i++, j++)
				{
						ns[i] = s2[j];
				}
				
				ns[0] = ns[0] + is2_len;
		}
		
		return true;
}

int main(int argc, char** argv)
{
		const char* chString = "Hello world world Workd!! world456";
		
		SString s;
		StrAssign(s, chString);
		
		PrintString(s);
		
		StrDelete(s, 2, 3);
		
		PrintString(s);
		
		SString si;
		StrAssign(si, "test");
		StrInsert(s, 2, si);
		cout << "After insert:" << endl;
		PrintString(s);
		
		SString s_copy;
		
		StrCopy(s_copy, s);
		PrintString(s_copy);
		
		cout << "StrCompare:" << StrCompare(s, s_copy) << endl;
		
		SString s2;
		StrAssign(s2, "abcdefghijk");
		cout << "StrCompare:" << StrCompare(s_copy, s2) << endl;
		
		SString s3;
		StrAssign(s3, "world");
		cout << "Index of world: " << Index_1(s, s3, 1) << endl;
		cout << "Index of world: " << Index_2(s, s3, 1) << endl;
		
		
		cout << "Test replace." << endl;
		Replace(s, s2, s3);
		PrintString(s);
		
		SString s4;
		Concat(s4, s, s3);
		PrintString(s4);
		return 0;
}