#include <iostream>
#include <sys/time.h>
#include <algorithm>
#include <cstdlib>
#include <cstring>

using namespace std;  //test


/*
 * ����˳��洢���Ͷ���
 *
 */
struct HString
{
		char* data;			// �洢�ַ������ڴ�
		int length;			// ʵ���ַ����ĳ���
};

int StrCompare(HString s1, HString s2);

// ��ӡ�Ѵ�
void PrintString(HString s)
{
		for(int i=0; i<s.length; i++)
		{
			cout << s.data[i];
		}
		
		cout << endl;
}


//����һ��ֵΪchars�Ĵ�dst��
bool StrAssign(HString* dst, const char* src)
{
		if(src == NULL)
		{
				return false;
		}
		
		int len = strlen(src);
		if(len == 0)
		{
				dst->length = 0;
				dst->data = NULL;
				return true;
		}
		
		dst->data = new char[len+1];
		memset(dst->data, 0, len+1);
		
		memcpy(dst->data, src, len);
		dst->length = len;
		return true;
}

// ����ַ���
void ClearString(HString* s)
{
		if(s == NULL)
		{
				return;
		}
		
		if(s->data)
		{
				delete[] s->data;
				s->data = NULL;
				s->length = 0;
				return;
		}
}

// �ж��ַ����Ƿ�Ϊ��
bool StrEmpty(HString s)
{
	 return s.length == 0 ? true : false;
}

// �����ַ����ĳ���
int StrLength(HString s)
{
		return s.length;
}


//pos��0��ʼ�����س���ΪLen���Ӵ�
bool SubString(HString* sub, HString s, int pos, int len)
{
		if(pos + len > s.length)
		{
				return false;
		}
		
		sub->data = new char[len+1];
		memset(sub->data, 0, len+1);
		
		memcpy(sub->data, s.data+pos, len);
		sub->length = len;
		return true;
}

