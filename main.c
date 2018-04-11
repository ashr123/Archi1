#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct bigNum
{
	char sign;
	char *digits;
} BigNum;

typedef struct Link
{
	BigNum num;
	struct Link *next;
} LinkedList;

static LinkedList *stackHead=NULL;

extern void addition(char *, char *, char *);

extern void substraction(char *, char *, char *);

extern void divisionBy2(char *);

static int strcmp1(const char *__s1, const char *__s2)
{
	const size_t len1=strlen(__s1), len2=strlen(__s2);
	if (len1<len2)
		return -1;
	if (len1==len2)
		return strcmp(__s1, __s2);
	return 1;
}

static void checkMalloc(void *toCheck)
{
	if (!toCheck)
	{
		puts("calc: not enough ram!!!");
		exit(-1);
	}
}

static size_t MAX(size_t a, size_t b)
{
	return a>b ? a : b;
}

static char *reverseStr(char *str)
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

static char *trim0(char *str)
{
	while (strlen(str)!=1 && str[strlen(str)-1]=='0')
		str[strlen(str)-1]='\0';
	return str;
}

static char *multiC(char *c1, char *c2)
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

static void divCHepler(char *first, char *second, char *result, char *factor)
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

static char *divC(char *first, char *second)
{
	if (strcmp(second, "0")==0)
	{
		puts("calc: divide by zero");
		return NULL;
	}
	char *result=(char *)malloc(sizeof(char)*(strlen(first)+1));
	checkMalloc(result);
	sprintf(result, "0");
	if (strcmp1(first, second)<0)
		return result;
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

static char *increase(char *string, size_t *size)
{
	char *temp=(char *)malloc((*size+=10)*sizeof(char));
	checkMalloc(temp);
	for (int i=0; i<*size; ++i)
		temp[i]='\0';
	strcpy(temp, string);
	free(string);
	return temp;
}

static void clear(LinkedList *stackHead)
{
	if (!stackHead)
		return;
	clear(stackHead->next);
	if (!stackHead->num.digits)
		free(stackHead->num.digits);
	free(stackHead);
}

static LinkedList *pop()
{
	LinkedList *out=stackHead;
	stackHead=stackHead->next;
	out->next=NULL;
	return out;
}

static void push(char *tempString)
{
	reverseStr(trim0(reverseStr(tempString)));
	LinkedList *tempLink=(LinkedList *)malloc(sizeof(LinkedList));
	checkMalloc(tempLink);
	tempLink->num.digits=tempString;
	tempLink->num.sign='\0';
	if (tempString[0]=='_')
	{
		strcpy(tempString, tempString+1);
		reverseStr(trim0(reverseStr(tempString)));
		if (tempString[0]!='0')
			tempLink->num.sign='-';
	}
	tempLink->next=stackHead;
	stackHead=tempLink;
}

static char *newTempString(long *tempSize, size_t *size)
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
//	int i=0;
	char ch;
	size_t size=10;
	long tempSize=0;
	char *tempString=(char *)malloc(sizeof(char)*10), *result;
	checkMalloc(tempString);
	while (EOF!=(ch=(char)fgetc(stdin)))
	{
//		i++;
//		printf("%d\n",i);
		tempString[tempSize++]=ch;
		if (tempSize==size)
			tempString=increase(tempString, &size);
		if (strcmp1(tempString, "+")==0 && stackHead && stackHead->next)
		{
			if ((stackHead->num.sign=='-') && (stackHead->next->num.sign=='-'))
				//If first is negative and second is negative
			{
				//Addition();
				size_t maxsize=MAX(strlen(stackHead->num.digits), strlen(stackHead->next->num.digits));
				result=(char *)malloc(sizeof(char)*(maxsize+2));
				checkMalloc(result);
				addition(strcmp1(stackHead->num.digits, stackHead->next->num.digits)>0 ?
				         stackHead->num.digits :
				         stackHead->next->num.digits,
				         strcmp1(stackHead->num.digits, stackHead->next->num.digits)<=0 ?
				         stackHead->num.digits :
				         stackHead->next->num.digits,
				         result);
				clear(pop());
				clear(pop());
				tempString=newTempString(&tempSize, &size);
				push(reverseStr(result));
				stackHead->num.sign='-';
				continue;
			}
			else
				if (((stackHead->num.sign=='-') && (stackHead->next->num.sign=='\0'))
				    || ((stackHead->num.sign=='\0') && (stackHead->next->num.sign=='-')))
				{
					//If Just one of them is negative and the second is positive
					//If first is bigger or equal to second
					size_t maxsize=MAX(strlen(stackHead->num.digits), strlen(stackHead->next->num.digits));
					result=(char *)malloc(sizeof(char)*(maxsize+2));
					checkMalloc(result);
					substraction(strcmp1(stackHead->num.digits, stackHead->next->num.digits)>0 ?
					             stackHead->num.digits :
					             stackHead->next->num.digits,
					             strcmp1(stackHead->num.digits, stackHead->next->num.digits)<=0 ?
					             stackHead->num.digits :
					             stackHead->next->num.digits,
					             result);
					const char sign=(const char)((strcmp1(stackHead->next->num.digits, stackHead->num.digits)>0 &&
					                              stackHead->next->num.sign) ||
					                             (strcmp1(stackHead->next->num.digits, stackHead->num.digits)<0 &&
					                              stackHead->num.sign) ?
					                             '-' :
					                             '\0');
					clear(pop());
					clear(pop());
					tempString=newTempString(&tempSize, &size);
					push(reverseStr(trim0(result)));
					stackHead->num.sign=sign;
				}
				else
				{
					size_t maxsize=MAX(strlen(stackHead->num.digits), strlen(stackHead->next->num.digits));
					result=(char *)malloc(sizeof(char)*(maxsize+2));
					checkMalloc(result);
					addition(strcmp1(stackHead->num.digits, stackHead->next->num.digits)>0 ?
					         stackHead->num.digits :
					         stackHead->next->num.digits,
					         strcmp1(stackHead->num.digits, stackHead->next->num.digits)<=0 ?
					         stackHead->num.digits :
					         stackHead->next->num.digits,
					         result);
					clear(pop());
					clear(pop());
					tempString=newTempString(&tempSize, &size);
					push(reverseStr(trim0(result)));
				}
		}
		if (strcmp1(tempString, "-")==0 && stackHead && stackHead->next)
		{
			//substraction();
//			size_t maxsize=MAX(strlen(stackHead->num.digits), strlen(stackHead->next->num.digits));
			result=(char *)malloc(
					sizeof(char)*(MAX(strlen(stackHead->num.digits), strlen(stackHead->next->num.digits))+1));
			checkMalloc(result);
			if (stackHead->num.sign && !stackHead->next->num.sign)
			{
				addition(strcmp1(stackHead->num.digits, stackHead->next->num.digits)>0 ?
				         stackHead->num.digits :
				         stackHead->next->num.digits,
				         strcmp1(stackHead->num.digits, stackHead->next->num.digits)<=0 ?
				         stackHead->num.digits :
				         stackHead->next->num.digits,
				         result);
				clear(pop());
				clear(pop());
				push(reverseStr(result));
			}
			else
				if (!stackHead->num.sign && stackHead->next->num.sign)
				{
					addition(strcmp1(stackHead->num.digits, stackHead->next->num.digits)>0 ?
					         stackHead->num.digits :
					         stackHead->next->num.digits,
					         strcmp1(stackHead->num.digits, stackHead->next->num.digits)<=0 ?
					         stackHead->num.digits :
					         stackHead->next->num.digits,
					         result);
					clear(pop());
					clear(pop());
					push(reverseStr(result));
					stackHead->num.sign='-';
				}
				else
					if (!stackHead->num.sign && stackHead->next->num.sign)
					{
						substraction(strcmp1(stackHead->num.digits, stackHead->next->num.digits)>0 ?
						             stackHead->num.digits :
						             stackHead->next->num.digits,
						             strcmp1(stackHead->num.digits, stackHead->next->num.digits)<=0 ?
						             stackHead->num.digits :
						             stackHead->next->num.digits,
						             result);
						clear(pop());
						clear(pop());
						push(reverseStr(trim0(result)));
						stackHead->num.sign='-';
					}
					else
					{
						substraction(strcmp1(stackHead->num.digits, stackHead->next->num.digits)>0 ?
						             stackHead->num.digits :
						             stackHead->next->num.digits,
						             strcmp1(stackHead->num.digits, stackHead->next->num.digits)<=0 ?
						             stackHead->num.digits :
						             stackHead->next->num.digits,
						             result);
						const char sign=(const char)(strcmp1(stackHead->next->num.digits,
						                                     stackHead->num.digits)>0 ?
						                             '-' :
						                             '\0');
						clear(pop());
						clear(pop());
						push(reverseStr(trim0(result)));
						stackHead->num.sign=sign;
					}
			
			tempString=newTempString(&tempSize, &size);
			continue;
		}
		
		if (strcmp1(tempString, "*")==0 && stackHead && stackHead->next)
		{
			if (((stackHead->num.sign=='-') && (stackHead->next->num.sign=='-')) ||
			    ((stackHead->num.sign=='\0') && (stackHead->next->num.sign=='\0')))
			{
				//if Both of them are negative or both of them are positive
//				multiplication();
				
				char *res=multiC(strcmp1(stackHead->num.digits, stackHead->next->num.digits)>0 ?
				                 stackHead->num.digits :
				                 stackHead->next->num.digits,
				                 strcmp1(stackHead->num.digits, stackHead->next->num.digits)<=0 ?
				                 stackHead->num.digits :
				                 stackHead->next->num.digits);
//				char *res2=(char *)malloc(sizeof(char)*(strlen(res)+1));
//				checkMalloc(res2);
//				strcpy(res2, res);
//				free(res);
				stackHead->num.digits=stackHead->next->num.digits=NULL;
				clear(pop());
				clear(pop());
				tempString=newTempString(&tempSize, &size);
				push(res);
				continue;
			}
			else
			{
				//One of them is negative anf the second is positive
				
				char *res=multiC(strcmp1(stackHead->num.digits, stackHead->next->num.digits)>0 ?
				                 stackHead->num.digits :
				                 stackHead->next->num.digits,
				                 strcmp1(stackHead->num.digits, stackHead->next->num.digits)<=0 ?
				                 stackHead->num.digits :
				                 stackHead->next->num.digits);
				stackHead->num.digits=stackHead->next->num.digits=NULL;
				clear(pop());
				clear(pop());
				tempString=newTempString(&tempSize, &size);
				push(res);
				stackHead->num.sign='-';
				continue;
			}
		}
		
		if (strcmp1(tempString, "/")==0 && stackHead && stackHead->next)
		{
//			division();
			char *res=divC(stackHead->next->num.digits, stackHead->num.digits);
			if (res)
			{
				const char sign=(const char)(stackHead->next->num.sign!=stackHead->num.sign ? '-' : '\0');
				stackHead->num.digits=stackHead->next->num.digits=NULL;
				clear(pop());
				clear(pop());
				push(res);
				stackHead->num.sign=sign;
			}
			tempString=newTempString(&tempSize, &size);
			continue;
		}
		if (strcmp1(tempString, "p")==0)
		{
			stackHead ? printf("%c%s\n", stackHead->num.sign, stackHead->num.digits) :
			puts("calc: stack empty");
			tempString=newTempString(&tempSize, &size);
			continue;
		}
		if (strcmp1(tempString, "q")==0)
		{
			clear(stackHead);
			exit(1);
		}
		if (strcmp1(tempString, "c")==0)
		{
			clear(stackHead);
			stackHead=NULL;
			tempString=newTempString(&tempSize, &size);
			continue;
		}
		if (ch<'!')
		{
			if (strcmp(tempString, "!")<0)
			{
				tempString[0]='\0';
				tempSize=0;
				continue;
			}
			tempString[tempSize-1]='\0';
			push(tempString);
			tempString=newTempString(&tempSize, &size);
			continue;
		}
		//puts("calc: stack empty");
	}
	return 0;
}