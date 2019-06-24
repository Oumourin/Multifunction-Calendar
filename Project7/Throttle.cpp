#include"Throttle.h"
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
	printf("请输入要查询的年份:\n");
	scanf("%d", &year);
	if (year<1940 || year >2040)
	{
		printf("输入超出制定范围\n\n");
	}
	printf("\n");
	printf("请选择你要查询的节气\n");
	printf(" ※※※※※※※※※※※※※※※※※※※※※ "); printf("\n");
	printf("\n");
	printf(" \t1.小寒\t2.大寒\t3.立春\t4.雨水\n");
	printf("\n");
	printf(" \t5.惊蛰\t6.春分\t7.清明\t8.谷雨\n");
	printf("\n");
	printf(" \t9.立夏\t10.小满\t11.芒种\t12.夏至\t\n");
	printf("\n");
	printf(" \t13.小暑\t14.大暑\t15.立秋\t16.处暑\t\n"); printf("\n");
	printf(" \t17.白露\t18.秋分\t19.寒露\t20.霜降\n");
	printf("\n");
	printf(" \t21.立冬\t22.小雪\t23.大雪\t24.冬至\n");
	printf("\n");
	printf(" ※※※※※※※※※※※※※※※※※※※※※ \n"); scanf("%d", &m);
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
	printf("公历%d年%d月%d日\n", year, iM, iD);
	returnMenu();
}