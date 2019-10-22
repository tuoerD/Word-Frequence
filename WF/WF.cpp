
#include<iostream>
#include<fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<algorithm>
#include<vector>
#include<map>
#include<ctype.h>
#include<conio.h>

//int main()
//{
//	FILE *fp;
//	int i;
//	fp = fopen("test.txt", "r");
//	if (fp != NULL)
//	{
//		while (!feof(fp))
//		{
//			fscanf(fp, "%d", &i);
//			printf("%d", i);
//		}
//	}
//	else
//	{
//		printf("empty file!");
//	}
//}
#define word_line 1000 

int CountL[26];//存储字母出现的次数 
char dif_word[word_line];//存储不重复的单词
 
int CheckL(char c)//判断字符是否为字母 
{
    int index;
    char i, j;
    int flag = 0;
 
    for(i = 'A', j = 'a'; i <= 'Z', j <= 'z'; i++, j++)
    {
        if(i == c)
        {
            CountL[i - 65]++;
            flag = 1;
            break;
        }
        if(j == c)
        {
            CountL[j - 97]++;
            flag = 1;
            break;
        }
    }
 
    return flag;
}
 
long LetterScan(char *filepath)
{
    FILE *fp;
    fp = fopen(filepath, "r");
    long AllCount = 0;//存储字母个数 
    char c;
 
    if(fp == NULL)
    {
        perror("Can't open!");
        exit(1);
    }
 
    while(!feof(fp))
    {
        c = fgetc(fp);
        if(CheckL(c))//返回的flag值为1则计入AllCount 
        {
            AllCount++;
        }
    }
 
    fclose(fp);
    return AllCount;
}
 
char *SortL()
{
    int i, j, t;
    char c;
    char *Letter;
 
    Letter = (char *)calloc(26, sizeof(char));
 
    for(i = 0; i < 26; i++)
    {
        Letter[i] = i + 97;
    }
 
    for(i = 0; i < 25; i++)
    {
        for(j = 0; j < 25 - i; j++)
        {
            if(CountL[j] < CountL[j + 1])
            {
                t = CountL[j];
                c = Letter[j];
                CountL[j] = CountL[j + 1];
                Letter[j] = Letter[j + 1];
                CountL[j + 1] = t;
                Letter[j + 1] = c;
            }
        }
    }
 
    return Letter;
}



int main()
{
    char *FilePath = "test.txt";
    int i;
    long count = 0;
    char *Letter;
 
    Letter = (char *)calloc(26, sizeof(char));
    system("rm -rf doc/test.txt");
    system("cat doc/*txt > doc/test.txt");
 
    count = LetterScan(FilePath);
    Letter = SortL();
 
    printf("测试文本包含有效英文字母总数：%ld\n", count);
    for(i = 0; i < 26; i++)
    {
        printf("%c共出现%d次，概率是%.2f%%\n", Letter[i], CountL[i], (float)CountL[i] / count);
    }
    free(Letter);
    
    
    
    return 0;
}

