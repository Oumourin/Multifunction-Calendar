#include"statement.h"
int main()
{
	mainMenu();

}
void mainMenu()
{
	printf("------------------------\n");
	printf("-                      -\n");
	printf("-      ����������      -\n");
	printf("-                      -\n");
	printf("-        ���˵�        -\n");
	printf("-1.�������            -\n");
	printf("-2.�����ж�            -\n");
	printf("-3.����/ũ��ת��       -\n");
	printf("-4.������ѯ            -\n");
	printf("-5.����ͳ��            -\n");
	printf("-6.�˳�ϵͳ            -\n");
	printf("-                      -\n");
	printf("------------------------\n");
	printf("                        \n");
	printf("��ѡ��");

	choiceMenu();

}

void choiceMenu()
{
	int a;
	scanf("%d", &a);
	printf("\n");
	switch (a)
	{
	case 1:
		system("cls");
		searchDate();
		break;
	case 2:
		system("cls");
		getLeap();
		break;
	case 3:
		system("cls");
		choiceLunar();
		break;
	case 4:
		system("cls");
		getThrottle();
		break;
	case 5:
		system("cls");
		getStatistics();
		break;
	case 6:
		exit(0);
	}
}


void searchDate()
{
	int y, m;
	printf("������ݺ��·�:");
	scanf("%d%d", &y, &m);
	printDate(y, m);
	returnMenu();

}

void returnMenu()
{
	printf("1.�������˵�  \n");
	printf("2.�˳�ϵͳ    \n");
	printf("��ѡ��\n");
	int t;
	scanf("%d", &t);
	if (t == 1)
	{
		system("cls");
		mainMenu();
	}
	else if (t == 2)
	{
		exit(0);
	}
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
	return w;     /*���������·�1�ŵ�����*/
}

