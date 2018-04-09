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

extern void divisionBy2(char *);

int strcmp1(const char * __s1, const char * __s2)
{
	if (strlen(__s1)<strlen(__s2))
		return -1;
	if (strlen(__s1)==strlen(__s2))
		return strcmp(__s1, __s2);
	return 1;
}

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

char *multiC(char *c1, char *c2)
{
	char *sum=malloc(sizeof(char)*2);
	checkMalloc(sum);
	sum[0]='0';
	sum[1]='\0';
	while (1)
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
			if (strcmp1(c1, "1")==0)
				return sum;
			c1[strlen(c1)-1]--;
		}
		char *temp2=(char *)(malloc(sizeof(char)*(strlen(c1)+2)));
		checkMalloc(temp2);
		addition(c2, c2, temp2);
		free(c2);
		c2=reverseStr(temp2);
		divisionBy2(c1);
		reverseStr(trim0(reverseStr(c1)));
	}
}

void divCHepler(char *first, char *second, char *result, char *factor)
{
	if (strcmp1(first, second)<0)
	{
//		divisionBy2(second);
//		reverseStr(trim0(reverseStr(second)));
//		divisionBy2(factor);
//		reverseStr(trim0(reverseStr(factor)));
		return;
	}
	char *temp=(char *)(malloc(sizeof(char)*(strlen(factor)+2)));
	checkMalloc(temp);
	addition(factor, factor, temp);
	factor=reverseStr(temp);
	
	temp=(char *)(malloc(sizeof(char)*(strlen(second)+2)));
	checkMalloc(temp);
	addition(second, second, temp);
	second=reverseStr(temp);
	
	divCHepler(first, second, result, factor);
	
	divisionBy2(second);
	reverseStr(trim0(reverseStr(second)));
	divisionBy2(factor);
	reverseStr(trim0(reverseStr(factor)));
	if (strcmp1(first, second)>=0)
	{
		temp=(char *)(malloc(sizeof(char)*(strlen(second)+1)));
		checkMalloc(temp);
		substraction(first, second, temp);
		strcpy(first, reverseStr(trim0(temp)));
		free(temp);
		
		temp=(char *)(malloc(sizeof(char)*(strlen(second)+strlen(factor)+1)));
		checkMalloc(temp);
		addition(strlen(result)>strlen(factor) ? result : factor,
		         strlen(result)<=strlen(factor) ? result : factor,
		         temp);
		strcpy(result, reverseStr(temp));
		free(temp);
	}
	
	free(second);
	free(factor);
}

char *divC(char *first, char *second)
{
	char *result=(char *)malloc(sizeof(char)*(strlen(first)+1));
	checkMalloc(result);
	sprintf(result, "0");
	char *factor=(char *)malloc(sizeof(char)*2);
	checkMalloc(factor);
	sprintf(factor, "1");
	divCHepler(first, second, result, factor);
	if (strcmp1(first, second)>=0)
	{
		char *temp=(char *)(malloc(sizeof(char)*(strlen(second)+1)));
		checkMalloc(temp);
		substraction(first, second, temp);
		strcpy(first, reverseStr(trim0(temp)));
		free(temp);
		
		temp=(char *)(malloc(sizeof(char)*(strlen(second)+strlen(factor)+1)));
		checkMalloc(temp);
		addition(result, factor, temp);
		strcpy(result, reverseStr(temp));
		free(temp);
	}
	free(factor);
	return result;
}

size_t MIN(size_t a, size_t b)
{
	return a<b ? a : b;
}

char *increase(char *string, size_t *size)
{
	char *temp=(char *)malloc((*size+=10)*sizeof(char));
	checkMalloc(temp);
	for (int i=0; i<*size; ++i)
		temp[i]='\0';
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

char *newTempString(long *tempSize, size_t *size)
{
	char *temp=(char *)malloc(sizeof(char)*10);
	checkMalloc(temp);
	for (int i=0; i<10; ++i)
		temp[i]='\0';
	*tempSize=0;
	*size=10;
	return temp;
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
		if (strcmp1(tempString, "+")==0 && stackHead && stackHead->next)
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
			tempString=newTempString(&tempSize, &size);
			push(result);
			continue;
		}
		if (strcmp1(tempString, "-")==0 && stackHead && stackHead->next)
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
			tempString=newTempString(&tempSize, &size);
			push(reverseStr(trim0(result)));
			continue;
		}
		if (strcmp1(tempString, "*")==0 && stackHead && stackHead->next)
		{
//			multipliaction();
			size_t maxsize=MAX(strlen(stackHead->num.digits), strlen(stackHead->next->num.digits));
			
			char *res=multiC(maxsize==strlen(stackHead->num.digits) ?
			                 stackHead->num.digits :
			                 stackHead->next->num.digits,
			                 maxsize!=strlen(stackHead->num.digits) ?
			                 stackHead->num.digits :
			                 stackHead->next->num.digits);
			clear(pop());
			clear(pop());
			tempString=newTempString(&tempSize, &size);
			push(res);
			continue;
		}
		if (strcmp1(tempString, "/")==0 && stackHead && stackHead->next)
		{
//			division();
			char *res=divC(stackHead->next->num.digits, stackHead->num.digits);
			clear(pop());
			clear(pop());
			tempString=newTempString(&tempSize, &size);
			push(res);
			continue;
		}
		if (strcmp1(tempString, "p")==0)
		{
			puts(stackHead ? stackHead->num.digits : "calc: stack empty");
			continue;
		}
		if (strcmp1(tempString, "q")==0)
			exit(1);
		if (strcmp1(tempString, "c")==0)
		{
			clear(stackHead);
			stackHead=NULL;
			continue;
		}
		if (ch=='\n')
		{
			if (strcmp(tempString, "!")<0)
			{
				tempString[0]='\0';
				tempSize=0;
				continue;
			}
			LinkedList *tempLink=(LinkedList *)malloc(sizeof(LinkedList));
			checkMalloc(tempLink);
			tempString[tempSize-1]='\0';
			tempLink->num.digits=tempString;
			tempString=newTempString(&tempSize, &size);
			tempLink->next=stackHead;
			stackHead=tempLink;
			continue;
		}
		//puts("calc: stack empty");
	}
	return 0;
}