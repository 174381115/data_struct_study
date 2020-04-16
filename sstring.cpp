#include <iostream>
#include <sys/time.h>
#include <algorithm>
#include <cstdlib>
#include <cstring>

using namespace std;

#define MAX_ELEM 	255


/*
 * 串的顺序存储类型定义
 *
 * 注：有效元素从SString的1号单元开始存储
 *     SString的0号单元用来存储其长度
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


//构造一个值为chars的串dst。
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

// 清空字符串
void ClearString(SString s)
{
		s[0] = 0;
}

// 判断字符串是否为空
bool StrEmpty(SString s)
{
	 return s[0] == 0 ? true : false;
}

// 返回字符串的长度
int StrLength(SString s)
{
		return s[0];
}


//pos从1开始，返回长度为Len的子串
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

//从pos处开始搜索模式串T在主串S中首次出现的位置，如果不存在，则返回0。
//如果查找成功，返回匹配的位置。
int Index_1(SString s, SString sub, int pos)
{
		int i = pos;
		SString tmp;
		
		cout << s[0]-sub[0]+1 << endl;
		if(pos < 1 || pos > (s[0]-sub[0]+1) || StrEmpty(sub))
		{
				return -1;
		}
		
		//从位置1 - (m-n+1)开始比较子串是否相等
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

//从pos处开始搜索模式串T在主串S中首次出现的位置，如果不存在，则返回0。
//如果查找成功，返回匹配的位置。
int Index_2(SString s, SString sub, int pos)
{
		if(pos < 1 || pos > (s[0]-sub[0]+1) || StrEmpty(sub))
		{
				return -1;
		}
		
		int i = pos;
		int j = 1;
		
		// 长度范围判断		
		while(i <= s[0] && j <= sub[0])
		{
				// 如果两个字符相等，则继续比较下一个字符
				if(s[i] == sub[j])
				{
						i++;
						j++;
				}
				else
				{
						// 如果发现有字符不相等，则回退到上次匹配首位的下一个字符
						i = i-j+2;
						j = 1;
				}	
		}
		
		// 如果j超过子串的长度，说明整个子字符串都匹配成功了
		if(j > sub[0])
		{
				return i - sub[0];
		}
		
		return -1;
}

//将串sub插入到主串S的pos位置处。
bool StrInsert(SString s, int pos, SString sub)
{
		if(s[0] + sub[0] > MAX_ELEM || pos < 1)
		{
				return false;
		}
		
		// 插入的为空串
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

// * 删除S[pos, pos+len-1]。
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
		
		
		// 将删除串之后的字符串向前移动
		for(int i=pos+len; i<=s[0]; i++)
		{
				s[i-len] = s[i];	
		}
		
		// 更新串的长度
		s[0] -= len;
		return true;
}

//将串src复制到串dst。
bool StrCopy(SString dst, SString src)
{
		dst[0] = src[0];
		
		memcpy(dst+1, src+1, src[0]);
		return false;
}

//比较串S和串T，返回比较结果
int StrCompare(SString s1, SString s2)
{
		int i=1;
		
		// 比较最短长度个字符，如果有一个字符不相等，则比较
		// 参见字符串不想等的定义
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


//用x替换主串s中出现的所有与y相等的且不重叠的子串。
bool Replace(SString s, SString x, SString y)
{
		if(StrEmpty(y))
		{
				return false;	
		}
		
		int pos = 1;
		int index = Index_2(s, y, pos);
		
		
		// 需要考虑替换后溢出的问题index + StrLength(x) > MAX_ELEM
		while(index>0 && (index + StrLength(x) <= MAX_ELEM))
		{
				// 替换内容
				int i=index;
				int j = 1;
		/*		for(; j<=StrLength(x); i++, j++)
				{
						s[i] = x[j];
				} */
				
				// 先删除y
				StrDelete(s, index, StrLength(y));	
				
				// 在插入x
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


// 联接S1和S2，并存储到T中返回。如果联接后的长度溢出，则只保留未溢出的部分。
// 返回值表示联接后的串是否完整。
bool Concat(SString ns, SString s1, SString s2)
{
		int is2_len = 0;
		
		StrCopy(ns, s1);
		
		// 计算还能插入的数据长度
		is2_len = MAX_ELEM - StrLength(s1);
		
		if(is2_len > 0)
		{
				// 插入剩下的字符
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