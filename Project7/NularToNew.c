#include"statement.h"

typedef struct _lunar {
	int year;
	int month;
	int day;
	int is_leap;
} lunar_t;

int is_gregorian_leap(int year)
{
	return((((year % 4) == 0) && ((year % 100) != 0)) || ((year % 400) == 0));
}

#define MIN_YEAR 1901  
#define MAX_YEAR 2099  


int lunarLeapMonth(int y)
{
	return((LunarCalendarTable[y - MIN_YEAR] & 0xf00000) >> 20);
}

int lunarMonthDays(int y, int m)
{
	return((LunarCalendarTable[y - MIN_YEAR] & (0x80000 >> (m - 1))) ? 30 : 29);
}

int lunarLeapMonthDays(int y)
{
	if (lunarLeapMonth(y))
	{
		return((LunarCalendarTable[y - MIN_YEAR] & (0x80000 >> (lunarLeapMonth(y) - 1))) ? 30 : 29);
	}
	else
	{
		return 0;
	}
}

int lunarSpringDate(int y, int*solar_m, int* solar_d)
{
	if (!solar_m || !solar_d)
		return -1;
	*solar_m = (LunarCalendarTable[y - MIN_YEAR] & 0x0060) >> 5;
	*solar_d = LunarCalendarTable[y - MIN_YEAR] & 0x1f;
	return 0;
}

int lunarDateCheck(lunar_t lunar)
{
	int leap = 0;

	if ((lunar.year < MIN_YEAR) || (lunar.year > MAX_YEAR))
	{
		return -1;
	}

	if ((lunar.month < 1) || (lunar.month > 12))
	{
		return -1;
	}

	if ((lunar.day < 1) || (lunar.day > 30)) //�й��������30��  
	{
		return -1;
	}

	if (lunarMonthDays(lunar.year, lunar.month)<lunar.day)
	{
		return -1;
	}

	if (lunar.is_leap == 1)
	{
		leap = lunarLeapMonth(lunar.year);
		if (leap == 0)
			return -1;
		else if (lunar.month != leap)
			return -1;
		else if (lunarLeapMonthDays(lunar.year)<lunar.day)
		{
			return -1;
		}
	}
	return 0;
}

int solarDateCheck(int year, int month, int day)
{
	if ((year < MIN_YEAR) || (year > MAX_YEAR))
	{
		return -1;
	}

	if ((month < 1) || (month > 12))
	{
		return -1;
	}
	if ((day < 1) || (day > 31))
	{
		return -1;
	}

	if (month == 2)
	{
		if (is_gregorian_leap(year))// ������  
		{
			if (day>29)
				return -1;
		}
		else
		{
			if (day>28)
				return -1;
		}
	}

	return 0;
}



int monthTotal[13] = { 0,31,59,90,120,151,181,212,243,273,304,334,365 };
int toSolar(lunar_t lunar, int* y, int* m, int*d)
{
	int year = lunar.year,
		month = lunar.month,
		day = lunar.day;
	int byNow, xMonth, i;
	int spring_solar_d;
	int spring_solar_m;
	if (lunarDateCheck(lunar) == -1)
		return -1;
	if (!y || !m || !d)
		return -1;

	lunarSpringDate(year, &spring_solar_m, &spring_solar_d);

	byNow = spring_solar_d - 1;
	if (spring_solar_m == 2)
		byNow += 31;
	for (i = 1; i < month; i++) {
		byNow += lunarMonthDays(year, i);
	}

	byNow += day;
	xMonth = lunarLeapMonth(year);
	if (xMonth != 0) {
		if (month > xMonth || (month == xMonth && lunar.is_leap == 1)) {
			byNow += lunarLeapMonthDays(year);
		}
	}

	if (byNow > 366 || (year % 4 != 0 && byNow == 365)) {
		year += 1;
		if (year % 4 == 0)
			byNow -= 366;
		else
			byNow -= 365;
	}

	for (i = 1; i <= 13; i++) {
		if (monthTotal[i] >= byNow) {
			month = i;
			break;
		}
	}
	*d = byNow - monthTotal[month - 1];
	*m = month;
	*y = year;

	return 0;
}

