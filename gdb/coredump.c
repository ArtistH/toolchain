#include <stdlib.h>

void f2(int *p1, int *p2)
{
	int *p = NULL;
	*p = 1;
}

void f1(int a, int b)
{
	f2(&a, &b);
}

int main()
{
	f1(1, 2);
    return 0;
}
