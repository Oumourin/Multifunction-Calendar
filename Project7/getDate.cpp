#include"statement.h"
void searchDate()
{
	int y, m;
	printf("输入年份和月份:");
	scanf("%d%d", &y, &m);
	printDate(y, m);
	returnMenu();

}

int getDate(int y, int m)
{
	int w = (y + (y - 1) / 4 - (y - 1) / 100 + (y - 1) / 400) % 7;
	int days = 0;
	switch (m)
	{
	case 12: days += 30;
	case 11: days += 31;
	case 10: days += 30;
	case 9:  days += 31;
	case 8:  days += 31;
	case 7:  days += 30;
	case 6:  days += 31;
	case 5:  days += 30;
	case 4:  days += 31;
	case 3:  if (isYear(y)) days += 29;
			 else days += 28;
	case 2:  days += 31;
	case 1:  days += 0;
	}
	w = (w + days) % 7;
	return w;     /*返回输入月份1号的星期*/
}

void printDate(int y, int m)
{
	int w = getDate(y, m);
	printf("%d年%d月的月历表:\n\n", y, m);
	printf("\n==========================="
		"========================\n\n");
	int month[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	if (isYear(y)) month[1] = 29;

	printf("SUN\tMON\tTUE\tWED\tTHU\tFRI\tSAT\n");
	int i, j;
	for (i = 0; i<w; i++) printf("\t");

	for (i = w, j = 1; j <= month[m - 1]; i++, j++)
	{
		if (i % 7 == 0) printf("\n");
		printf("%d\t", j);
	}
	printf("\n\n========================"
		"===========================\n\n");
}
