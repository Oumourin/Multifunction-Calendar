#include"ReturnMenu.h"

void returnMenu()
{
printf("1.返回主菜单  \n");
printf("2.退出系统    \n");
printf("请选择：\n");
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