void printDate(int y, int m)
{
	int w = getDate(y, m);
	printf("%d��%d�µ�������:\n\n", y, m);
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

int isYear(int year)
{
	return (year % 4 == 0) && (year % 400 == 0 || year % 100 != 0) ? 1 : 0;
}

void getLeap()
{
	printf("��������ݣ�");
	int year;
	scanf("%d", &year);
	if (isYear(year))
		printf("%d������\n",year);
	else
	{
		printf("%d��������\n",year);
	}
	returnMenu();
}



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
	scanf("%d",&temp);
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

void getThrottle()
{
	double f20[24] = { 6.11,20.84,4.15,19.0698,5.6744,21.624,5.59 ,
		20.888,6.318,21.86,6.5 ,22.20 ,7.928,23.65 ,8.35 ,23.95,
		8.44,23.822,9.098,24.218,8.218,23.08,7.9 ,22.60 };
	double f21[24] = { 5.4055,20.11 ,3.87 ,18.73,5.63 ,20.646,
		4.81 ,20.1  ,5.52 ,21.04,5.678,21.37,7.108,22.83 ,7.5  ,
		23.13,7.646,23.042,8.318,23.438,7.438,22.36,7.18 ,21.94 };
	int year, m;
	int tian = 0;
	printf("������Ҫ��ѯ�����:\n");
	scanf("%d", &year);
	if (year<1940 || year >2040)
	{
		printf("���볬���ƶ���Χ\n\n");
	}
	printf("\n");
	printf("��ѡ����Ҫ��ѯ�Ľ���\n");
	printf(" ������������������������������������������ "); printf("\n");
	printf("\n");
	printf(" \t1.С��\t2.��\t3.����\t4.��ˮ\n");
	printf("\n");
	printf(" \t5.����\t6.����\t7.����\t8.����\n");
	printf("\n");
	printf(" \t9.����\t10.С��\t11.â��\t12.����\t\n");
	printf("\n");
	printf(" \t13.С��\t14.����\t15.����\t16.����\t\n"); printf("\n");
	printf(" \t17.��¶\t18.���\t19.��¶\t20.˪��\n");
	printf("\n");
	printf(" \t21.����\t22.Сѩ\t23.��ѩ\t24.����\n");
	printf("\n");
	printf(" ������������������������������������������ \n"); scanf("%d", &m);
	int iL = 0;
	int iY = 0;
	int iD = 0;
	int iM = 0;
	if (year<2000)
	{
		iY = year - 1900;
		if (m<5)
		{
			iL = (iY - 1) / 4;
		}
		else
		{
			iL = iY / 4;
		}
		iD = (double)iY*0.2422 + f20[m - 1] - iL;
		iM = (m + 1) / 2;
		if (year == 1982 && m == 1)
		{
			iD--;
		}
		if (year == 1982 && m == 4)
		{
			iD--;
		}
		if (year == 1978 && m == 22)
		{
			iD++;
		}
		if (year == 1954 && m == 23)
		{
			iD++;
		}
	}
	else
	{
		iY = year - 2000;
		if (m<5)
		{
			iL = (iY - 1) / 4;
		}
		else
		{
			iL = iY / 4;
		}
		iD = (double)iY *0.2422 + f21[m - 1] - iL; iM = (m + 1) / 2;
		if (year == 2019 && m == 1)
		{
			iD--;
		}
		if (year == 2008 && m == 10)
		{
			iD++;
		}
		if (year == 2016 && m == 13)
		{
			iD++;
		}
		if (year == 2002 && m == 15)
		{
			iD++;
		}
		if (year == 2021 && m == 24)
		{
			iD--;
		}
	}
	printf("����%d��%d��%d��\n", year, iM, iD);
	returnMenu();
}

void getStatistics()
{
	printf("1.ͳ�Ƴ������������\n");
	printf("2.ͳ�ƾ���ĳ��������Ľڼ��յ�����\n");
	printf("3.ͳ��ĳ�����Ǹ���ڼ������ڼ�\n");
	printf("�����룺\n");
	sonMenu();
}

void sonMenu()
{
	char b;
	scanf("%d", &b);
	printf("\n");
	switch (b)
	{
	case 1:
		system("cls");
		getBirthday();
		break;
	case 2:
		system("cls");
		getHoliday();
		break;
	case 3:
		system("cls");
		getInformation();
		break;
	}
}

int getBirthday()
{
	int year1, month1, day1;
	int year2, month2, day2;
	do
	{
		printf("\n����������ڣ������ʽ1998-11-11��: ");
		scanf("%d-%d-%d", &year1, &month1, &day1);
	} while (year1 <0 || month1<1 || month1>12 || day1<1 || day1> getDayOfMonth(year1, month1));
	do
	{
		printf("\n\n\n����Ҫ��������ڣ������ʽ2000-11-11��: ");
		scanf("%d-%d-%d", &year2, &month2, &day2);
	} while (year2 <0 || year2 <year1 || month2<1 || month2>12 || day2<1 || day2> getDayOfMonth(year2, month2));
	printf("\n�����������: %ld  days \n\n\n", getTotalDay(year1, month1, day1, year2, month2, day2));
	returnMenu();
	return 0;
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

void getInformation()
{
	printf("����������(�����ʽ2000-01-01)��");
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
	printf("�Ǹ���ĵ�%d�죬", sum);
	CaculateWeekDay(year, month, day);
	printf("\n");
	returnMenu();
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
	case 0: printf("����һ\n"); break;
	case 1: printf("���ڶ�\n"); break;
	case 2: printf("������\n"); break;
	case 3: printf("������\n"); break;
	case 4: printf("������\n"); break;
	case 5: printf("������\n"); break;
	case 6: printf("������\n"); break;

	}
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
	} while (year<1936||year>2028||month<1||month>12||day<1||day>31);

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

void getHoliday()	//���ڼ��㣬û����ũ�����ڣ�ֻ�����˹�������
{
	int year, month, day;
	int temp=-1;
	printf("������Ҫ��������ڣ������ڸ�ʽ��2000-01-01��");
	do
	{
		scanf("%d-%d-%d",&year,&month,&day);
	} while (year<0||month<=0||month>12||day<=0||day>31);
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
	if (temp==-1)
	{
		printf("�����������");
	}
	else
	{
		printf("����������ڻ��У�%d\n",temp);
	}
	returnMenu();
}
