# Multifunction-calendar
NUC-中北大学C语言大作业-多功能月历

**请务必使用VS2019进行编译，低版本编译器处理不了头文件对应关系**

##  相关数据结构

##  一维数组

*  ```unsigned int LunarCalendarTable[199]```
  * 用于存储旧历和新历对应关系
*  ```int MonthAdd[12]```
  * 用于存储每月经过的天数
*  ```int MONTH_DAYS[]```
  * 用于存储大小月天数

###  二维数组

*   ```int DATAS[][17]```
  *  用于存储农历和新历转换关系
* ``` int DAYS_MONTH[][12] ```
  *  用于存储闰年和平年各月天数

##  相关函数

###  闰年判断函数

函数定义

```c++
int isYear(int year);
```

函数功能

接受一个年份，判断是否为闰年，为真则返回1

###  月份天数获取函数

函数定义

```c++
int getDayOfMonth(int year, int month);
```

函数功能

接受一个年份和一个月份，返回当月天数

###  计算经过天数函数

函数定义

```c++
int getTotalDay(int year1, int month1, int day1, int year2, int month2, int day2);
```

函数功能

接受两个年份和月份，计算相距天数

###  星期获取函数

函数定义

```C+=
void CaculateWeekDay(int year, int month, int day)；
```

函数功能

接受一个日期，输出其对应的星期

###  打印月历函数

函数定义

```c++
void searchDate()；
```

函数功能

接受一个年份和月份输入，输出对应月历

###  获取经过日期函数

函数定义

```c++
int getDate(int y, int m)；
```

函数功能

接受一个年份和月份，获取经过的天数

###  打印月历函数

函数定义 

```c++
void printDate(int y, int m);
```

函数功能

格式化输出月历方法

###  农历转换函数

函数定义

```c++
int LunarCalendar(int year, int month, int day)；
```

函数功能

接受一个年月日，实现农历转换

###  公历农历功能选择函数

函数定义

```c++
void choiceLunar();
```

函数功能

公历农历菜单选择逻辑