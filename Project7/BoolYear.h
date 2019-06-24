#pragma once
#include<stdio.h>
#include"ReturnMenu.h"

#ifndef BOOL_YEAR_H
#define BOOL_YEAR_H
int isYear(int year);

void getLeap();

int getDayOfMonth(int year, int month);

int getTotalDay(int year1, int month1, int day1, int year2, int month2, int day2);

void CaculateWeekDay(int year, int month, int day);



#endif // !BOOL_YEAR_H
