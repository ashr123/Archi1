#include <stdio.h>

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

int main()
{
	LinkedList a;
	
	scanf("%s", a.num.digits);
	return 0;
}