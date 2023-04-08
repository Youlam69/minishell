#include "stdio.h"
#include "stdlib.h"

void tst(int *tab)
{
	tab[0]++;
	tab[1] = 555;
}
int main()
{
	int i;
	int h;
	int *tab;
	tab = malloc((sizeof(int) * 2));
	tab[0] = i;
	tab[1] = h;
	i = 44;
	h = 202;
	printf("tab 0 =  %d u tab 1 = %d\n", tab[0], tab[1]);

	printf("tab 0 =  %d u tab 1 = %d\n", i, h);
	tst(tab);
	printf("tab 0 =  %d u tab 1 = %d\n", tab[0], tab[1]);

	printf("tab 0 =  %d u tab 1 = %d\n", i, h);

}
