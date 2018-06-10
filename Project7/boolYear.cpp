#include"statement.h"
int isYear(int year)
{
	return (year % 4 == 0) && (year % 400 == 0 || year % 100 != 0) ? 1 : 0;
}

void getLeap()
{
	printf("请输入年份：");
	int year;
	scanf("%d", &year);
	if (isYear(year))
		printf("%d是闰年\n", year);
	else
	{
		printf("%d不是闰年\n", year);
	}
	returnMenu();
}
int getDayOfMonth(int year, int month)
{
	int dayArr[] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
	return (month == 2 && isYear(year) == 1) ? dayArr[month] + 1 : dayArr[month];
}

int getTotalDay(int year1, int month1, int day1, int year2, int month2, int day2)
{
	long total = 0;
	for (int year = year1; year < year2; year++)
	{
		total = total + 365;
		if (isYear(year) == 1)
			total++;
	}
	for (int month = 1; month < month2; month++)
	{
		total = total + getDayOfMonth(year2, month);
	}
	total = total + day2;
	for (int month = 1; month < month1; month++)
	{
		total = total - getDayOfMonth(year1, month);
	}
	return total - day1;
}




void CaculateWeekDay(int year, int month, int day)
{
	if (month == 1 || month == 2)
	{
		month += 12;
		year--;
	}
	int iWeek = (day + 2 * month + 3 * (month + 1) / 5 + year + year / 4 - year / 100 + year / 400) % 7;
	switch (iWeek)
	{
	case 0: printf("星期一\n"); break;
	case 1: printf("星期二\n"); break;
	case 2: printf("星期三\n"); break;
	case 3: printf("星期四\n"); break;
	case 4: printf("星期五\n"); break;
	case 5: printf("星期六\n"); break;
	case 6: printf("星期日\n"); break;

	}
}