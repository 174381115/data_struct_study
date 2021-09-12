#include <iostream>
#include <sys/time.h>
#include <algorithm>
#include <cstdlib>
#include <cstring>

using namespace std;  //test


/*
 * 串的顺序存储类型定义
 *
 */
struct HString
{
		char* data;			// 存储字符串的内存
		int length;			// 实际字符串的长度
};

int StrCompare(HString s1, HString s2);

// 打印堆串
void PrintString(HString s)
{
		for(int i=0; i<s.length; i++)
		{
			cout << s.data[i];
		}
		
		cout << endl;
}


//构造一个值为chars的串dst。
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

// 清空字符串
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

// 判断字符串是否为空
bool StrEmpty(HString s)
{
	 return s.length == 0 ? true : false;
}

// 返回字符串的长度
int StrLength(HString s)
{
		return s.length;
}


//pos从0开始，返回长度为Len的子串
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

//从pos处开始搜索模式串T在主串S中首次出现的位置，如果不存在，则返回0。
//如果查找成功，返回匹配的位置。
int Index_1(HString s, HString sub, int pos)
{
		int i = pos;
		HString tmp;
		
		if(pos < 0 || pos > (s.length-sub.length+1) || StrEmpty(sub))
		{
				return -1;
		}
		
		//从位置1 - (m-n+1)开始比较子串是否相等
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

//从pos处开始搜索模式串T在主串S中首次出现的位置，如果不存在，则返回0。
//如果查找成功，返回匹配的位置。
int Index_2(HString s, HString sub, int pos)
{
		if(pos < 0 || pos > (s.length-sub.length+1) || StrEmpty(sub))
		{
				return -1;
		}
		
		int i = pos;
		int j = 0;
		
		// 长度范围判断		
		while(i < s.length && j < sub.length)
		{
				// 如果两个字符相等，则继续比较下一个字符
				if(s.data[i] == sub.data[j])
				{
						i++;
						j++;
				}
				else
				{
						// 如果发现有字符不相等，则回退到上次匹配首位的下一个字符
						i = i-j+1;
						j = 0;
				}	
		}
		
		// 如果j超过子串的长度，说明整个子字符串都匹配成功了
		if(j >= sub.length)
		{
				return i - sub.length;
		}
		
		return -1;
}

//将串sub插入到主串S的pos位置处。
bool StrInsert(HString* s, int pos, HString sub)
{
		if(pos < 0)
		{
				return false;
		}
		
		// 插入的为空串
		if(sub.length == 0)
		{
				return true;
		}
		
		//重新分配内存
		char *nd = new char[s->length+sub.length+1];
		
		memset(nd, 0, s->length+sub.length+1);
		
		// 复制pos之前的数据
		memcpy(nd, s->data, pos);
		
		// 复制要插入的子串
		memcpy(nd+pos, sub.data, sub.length);
		
		// 复制s中pos之后的子串
		memcpy(nd+pos+sub.length, s->data+pos, s->length - pos);
		
		s->length += sub.length;
		delete[] s->data;
		
		s->data = nd;
		return true;
}

// * 删除S[pos, pos+len-1]。
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
		
		
		// 将删除串之后的字符串向前移动
		for(int i=pos+len; i<=s->length; i++)
		{
				s->data[i-len] = s->data[i];	
		}
		
		// 更新串的长度
		s->length -= len;
		return true;
}

//将串src复制到串dst。
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

//比较串S和串T，返回比较结果
int StrCompare(HString s1, HString s2)
{
		int i=0;
		
		// 比较最短长度个字符，如果有一个字符不相等，则比较
		// 参见字符串不想等的定义
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


//用x替换主串s中出现的所有与y相等的且不重叠的子串。
bool Replace(HString* s, HString x, HString y)
{
		if(StrEmpty(y))
		{
				return false;	
		}
		
		int pos = 0;
		int index = Index_2(*s, y, pos);
		
		
		// 需要考虑替换后溢出的问题index + StrLength(x) > MAX_ELEM
		while(index>0 && (index + StrLength(x) <= s->length))
		{
				// 替换内容
				int i=index;
				
				// 先删除y
				StrDelete(s, index, StrLength(y));	
				
				// 在插入x
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


// 联接S1和S2，并存储到T中返回。如果联接后的长度溢出，则只保留未溢出的部分。
// 返回值表示联接后的串是否完整。
bool Concat(HString* ns, HString s1, HString s2)
{
		if(StrEmpty(s1) && StrEmpty(s2))
		{
				ns->length = 0;
				ns->data = NULL;
				return true;	
		}
		
		// 根据总的数据长度，分配对应长度的内存
		char* data = new char[s1.length + s2.length + 1];
		
		memset(data, 0, s1.length + s2.length + 1);
		
		// 拷贝s1到s中
		if(!StrEmpty(s1))
		{
				ns->length = s1.length;
				memcpy(data, s1.data, s1.length);
		}	
		
		// 将s2拼接到s中
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