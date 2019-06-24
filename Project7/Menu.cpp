#include"Menu.h"
void mainMenu()
{
	printf("------------------------\n");
	printf("-                      -\n");
	printf("-      万能日历表      -\n");
	printf("-                      -\n");
	printf("-        主菜单        -\n");
	printf("-1.输出月历            -\n");
	printf("-2.闰年判定            -\n");
	printf("-3.公历/农历转换       -\n");
	printf("-4.节气查询            -\n");
	printf("-5.日期统计            -\n");
	printf("-6.退出系统            -\n");
	printf("-                      -\n");
	printf("------------------------\n");
	printf("                        \n");
	printf("请选择：");

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


void getStatistics()
{
	printf("1.统计出生至今的天数\n");
	printf("2.统计距离某日期最近的节假日的天数\n");
	printf("3.统计某日期是该年第几天星期几\n");
	printf("请输入：\n");
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