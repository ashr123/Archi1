#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct bigNum
{
	//char sign;
	char *digits;
} BigNum;

typedef struct Link
{
	BigNum num;
	struct Link *next;
} LinkedList;

LinkedList *stackHead=NULL;

extern void addition(char *, char *, char *);

extern void substraction(char *, char *, char *);

extern void multipliaction(char *, char *, char *);

extern void division(char *, char *, char *);

char* multiC(char *c1, char *c2);

void checkMalloc(void *toCheck)
{
	if (!toCheck)
	{
		puts("calc: not enough ram!!!");
		exit(-1);
	}
}

size_t MAX(size_t a, size_t b)
{
	return a>b ? a : b;
}

char *reverseStr(char *str)
{
	size_t n=strlen(str);
	
	// Swap character starting from two
	// corners
	for (int i=0; i<n/2; i++)
	{
		char temp=str[i];
		str[i]=str[n-i-1];
		str[n-i-1]=temp;
	}
	return str;
}

char *trim0(char *str)
{
	while (strlen(str)!=0 && str[strlen(str)-1]=='0')
		str[strlen(str)-1]='\0';
	return str;
}

void divC(char *first, char *second, char *factor, char *sum, char **temp)
{
	if (strcmp(first, second)<0)
	{
		temp[0]=first;
		temp[1]=sum;
		return;
	}
	divC(first, multiC(second, "2"), multiC(factor, "2"), sum, temp);
	if (temp[0]!=first)
	{
		free(first);
		first=temp[0];
		free(sum);
		sum=temp[1];
	}
	if (strcmp(first,second)>=0)
	{
		char *result=(char *)malloc(sizeof(char)*(strlen(sum)+2));
		addition(factor, sum, result);
		free(sum);
		sum=reverseStr(result);
		
		result = (char *)malloc(sizeof(char)*(strlen(sum)+1));
		substraction(first,second,result);
		reverseStr(trim0(result));
	}
	temp[0]=first;
	temp[1]=sum;
}

char* multiC(char *c1, char *c2)
{
	char *sum = malloc(sizeof(char)*2);
	checkMalloc(sum);
	sum[0]='0';
	sum[1]='\0';
	while(strcmp(c1, "1")!=0)
	{
		char firstDigit=c1[strlen(c1)-1];
		if (firstDigit=='1' || firstDigit=='3' || firstDigit=='5' || firstDigit=='7' || firstDigit=='9')
		{
			size_t maxsize=MAX(strlen(sum), strlen(c2));
			char *temp=(char *)malloc(sizeof(char)*(strlen(maxsize==strlen(sum) ? sum : c2)+2));
			checkMalloc(temp);
			addition(maxsize==strlen(sum) ? sum : c2,
			         maxsize!=strlen(sum) ? sum : c2,
			         temp);
			free(sum);
			sum=reverseStr(temp);
			c1[strlen(c1)-1]--;
		}
		char *temp, *temp2=(char *)(malloc(sizeof(char)*(strlen(c1)+2)));
		checkMalloc(temp2);
		addition(c2, c2, temp2);
		free(c2);
		c2=temp2;
		temp=divC(c1, "2", 1, );
		free(c1);
		c1=temp;
		if (strcmp(c1, "1")==0)
			return sum;
	}
	return c1;
}

size_t MIN(size_t a, size_t b)
{
	return a<b ? a : b;
}

char *increase(char *string, size_t *size)
{
	char *temp=(char *)malloc((*size+=10)*sizeof(char));
	checkMalloc(temp);
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

LinkedList *pop()
{
	LinkedList *out=stackHead;
	stackHead=stackHead->next;
	out->next=NULL;
	return out;
}

void push(char *tempString)
{
	LinkedList *tempLink=(LinkedList *)malloc(sizeof(LinkedList));
	checkMalloc(tempLink);
	tempLink->num.digits=tempString;
	tempLink->next=stackHead;
	stackHead=tempLink;
}

int main()
{
	char ch;
	size_t size=10;
	long tempSize=0;
	char *tempString=(char *)malloc(sizeof(char)*10), *result;
	checkMalloc(tempString);
	while (EOF!=(ch=(char)fgetc(stdin)))
	{
		tempString[tempSize++]=ch;
		if (tempSize==size)
			tempString=increase(tempString, &size);
		if (strcmp(tempString, "+")==0 && stackHead && stackHead->next)
		{
			//Addition();
			size_t maxsize=MAX(strlen(stackHead->num.digits), strlen(stackHead->next->num.digits));
			result=(char *)malloc(sizeof(char)*(maxsize+2));
			addition(maxsize==strlen(stackHead->num.digits) ?
			         stackHead->num.digits :
			         stackHead->next->num.digits,
			         maxsize!=strlen(stackHead->num.digits) ?
			         stackHead->num.digits :
			         stackHead->next->num.digits,
			         result);
			clear(pop());
			clear(pop());
			puts(reverseStr(result));
			push(result);
			continue;
		}
		if (strcmp(tempString, "-")==0 && stackHead && stackHead->next)
		{
			//substraction();
			size_t maxsize=MAX(strlen(stackHead->num.digits), strlen(stackHead->next->num.digits));
			result=(char *)malloc(sizeof(char)*(maxsize+1));
			substraction(maxsize==strlen(stackHead->num.digits) ?
			         stackHead->num.digits :
			         stackHead->next->num.digits,
			         maxsize!=strlen(stackHead->num.digits) ?
			         stackHead->num.digits :
			         stackHead->next->num.digits,
			         result);
			clear(pop());
			clear(pop());
			puts(reverseStr(trim0(result)));
			push(result);
			continue;
		}
		if (strcmp(tempString, "*")==0 && stackHead && stackHead->next)
		{
//			multipliaction();
			char *res = multiC(*c1,*c2);
			
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
			checkMalloc(tempLink)
			tempString[tempSize-1]='\0';
			tempLink->num.digits=tempString;
			tempString=(char *)malloc(sizeof(char)*10);
			checkMalloc(tempString);
			size=10;
//			tempLink->num.num_of_digits=tempSize-1;
			tempSize=0;
			tempLink->next=stackHead;
			stackHead=tempLink;
			continue;
		}
		//puts("calc: stack empty");
	}
	return 0;
}