#include"ReturnMenu.h"

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