int toLunar(int year, int month, int day, lunar_t * lunar)
{
	int bySpring, bySolar, daysPerMonth;
	int index, flag;
	int spring_solar_d;
	int spring_solar_m;

	if (!lunar)
		return -1;
	if (solarDateCheck(year, month, day) == -1)
		return -1;

	//bySpring ��¼�����뵱��Ԫ����������  
	//bySolar ��¼�������뵱��Ԫ����������  
	lunarSpringDate(year, &spring_solar_m, &spring_solar_d);
	if (spring_solar_m == 1)
		bySpring = spring_solar_d - 1;
	else
		bySpring = spring_solar_d - 1 + 31;

	bySolar = monthTotal[month - 1] + day - 1;
	if ((!(year % 4)) && (month > 2))
		bySolar++;

	//daysPerMonth��¼��С�µ����� 29 ��30  
	//index ��¼���ĸ��¿�ʼ�����㡣  
	//flag �����������µ����⴦��  

	//�ж��������ڴ���ǰ���Ǵ��ں�  
	if (bySolar >= bySpring) /*/�������ڴ��ں󣨺��������죩*/
	{
		bySolar -= bySpring;
		month = 1;
		flag = 0;
		daysPerMonth = lunarMonthDays(year, month);

		while (bySolar >= daysPerMonth)
		{
			bySolar -= daysPerMonth;
			if (month == lunarLeapMonth(year))
			{
				flag = ~flag;
				if (flag == 0)
				{
					month++;
				}
			}
			else
			{
				month++;
			}
			daysPerMonth = lunarMonthDays(year, month);
		}
		day = bySolar + 1;
	}
	else
	{                                                      //�������ڴ���ǰ   
		bySpring -= bySolar;
		year--;
		month = 12;
		if (lunarLeapMonth(year) == 0)
			index = 12;
		else
			index = 13;
		flag = 0;

		daysPerMonth = lunarMonthDays(year, index);

		while (bySpring > daysPerMonth)
		{
			bySpring -= daysPerMonth;
			index--;

			if (flag == 0)
				month--;
			if (month == lunarLeapMonth(year))
			{
				flag = !flag;
			}
			daysPerMonth = lunarMonthDays(year, index);
		}
		day = daysPerMonth - bySpring + 1;
	}
	lunar->day = day;
	lunar->month = month;
	lunar->year = year;
	if (month == lunarLeapMonth(year))
		lunar->is_leap = 1;
	else
		lunar->is_leap = 0;
	return 0;
}

int main(int argc, char*argv[])
{
	const char *ChDay[] = { "*","��һ","����","����","����","����",
		"����","����","����","����","��ʮ",
		"ʮһ","ʮ��","ʮ��","ʮ��","ʮ��",
		"ʮ��","ʮ��","ʮ��","ʮ��","��ʮ",
		"إһ","إ��","إ��","إ��","إ��",
		"إ��","إ��","إ��","إ��","��ʮ" };
	const char *ChMonth[] = { "*","��","��","��","��","��","��","��","��","��","ʮ","ʮһ","��" };
	int year, month, day;
#if 0  
	lunar_t olunar = {
		.year = 2009,
		.month = 5,
		.day = 17,
		.is_leap = 1, //1��ʾ����,0��ʾƽ��  
	};
#else  
	lunar_t olunar = {
		.year = 1985,
		.month = 1,
		.day = 11,
		.is_leap = 0, //1��ʾ����,0��ʾƽ��  
	};
#endif  
	lunar_t lunar;

	if (toSolar(olunar, &year, &month, &day) == 0)
	{
		printf("Lunar: %d-%s-%s", olunar.year, ChMonth[olunar.month], ChDay[olunar.day]);
		printf(" =>Solar: %d-%d-%d\n", year, month, day);
	}
	if (toLunar(year, month, day, &lunar) == 0)
	{
		printf("Solar: %d-%02d-%02d", year, month, day);
		printf(" =>Lunar: %d-%s-%s\n", lunar.year, ChMonth[lunar.month], ChDay[lunar.day]);
	}


	printf("%d\r\n", lunarLeapMonth(2015));
	printf("%d\r\n", lunarMonthDays(2015, 1));
	printf("%d\r\n", lunarMonthDays(2015, 2));
	printf("%d\r\n", lunarMonthDays(2015, 3));
	printf("%d\r\n", lunarMonthDays(1015, 5));
	lunarSpringDate(2015, &month, &day);
	printf("springDate is %d - %d\r\n", month, day);


	return 0;
}