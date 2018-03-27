#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

extern char *addition(char *, char *);
extern char *substraction(char *, char*);
extern char *multipliaction(char*, char*);
extern char *division(char*, char*);

typedef struct
{
	long num_of_digits;
	char *digits;
} BigNum;

typedef struct Link
{
	BigNum num;
	struct Link *next;
} LinkedList;

void increase(LinkedList *stackHead, size_t *size)
{
	char *temp=(char *) malloc((*size+=10)*sizeof(char));
	if (!temp)
	{
		puts("Not enough ram!!!");
		exit(-1);
	}
	strcpy(temp, stackHead->num.digits);
	free(stackHead->num.digits);
	stackHead->num.digits=temp;
}


bool stackIsEmpty()
{
	return 0;
}

int main()
{
	LinkedList *stackHead=(LinkedList *) malloc(sizeof(LinkedList));
	stackHead->num.digits=(char *) malloc(sizeof(char)*10);
	stackHead->num.num_of_digits=0;
	int ch;
	size_t size=0;
	while (EOF!=(ch=fgetc(stdin))/* && ch!='\n'*/)
	{
		stackHead->num.digits[stackHead->num.num_of_digits++]=(char) ch;
		if (stackHead->num.num_of_digits+1==size)
			increase(stackHead, &size);
		if (strcmp(ch, "+")==0)
		{
			if (!stackIsEmpty())
			{
				addition();
			}
		}
		else
			if (strcmp(ch, "-")==0)
			{
				if (!stackIsEmpty())
				{
					substraction();
				}
			}
			else
				if (strcmp(ch, "*")==0)
				{
					if (!stackIsEmpty())
					{
						multipliaction();
					}
				}
				else
					if (strcmp(ch, "/")==0)
					{
						if (!stackIsEmpty())
						{
							division();
						}
					}
					else
						if (strcmp(ch, "p")==0)
						{
							//TODO pop from stack and print the latest number that entered
						}
						else if (strcmp(ch,"q")==0)
							{
								exit(1);
							}
							else if (strcmp(ch,"c")==0)
								{
									//TODO Clear everything from the stack
								}
	}
	return 0;
}
