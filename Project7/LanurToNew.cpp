#include"statement.h"
int LunarCalendar(int year, int month, int day)
{
	int Spring_NY, Sun_NY, StaticDayCount;
	int index, flag;
	//Spring_NY ��¼�����뵱��Ԫ����������  
	//Sun_NY ��¼�������뵱��Ԫ����������  
	if (((LunarCalendarTable[year - 1901] & 0x0060) >> 5) == 1)
		Spring_NY = (LunarCalendarTable[year - 1901] & 0x001F) - 1;
	else
		Spring_NY = (LunarCalendarTable[year - 1901] & 0x001F) - 1 + 31;
	Sun_NY = MonthAdd[month - 1] + day - 1;
	if ((!(year % 4)) && (month > 2))
		Sun_NY++;
	//StaticDayCount��¼��С�µ����� 29 ��30  
	//index ��¼���ĸ��¿�ʼ�����㡣  
	//flag �����������µ����⴦��  
	//�ж��������ڴ���ǰ���Ǵ��ں�  
	if (Sun_NY >= Spring_NY)//�������ڴ��ں󣨺��������죩  
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
	else //�������ڴ���ǰ  
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
	printf("ѡ���ܣ�\n1.����ת��ũ��\n2.ũ��ת������\n");
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
	const char *ChDay[] = { "*","��һ","����","����","����","����",
		"����","����","����","����","��ʮ",
		"ʮһ","ʮ��","ʮ��","ʮ��","ʮ��",
		"ʮ��","ʮ��","ʮ��","ʮ��","��ʮ",
		"إһ","إ��","إ��","إ��","إ��",
		"إ��","إ��","إ��","إ��","��ʮ"
	};
	const char *ChMonth[] = { "*","��","��","��","��","��","��","��","��","��","ʮ","ʮһ","��" };
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
	printf("���������빫���������գ�����2013��1��2�գ����룺2013-1-2��");
	scanf("%d-%d-%d", &year, &month, &day);
#endif  
	printf("%d��%d��%d��\t", year, month, day);
	if (LunarCalendar(year, month, day))
	{
		strcat(str, "��");
		strcat(str, ChMonth[(LunarCalendarDay & 0x3C0) >> 6]);
	}
	else
		strcat(str, ChMonth[(LunarCalendarDay & 0x3C0) >> 6]);
	strcat(str, "��");
	strcat(str, ChDay[LunarCalendarDay & 0x3F]);
	puts(str);
	getchar();
	returnMenu();
}
void lanurToNew()	//ũ��ת������
{
	int year;
	int month;
	int day;
	printf("������Ҫת���Ĺ������ڣ������ʽ��2000-01-01��(ʱ�䷶Χ��1936-2028)��\n");
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
	printf("���������ǣ�%d-%d-%d\n", year, month, day);
	returnMenu();
}

