#include"Menu.h"
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