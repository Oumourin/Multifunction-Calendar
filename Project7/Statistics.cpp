#include"Statistics.h"
int getBirthday()
{
	int year1, month1, day1;
	int year2, month2, day2;
	do
	{
		printf("\n输入出生日期（输入格式1998-11-11）: ");
		scanf("%d-%d-%d", &year1, &month1, &day1);
	} while (year1 <0 || month1<1 || month1>12 || day1<1 || day1> getDayOfMonth(year1, month1));
	do
	{
		printf("\n\n\n输入要计算的日期（输入格式2000-11-11）: ");
		scanf("%d-%d-%d", &year2, &month2, &day2);
	} while (year2 <0 || year2 <year1 || month2<1 || month2>12 || day2<1 || day2> getDayOfMonth(year2, month2));
	printf("\n距离出生过了: %ld  days \n\n\n", getTotalDay(year1, month1, day1, year2, month2, day2));
	returnMenu();
	return 0;
}

void getInformation()
{
	printf("请输入日期(输入格式2000-01-01)：");
	int year, month, day;
	int sum, i;
	int months[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	scanf("%d-%d-%d", &year, &month, &day);
	printf("%d-%d-%d", year, month, day);
	if ((year % 400 == 0) || (year % 100 != 0 && year % 4 == 0))
	{
		months[1] += 1;
	}
	sum = 0;
	for (i = 1; i < month; i++)
	{
		sum += months[i - 1];
	}
	sum += day;
	printf("是该年的第%d天，", sum);
	CaculateWeekDay(year, month, day);
	printf("\n");
	returnMenu();
}

void getHoliday()	//假期计算，没有做农历假期，只考虑了公历假期
{
	int year, month, day;
	int temp = -1;
	printf("输入需要计算的日期：（日期格式：2000-01-01）");
	do
	{
		scanf("%d-%d-%d", &year, &month, &day);
	} while (year<0 || month <= 0 || month>12 || day <= 0 || day>31);
	switch (month)
	{
	case 1:
	case 2:
	case 3:
	case 4:temp = getTotalDay(year, month, day, year, 5, 1);
		break;
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:temp = getTotalDay(year, month, day, year, 10, 1);
		break;
	case 10:
	case 11:
	case 12:
		temp = getTotalDay(year, month, day, year + 1, 1, 1);
	default:
		break;
	}
	if (temp == -1)
	{
		printf("日期输入错误");
	}
	else
	{
		printf("距离最近假期还有：%d\n", temp);
	}
	returnMenu();
}
