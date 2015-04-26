#include "MySupportFuncs.h"
#include<math.h>

int getWeishu(int num)
{
	if (num == 0)
		return 1;
	return (int)log10(num + 0.0) + 1;
}

char* getNum(int num)
{
	int weishu = getWeishu(num);
	char* result = new char[weishu + 1];
	result[weishu] = '\0';
	for (int i = weishu; i >= 1; i--)
	{
		int yushu = (int)(pow(10.0, i - 1));
		char c = ((num - (num%yushu)) / yushu) + 48;
		num -= ((int)(num / yushu)*yushu);
		result[weishu - i] = c;
	}
	return result;
}



char* add_char_string(char*a, char* b, int a_len, int b_len)
{
	int len = a_len + b_len + 1;
	char* result = new char[len];
	result[len - 1] = '\0';
	for (int i = 0; i < a_len; i++)
	{
		result[i] = a[i];
	}
	for (int i = 0; i < b_len; i++)
	{
		result[i + a_len] = b[i];
	}
	return result;
}