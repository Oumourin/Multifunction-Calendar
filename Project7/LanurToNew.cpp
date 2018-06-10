#include"statement.h"
int LunarCalendar(int year, int month, int day)
{
	int Spring_NY, Sun_NY, StaticDayCount;
	int index, flag;
	//Spring_NY 记录春节离当年元旦的天数。  
	//Sun_NY 记录阳历日离当年元旦的天数。  
	if (((LunarCalendarTable[year - 1901] & 0x0060) >> 5) == 1)
		Spring_NY = (LunarCalendarTable[year - 1901] & 0x001F) - 1;
	else
		Spring_NY = (LunarCalendarTable[year - 1901] & 0x001F) - 1 + 31;
	Sun_NY = MonthAdd[month - 1] + day - 1;
	if ((!(year % 4)) && (month > 2))
		Sun_NY++;
	//StaticDayCount记录大小月的天数 29 或30  
	//index 记录从哪个月开始来计算。  
	//flag 是用来对闰月的特殊处理。  
	//判断阳历日在春节前还是春节后  
	if (Sun_NY >= Spring_NY)//阳历日在春节后（含春节那天）  
	{
		Sun_NY -= Spring_NY;
		month = 1;
		index = 1;
		flag = 0;
		if ((LunarCalendarTable[year - 1901] & (0x80000 >> (index - 1))) == 0)
			StaticDayCount = 29;
		else
			StaticDayCount = 30;
		while (Sun_NY >= StaticDayCount)
		{
			Sun_NY -= StaticDayCount;
			index++;
			if (month == ((LunarCalendarTable[year - 1901] & 0xF00000) >> 20))
			{
				flag = ~flag;
				if (flag == 0)
					month++;
			}
			else
				month++;
			if ((LunarCalendarTable[year - 1901] & (0x80000 >> (index - 1))) == 0)
				StaticDayCount = 29;
			else
				StaticDayCount = 30;
		}
		day = Sun_NY + 1;
	}
	else //阳历日在春节前  
	{
		Spring_NY -= Sun_NY;
		year--;
		month = 12;
		if (((LunarCalendarTable[year - 1901] & 0xF00000) >> 20) == 0)
			index = 12;
		else
			index = 13;
		flag = 0;
		if ((LunarCalendarTable[year - 1901] & (0x80000 >> (index - 1))) == 0)
			StaticDayCount = 29;
		else
			StaticDayCount = 30;
		while (Spring_NY > StaticDayCount)
		{
			Spring_NY -= StaticDayCount;
			index--;
			if (flag == 0)
				month--;
			if (month == ((LunarCalendarTable[year - 1901] & 0xF00000) >> 20))
				flag = ~flag;
			if ((LunarCalendarTable[year - 1901] & (0x80000 >> (index - 1))) == 0)
				StaticDayCount = 29;
			else
				StaticDayCount = 30;
		}
		day = StaticDayCount - Spring_NY + 1;
	}
	LunarCalendarDay |= day;
	LunarCalendarDay |= (month << 6);
	if (month == ((LunarCalendarTable[year - 1901] & 0xF00000) >> 20))
		return 1;
	else
		return 0;
}

void choiceLunar()
{
	int temp = 0;
	printf("选择功能：\n1.公历转换农历\n2.农历转换公历\n");
	scanf("%d", &temp);
	switch (temp)
	{
	case 1:
		getLunar();
		break;
	case 2:
		lanurToNew();
		break;
	default:
		break;
	}
}

void getLunar()
{
	const char *ChDay[] = { "*","初一","初二","初三","初四","初五",
		"初六","初七","初八","初九","初十",
		"十一","十二","十三","十四","十五",
		"十六","十七","十八","十九","二十",
		"廿一","廿二","廿三","廿四","廿五",
		"廿六","廿七","廿八","廿九","三十"
	};
	const char *ChMonth[] = { "*","正","二","三","四","五","六","七","八","九","十","十一","腊" };
	struct tm * Local;
	long t;
	int year, month, day;
	char str[13] = "";
#if 0  
	t = time(NULL);
	Local = localtime(&t);
	year = Local->tm_year + 1900;
	month = Local->tm_mon + 1;
	day = Local->tm_mday;
#else  
	year = 2013;
	month = 2;
	day = 10;
	printf("请依次输入公历的年月日（例如2013年1月2日，输入：2013-1-2）");
	scanf("%d-%d-%d", &year, &month, &day);
#endif  
	printf("%d年%d月%d日\t", year, month, day);
	if (LunarCalendar(year, month, day))
	{
		strcat(str, "闰");
		strcat(str, ChMonth[(LunarCalendarDay & 0x3C0) >> 6]);
	}
	else
		strcat(str, ChMonth[(LunarCalendarDay & 0x3C0) >> 6]);
	strcat(str, "月");
	strcat(str, ChDay[LunarCalendarDay & 0x3F]);
	puts(str);
	getchar();
	returnMenu();
}
void lanurToNew()	//农历转换公历
{
	int year;
	int month;
	int day;
	printf("输入需要转换的公历日期（输入格式：2000-01-01）(时间范围：1936-2028)：\n");
	do
	{
		scanf("%d-%d-%d", &year, &month, &day);
	} while (year<1936 || year>2028 || month<1 || month>12 || day<1 || day>31);

	int index = year - 1936;
	int endIndex = month;
	if ((DATAS[index][1] != 0) && (month > DATAS[index][1]))
	{
		endIndex++;
	}
	int dayNum = 0;
	for (int i = 0; i < (endIndex - 1); i++)
	{
		dayNum += MONTH_DAYS[DATAS[index][4 + i]];
	}
	dayNum += day;
	dayNum += DATAS[index][0];
	int year_days = 365;
	if (isYear(year))
	{
		year_days = 366;
	}
	if (dayNum > year_days)
	{
		year++;
		dayNum -= year_days;
	}
	month = 1;

	int dayOfMonth[12];

	int i = 0;

	if (isYear(year))
	{
		for (i = 0; i < 12; i++)
		{
			dayOfMonth[i] = DAYS_MONTH[1][i];
		}
	}
	else
	{
		for (i = 0; i < 12; i++)
		{
			dayOfMonth[i] = DAYS_MONTH[0][i];
		}
	}

	for (i = 0; i < 12; i++)
	{
		dayNum -= dayOfMonth[i];
		if (dayNum <= 0)
		{
			break;
		}
		month++;
	}
	day = dayOfMonth[i] + dayNum;
	printf("新历日期是：%d-%d-%d\n", year, month, day);
	returnMenu();
}

