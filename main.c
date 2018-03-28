#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct bigNum
{
	long num_of_digits;
	char *digits;
} BigNum;

typedef struct Link
{
	BigNum num;
	struct Link *next;
} LinkedList;

extern char *addition(BigNum *, BigNum *);

extern char *substraction(BigNum *, BigNum *);

extern char *multipliaction(BigNum *, BigNum *);

extern char *division(BigNum *, BigNum *);

char *increase(char *string, size_t *size)
{
	char *temp=(char *)malloc((*size+=10)*sizeof(char));
	if (!temp)
	{
		puts("calc: not enough ram!!!");
		exit(-1);
	}
	strcpy(temp, string);
	free(string);
	return temp;
}

void clear(LinkedList *stackHead)
{
	if (!stackHead)
		return;
	clear(stackHead->next);
	free(stackHead->num.digits);
	free(stackHead);
}

int main()
{
	LinkedList *stackHead=NULL;
	char ch;
	size_t size=10;
	long tempSize=0;
	char *tempString=(char *)malloc(sizeof(char)*10);
	if (!tempString)
	{
		puts("calc: not enough ram!!!");
		exit(-1);
	}
	while (EOF!=(ch=(char)fgetc(stdin)))
	{
		tempString[tempSize++]=ch;
		if (tempSize==size)
			tempString=increase(tempString, &size);
		if (strcmp(tempString, "+")==0 && stackHead && stackHead->next)
		{
//			addition();
			continue;
		}
		if (strcmp(tempString, "-")==0 && stackHead && stackHead->next)
		{
//			substraction();
			continue;
		}
		if (strcmp(tempString, "*")==0 && stackHead && stackHead->next)
		{
//			multipliaction();
			continue;
		}
		if (strcmp(tempString, "/")==0 && stackHead && stackHead->next)
		{
//			division();
			continue;
		}
		if (strcmp(tempString, "p")==0)
		{
			puts(stackHead ? stackHead->num.digits : "calc: stack empty");
			continue;
		}
		if (strcmp(tempString, "q")==0)
			exit(1);
		if (strcmp(tempString, "c")==0)
		{
			clear(stackHead);
			stackHead=NULL;
			continue;
		}
		if (ch=='\n')
		{
			LinkedList *tempLink=(LinkedList *)malloc(sizeof(LinkedList));
			if (!tempLink)
			{
				puts("calc: not enough ram!!!");
				exit(-1);
			}
			tempString[tempSize-1]='\0';
			tempLink->num.digits=tempString;
			tempString=(char *)malloc(sizeof(char)*10);
			if (!tempString)
			{
				puts("calc: not enough ram!!!");
				exit(-1);
			}
			size=10;
			tempLink->num.num_of_digits=tempSize-1;
			tempSize=0;
			tempLink->next=stackHead;
			stackHead=tempLink;
			continue;
		}
		puts("calc: stack empty");
	}
	return 0;
}