//��pos����ʼ����ģʽ��T������S���״γ��ֵ�λ�ã���������ڣ��򷵻�0��
//������ҳɹ�������ƥ���λ�á�
int Index_1(HString s, HString sub, int pos)
{
		int i = pos;
		HString tmp;
		
		if(pos < 0 || pos > (s.length-sub.length+1) || StrEmpty(sub))
		{
				return -1;
		}
		
		//��λ��1 - (m-n+1)��ʼ�Ƚ��Ӵ��Ƿ����
		int n = StrLength(sub);
		int m = StrLength(s);
		while( i <= m-n+1)
		{
				
				SubString(&tmp, s, i, n);
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
int Index_2(HString s, HString sub, int pos)
{
		if(pos < 0 || pos > (s.length-sub.length+1) || StrEmpty(sub))
		{
				return -1;
		}
		
		int i = pos;
		int j = 0;
		
		// ���ȷ�Χ�ж�		
		while(i < s.length && j < sub.length)
		{
				// ��������ַ���ȣ�������Ƚ���һ���ַ�
				if(s.data[i] == sub.data[j])
				{
						i++;
						j++;
				}
				else
				{
						// ����������ַ�����ȣ�����˵��ϴ�ƥ����λ����һ���ַ�
						i = i-j+1;
						j = 0;
				}	
		}
		
		// ���j�����Ӵ��ĳ��ȣ�˵���������ַ�����ƥ��ɹ���
		if(j >= sub.length)
		{
				return i - sub.length;
		}
		
		return -1;
}

//����sub���뵽����S��posλ�ô���
bool StrInsert(HString* s, int pos, HString sub)
{
		if(pos < 0)
		{
				return false;
		}
		
		// �����Ϊ�մ�
		if(sub.length == 0)
		{
				return true;
		}
		
		//���·����ڴ�
		char *nd = new char[s->length+sub.length+1];
		
		memset(nd, 0, s->length+sub.length+1);
		
		// ����pos֮ǰ������
		memcpy(nd, s->data, pos);
		
		// ����Ҫ������Ӵ�
		memcpy(nd+pos, sub.data, sub.length);
		
		// ����s��pos֮����Ӵ�
		memcpy(nd+pos+sub.length, s->data+pos, s->length - pos);
		
		s->length += sub.length;
		delete[] s->data;
		
		s->data = nd;
		return true;
}

// * ɾ��S[pos, pos+len-1]��
bool StrDelete(HString* s, int pos, int len)
{
		if(pos < 0 || (pos + len -1) > s->length || len < 0)
		{
				return false;
		}
		
		if(len == 0)
		{
				return true;
		}
		
		
		// ��ɾ����֮����ַ�����ǰ�ƶ�
		for(int i=pos+len; i<=s->length; i++)
		{
				s->data[i-len] = s->data[i];	
		}
		
		// ���´��ĳ���
		s->length -= len;
		return true;
}

//����src���Ƶ���dst��
bool StrCopy(HString* dst, HString src)
{
		dst->length = src.length;
		
		if(StrEmpty(src))
		{
				dst->data = NULL;
				return true;
		}
		
		dst->data = new char[src.length + 1];
		memset(dst->data, 0, src.length+1);
		
		memcpy(dst->data, src.data, src.length);
		return true;
}

//�Ƚϴ�S�ʹ�T�����رȽϽ��
int StrCompare(HString s1, HString s2)
{
		int i=0;
		
		// �Ƚ���̳��ȸ��ַ��������һ���ַ�����ȣ���Ƚ�
		// �μ��ַ�������ȵĶ���
		while(i<s1.length && i<s2.length)
		{
				if(s1.data[i] != s2.data[i])
				{
						return s1.data[i] - s2.data[i];
				}
				
				i++;
		}
		
		return s1.length - s2.length;
}


//��x�滻����s�г��ֵ�������y��ȵ��Ҳ��ص����Ӵ���
bool Replace(HString* s, HString x, HString y)
{
		if(StrEmpty(y))
		{
				return false;	
		}
		
		int pos = 0;
		int index = Index_2(*s, y, pos);
		
		
		// ��Ҫ�����滻�����������index + StrLength(x) > MAX_ELEM
		while(index>0 && (index + StrLength(x) <= s->length))
		{
				// �滻����
				int i=index;
				
				// ��ɾ��y
				StrDelete(s, index, StrLength(y));	
				
				// �ڲ���x
				if(!StrInsert(s, index, x))
				{
						cout << "StrInsert failed" << endl;
						break;
				}

				pos = index + StrLength(x);
				index = Index_2(*s, y, pos);
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
bool Concat(HString* ns, HString s1, HString s2)
{
		if(StrEmpty(s1) && StrEmpty(s2))
		{
				ns->length = 0;
				ns->data = NULL;
				return true;	
		}
		
		// �����ܵ����ݳ��ȣ������Ӧ���ȵ��ڴ�
		char* data = new char[s1.length + s2.length + 1];
		
		memset(data, 0, s1.length + s2.length + 1);
		
		// ����s1��s��
		if(!StrEmpty(s1))
		{
				ns->length = s1.length;
				memcpy(data, s1.data, s1.length);
		}	
		
		// ��s2ƴ�ӵ�s��
		if(!StrEmpty(s2))
		{
				memcpy(data + ns->length, s2.data, s2.length);
				ns->length += s2.length;	
		}
		
		ns->data = data;
		return true;
}

int main(int argc, char** argv)
{
		const char* chString = "Hello world world Workd!! world456";
		
		HString s;
		StrAssign(&s, chString);
		
		PrintString(s);
		
		StrDelete(&s, 2, 3);
		
		PrintString(s);
		
		HString si;
		StrAssign(&si, "test");
		StrInsert(&s, 2, si);
		cout << "After insert:" << endl;
		PrintString(s);
		
		HString s_copy;
		
		StrCopy(&s_copy, s);
		
		cout << "After copy:" << endl;
		PrintString(s_copy);
		
		cout << "StrCompare:" << StrCompare(s, s_copy) << endl;
		
		HString s2;
		StrAssign(&s2, "abcdefghijk");
		cout << "StrCompare:" << StrCompare(s_copy, s2) << endl;
		
		HString s3;
		StrAssign(&s3, "world");
		cout << "Index of world: " << Index_1(s, s3, 1) << endl;
		cout << "Index of world: " << Index_2(s, s3, 1) << endl;
		
		
		cout << "Test replace." << endl;
		Replace(&s, s2, s3);
		PrintString(s);
		
		cout << "Test Concat." << endl;
		HString s4;
		Concat(&s4, s, s3);
		PrintString(s4);
		
		ClearString(&s4);
		cout << "Test ClearString." << endl;
		PrintString(s4);
		return 0;
}