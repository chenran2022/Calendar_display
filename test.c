#include<stdio.h>
#include<stdbool.h>
#include<time.h>
#include<Windows.h>
#include<stdlib.h>
#include<string.h>

//菜单
void menu();

//判断输入的年月日是否正常
bool DateIsRight(int year, int month, int day);

//显示指定年份的全年日历
void DisplayYearCalendar(int year);

//显示指定年月的日历
void DisplayMonthCalendar(int year, int month);

//显示指定日期的农历、农历节日，或者公历节日
//因txt文件只有2000年-2050年的农历日期，所以只能打印2000-2050年的农历
void DisplayLunarAndFestival(int lunar_m, int lunar_d, int month, int day);

//计算某一天为周几
int DayOfWeek(int year, int month, int day);

//计算某一个月的总天数
int DaysOfMonth(int year, int month);

//判断这一年是否为闰年
bool IsLeapYear(int year);

//计算距离当前时间多少天
void CalculateDays(int year, int month, int day);

//打印输入日期为星期几
void PrintDayOfWeek(int year, int month, int day);

//打印输入日期是否为公历和农历节日
void IsFestival(int year, int month, int day);

//结构体存放当前系统时间的年月日
struct CurrentDate
{
	int current_year;
	int current_month;
	int current_day;
};

int main()
{
	int i = 0;
	int year = 0, month = 0, day = 0;
	do
	{
		menu();
		scanf("%d", &i);
		switch (i)
		{
		case 1:
			printf("请输入要查找的年份：");
			scanf("%d", &year);
			if (DateIsRight(year, 1, 1))
			{
				DisplayYearCalendar(year);
			}
			else
			{
				system("cls");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
				printf("输入日期错误,请重新输入\n");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			}
			break;
		case 2:
			printf("请输入要查找的年份和月份: ");
			scanf("%d %d", &year, &month);
			if (DateIsRight(year, month, 1))
			{
				DisplayMonthCalendar(year, month);
			}
			else
			{
				system("cls");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
				printf("输入日期错误,请重新输入\n");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			}
			break;
		case 3:
			printf("请输入要查找的年、月、日: ");
			scanf("%d %d %d", &year, &month, &day);
			if (DateIsRight(year, month, day))
			{
				CalculateDays(year, month, day);
				PrintDayOfWeek(year, month, day);
				IsFestival(year, month, day);
			}
			else
			{
				system("cls");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
				printf("输入日期错误,请重新输入\n");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			}
			break;
		case 0:
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
			printf("退出成功\n");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			break;
		default:
			system("cls");
			printf("输入错误,请重新输入\n");
		}
	} while (i);
	
	return 0;
}

//菜单
void menu()
{
	//以只写的方式打开文件
	FILE* pf = fopen("menu.txt", "w");
	if (pf == NULL)
	{
		perror("fopen");
		exit(0);
	}
	fputs("	*********************************************************************************************\n", pf);
	fputs("		1:输入一个年份，输出是在屏幕上显示该年的日历。假定输入的年份在1900-2100年之间。\n", pf);
	fputs("		2:输入年月，输出该月的日历。                                                   \n", pf);
	fputs("		3:输入年月日，输出距今天还有多少天，星期几，是否是公历节日。                   \n", pf);
	fputs("		0:退出。                                                                       \n", pf);
	fputs("	*********************************************************************************************\n", pf);
	fputs("请输入你想实现的功能序号：", pf);
	fclose(pf);

	//以只读的方式打开文件
	pf = fopen("menu.txt", "r");
	if (pf == NULL)
	{
		perror("fopen");
		exit(0);
	}
	char arr[100];
	//读取文件内容并输出,
	for (int i = 0; i < 7; i++)
	{
		if (i == 0 || i == 5)
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
		else if (i == 1)
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
		else if (i == 2)
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
		else if (i == 3)
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
		else if (i == 4)
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
		else if (i == 6)
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		fgets(arr, 100, pf);
		printf("%s", arr);
	}
	fclose(pf);
	pf = NULL;
}
//判断输入的年月日是否正常
bool DateIsRight(int year, int month, int day)
{
	if (year >= 1900 && year <= 2100)
	{
		if (month >= 1 && month <= 12)
		{
			if (day >= 1 && day <= 31)
			{
				if (day > DaysOfMonth(year, month))
					return false;
				else
					return true;
			}
			else
				return false;
		}
		else
			return false;
	}
	else
		return false;
}
//显示指定年份的全年日历
void DisplayYearCalendar(int year)
{
	int i = 0;
	for (i = 1; i <= 12; i++)
	{
		DisplayMonthCalendar(year, i);
	}
}
//显示指定年月的日历
void  DisplayMonthCalendar(int year, int month)
{
	printf("----------------------", year, month);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
	printf("%4d年%2d月", year, month);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("-----------------------\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	printf("周日\t周一\t周二\t周三\t周四\t周五\t周六\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	//计算这一月的第一天为周几
	//0 - 星期日，1 - 星期一，2 - 星期二，3 - 星期三，4 - 星期四，5 - 星期五，6 - 星期六
	int first_day = DayOfWeek(year, month, 1);

	//计算这一个月的总天数	
	int day_month = DaysOfMonth(year, month);
	int count = first_day;

	char arr[30];
	char y[5], m[3], d[3], lm[3], ld[3];
	int temp_y, temp_m, temp_d, lunar_m, lunar_d;

	int count1 = first_day;
	int day = 1;
	int i = 0;
	for (i = 0; i <= day_month; i++)
	{
		//阳历
		//日期对齐
		if (i == 0)
		{
			for (int j = 0; j < (first_day % 7); j++)
			{
				printf("\t");
			}
		}
		else
		{
			printf(" %2d\t", i);
			count++;
		}

		//在合适的地方换行,其中有两个地方是特殊的，分别是第一行和最后一行
		if ((i != 0 && count == 7) || (i == day_month))
		{
			//使用两个计数器，来计算农历最后一天
			if (i != day_month)
				count = 0;
			printf("\n");

			//此txt文件只有2000年-2050年的农历日期
			if (year >= 2000 && year <= 2050)
			{
				//打印农历

			//日期对齐			
				if (i <= 7)
				{
					for (int j = 0; j < (first_day % 7); j++)
					{
						printf("\t");
					}
				}
				//txt文件类型必须为UTF-8，并且不带BOM，否则会有乱码
				//此文件只有2000年-2050年的农历日期
				FILE* pf = fopen("calendar.txt", "r");
				while (count1 < 7)
				{
					//使用strncpy和atoi获得指定日期
					while (1)
					{
						if (pf == NULL)
						{
							perror("fopen");
							exit(0);
						}
						fgets(arr, 30, pf);
						strncpy(y, arr + 1, 5);
						strncpy(m, arr + 6, 2);
						strncpy(d, arr + 9, 2);
						strncpy(lm, arr + 12, 2);
						strncpy(ld, arr + 15, 2);
						y[4] = '\0';
						m[2] = '\0';
						d[2] = '\0';
						lm[2] = '\0';
						ld[2] = '\0';
						temp_y = atoi(y);
						temp_m = atoi(m);
						temp_d = atoi(d);

						if (year == temp_y && month == temp_m && day == temp_d)
						{
							lunar_m = atoi(lm);
							lunar_d = atoi(ld);

							DisplayLunarAndFestival(lunar_m, lunar_d, month, day);//以农历形式进行显示
							day++;
							printf("\t");
							count1++;
							break;
						}
					}
					if (count1 == 7 || count1 == count)
					{
						count1 = 0;
						printf("\n\n");
						break;
					}
				}
				fclose(pf);
				pf = NULL;
			}
		}

	}

}

//显示指定日期的农历、农历节日，或者公历节日
//因txt文件只有2000年-2050年的农历日期，所以只能打印2000-2050年的农历
void DisplayLunarAndFestival(int lunar_m, int lunar_d, int month, int day)
{
	//用颜色突出显示农历节日
	if (lunar_m == 1 && lunar_d == 1) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
		printf("春节");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	}
	else if (lunar_m == 1 && lunar_d == 15) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
		printf("元宵");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	}
	else if (lunar_m == 5 && lunar_d == 5) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
		printf("端午节");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	}
	else if (lunar_m == 7 && lunar_d == 7) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
		printf("七夕");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	}
	else if (lunar_m == 7 && lunar_d == 15) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
		printf("中元节");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	}

	else if (lunar_m == 8 && lunar_d == 15) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
		printf("中秋节");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	}
	else if (lunar_m == 9 && lunar_d == 9)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
		printf("重阳节");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	}
	else if (lunar_m == 12 && lunar_d == 30) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
		printf("除夕");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	}

	//如果是公历节日
	else if (month == 1 && day == 1)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
		printf("元旦节");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

	}
	else if (month == 2 && day == 14)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
		printf("情人节");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	}
	else if (month == 3 && day == 8)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
		printf("妇女节");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	}
	else if (month == 3 && day == 12)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
		printf("植树节");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	}
	else if (month == 5 && day == 1)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
		printf("劳动节");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	}
	else if (month == 6 && day == 1)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
		printf("儿童节");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	}

	else if (month == 7 && day == 1)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
		printf("建党节");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	}
	else if (month == 8 && day == 1)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
		printf("建军节");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	}
	else if (month == 9 && day == 10)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
		printf("教师节");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	}
	else if (month == 10 && day == 1)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
		printf("国庆节");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

	}
	else if (month == 12 && day == 24)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
		printf("平安夜");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	}
	else if (month == 12 && day == 25)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
		printf("圣诞节");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	}
	else
	{
		switch (lunar_d)
		{
		case 1:printf("初一"); break;
		case 2:printf("初二"); break;
		case 3:printf("初三"); break;
		case 4:printf("初四"); break;
		case 5:printf("初五"); break;
		case 6:printf("初六"); break;
		case 7:printf("初七"); break;
		case 8:printf("初八"); break;
		case 9:printf("初九"); break;
		case 10:printf("初十"); break;
		case 11:printf("十一"); break;
		case 12:printf("十二"); break;
		case 13:printf("十三"); break;
		case 14:printf("十四"); break;
		case 15:printf("十五"); break;
		case 16:printf("十六"); break;
		case 17:printf("十七"); break;
		case 18:printf("十八"); break;
		case 19:printf("十九"); break;
		case 20:printf("二十"); break;
		case 21:printf("廿一"); break;
		case 22:printf("廿二"); break;
		case 23:printf("廿三"); break;
		case 24:printf("廿四"); break;
		case 25:printf("廿五"); break;
		case 26:printf("廿六"); break;
		case 27:printf("廿七"); break;
		case 28:printf("廿八"); break;
		case 29:printf("廿九"); break;
		case 30:printf("三十"); break;
		}
	}


}
//计算某一天为周几
int DayOfWeek(int year, int month, int day)
{
	//蔡勒（Zeller）公式，是一个计算星期的公式，随便给一个日期，就能用这个公式推算出是星期几。
	//	w=y + y / 4 + c / 4 - 2 * c + 26 * (m + 1) / 10 + d - 1;
	//	w：星期； w对7取模得：0 - 星期日，1 - 星期一，2 - 星期二，3 - 星期三，4 - 星期四，5 - 星期五，6 - 星期六
	//	c：世纪（注：一般情况下，在公式中取值为已经过的世纪数，也就是年份除以一百的结果，而非正在进行的世纪，也就是现在常用的年份除以一百加一；
	//			不过如果年份是公元前的年份且非整百数的话，c应该等于所在世纪的编号，如公元前253年，是公元前3世纪，c就等于 - 3）
	//	y：年（一般情况下是后两位数，如果是公元前的年份且非整百数，y应该等于c%100 + 100）
	//	m：月（m大于等于3，小于等于14，即在蔡勒公式中，某年的1、2月要看作上一年的13、14月来计算，比如2003年1月1日要看作2002年的13月1日来计算）
	//	d：日
	int c, y, week;
	if (month == 1 || month == 2)
	{
		year--;
		month += 12;
	}
	c = year / 100;
	y = year - c * 100;
	week = (y + y / 4 + c / 4 - 2 * c + 26 * (month + 1) / 10 + day - 1) % 7;
	week = (week >= 0 ? week : week + 7);//结果有可能为负数，：0 - 星期日，1 - 星期一，2 - 星期二，3 - 星期三，4 - 星期四，5 - 星期五，6 - 星期六
	return week;
}
//计算某一个月的总天数
int DaysOfMonth(int year, int month)
{
	int arr[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	if (month == 2)
	{
		//如果是闰年，2月有29天
		if (IsLeapYear(year))
			arr[1] = 29;
	}
	return arr[month - 1];
}
//判断这一年是否为闰年
bool IsLeapYear(int year)
{
	if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
		return true;
	return false;
}

//计算距离当前时间多少天
void CalculateDays(int year, int month, int day)
{
	//获取当前时间的结构体
	//tm_year是从1900年开始的，tm_mon是从0开始的（即1表示二月），tm_mday表示一个月中的第几天
	struct CurrentDate current_time;
	struct tm* p;
	time_t t;
	time(&t);
	p = localtime(&t);
	current_time.current_year = p->tm_year + 1900;
	current_time.current_month = p->tm_mon + 1;
	current_time.current_day = p->tm_mday;
	int days = 0;//计算相差的总天数
	//如果时间就是今天
	if (year == current_time.current_year && month == current_time.current_month && day == current_time.current_day)
	{
		printf("输入日期就是今天\n");
	}
	//如果时间比当前时间早
	else if (year < current_time.current_year || (year == current_time.current_year && month < current_time.current_month)
		|| (year == current_time.current_year && month == current_time.current_month && day < current_time.current_day))
	{
		//当年份相同时
		if (year == current_time.current_year)
		{
			//计算相差的整月天数
			for (int i = month + 1; i < current_time.current_month; i++)
			{
				days += DaysOfMonth(year, i);
			}
			//计算不是整月的天数
			if (month == current_time.current_month)
			{
				days += (current_time.current_day - day);
			}
			else
			{
				days += current_time.current_day;
				days += (DaysOfMonth(year, month) - day);
			}
		}
		//当年份不同时
		else
		{
			//计算相差的整年天数
			for (int i = year + 1; i < current_time.current_year; i++)
			{
				if (IsLeapYear(i))
					days += 366;
				else
					days += 365;
			}
			//计算当前年份已经过的整月天数
			for (int i = 1; i < current_time.current_month; i++)
			{
				days += DaysOfMonth(current_time.current_year, i);
			}
			//计算当前月份已经过的天数
			days += current_time.current_day;
			//计算输入年份过完一整年的整月天数
			for (int i = month + 1; i < 13; i++)
			{
				days += DaysOfMonth(year, i);
			}
			//计算输入月份过完一整月的天数
			days += (DaysOfMonth(year, month) - day);
		}
		printf("输入日期距离今天还差%d天\n", days);
	}
	//如果时间比当前时间晚
	else
	{
		//当年份相同时
		if (year == current_time.current_year)
		{
			//计算相差的整月天数
			for (int i = current_time.current_month + 1; i < month; i++)
			{
				days += DaysOfMonth(year, i);
			}
			//计算不是整月的天数
			if (month == current_time.current_month)
			{
				days += (day - current_time.current_day);
			}
			else
			{
				days += day;
				days += (DaysOfMonth(year, current_time.current_month) - current_time.current_day);
			}
		}
		//当年份不同时
		else
		{
			for (int i = current_time.current_year + 1; i < year; i++)
			{
				if (IsLeapYear(i))
					days += 366;
				else
					days += 365;
			}
			//计算输入年份已经过的整月天数
			for (int i = 1; i < month; i++)
			{
				days += DaysOfMonth(year, i);
			}
			//计算输入月份已经过的天数
			days += day;
			//计算当前年份过完一整年的整月天数
			for (int i = current_time.current_month + 1; i < 13; i++)
			{
				days += DaysOfMonth(current_time.current_year, i);
			}
			//计算当前月份过完一整月的天数
			days += (DaysOfMonth(current_time.current_year, current_time.current_month) - current_time.current_day);
		}
		printf("今天到输入日期还有%d天\n", days);
	}
}
//打印输入日期为星期几
void PrintDayOfWeek(int year, int month, int day)
{
	int week = DayOfWeek(year, month, day);
	switch (week)
	{
	case 1:
		printf("输入日期为星期一\n");
		break;
	case 2:
		printf("输入日期为星期二\n");
		break;
	case 3:
		printf("输入日期为星期三\n");
		break;
	case 4:
		printf("输入日期为星期四\n");
		break;
	case 5:
		printf("输入日期为星期五\n");
		break;
	case 6:
		printf("输入日期为星期六\n");
		break;
	case 0:
		printf("输入日期为星期日\n");
		break;
	default:
		break;
	}
}
//打印输入日期是否为公历和农历节日
void IsFestival(int year, int month, int day)
{
	if (year < 2000 || year>2050)
	{
		if (month == 1 && day == 1)
		{
			printf("输入日期是元旦节\n");
		}
		else if (month == 2 && day == 14)
		{
			printf("输入日期是情人节\n");
		}
		else if (month == 3 && day == 8)
		{
			printf("输入日期是妇女节\n");
		}
		else if (month == 3 && day == 12)
		{
			printf("输入日期是植树节\n");;
		}
		else if (month == 5 && day == 1)
		{
			printf("输入日期是劳动节\n");

		}
		else if (month == 6 && day == 1)
		{
			printf("输入日期是儿童节\n");
		}
		else if (month == 7 && day == 1)
		{
			printf("输入日期是建党节\n");
		}
		else if (month == 8 && day == 1)
		{
			printf("输入日期是建军节\n");
		}
		else if (month == 9 && day == 10)
		{
			printf("输入日期是教师节\n");
		}
		else if (month == 10 && day == 1)
		{
			printf("输入日期是国庆节\n");
		}
		else if (month == 12 && day == 24)
		{
			printf("输入日期是平安夜\n");
		}
		else if (month == 12 && day == 25)
		{
			printf("输入日期是圣诞节\n");

		}
		else
			printf("输入日期不是节日\n");
	}
	else
	{
		char arr[30];
		char y[5], m[3], d[3], lm[3], ld[3];
		int temp_y, temp_m, temp_d, lunar_m, lunar_d;
		FILE* pf = fopen("calendar.txt", "r");

		//使用strncpy和atoi获得指定日期所对应的农历日期
		while (1)
		{
			if (pf == NULL)
			{
				perror("fopen");
				exit(0);
			}
			fgets(arr, 30, pf);
			strncpy(y, arr + 1, 5);
			strncpy(m, arr + 6, 2);
			strncpy(d, arr + 9, 2);
			strncpy(lm, arr + 12, 2);
			strncpy(ld, arr + 15, 2);
			y[4] = '\0';
			m[2] = '\0';
			d[2] = '\0';
			lm[2] = '\0';
			ld[2] = '\0';
			temp_y = atoi(y);
			temp_m = atoi(m);
			temp_d = atoi(d);

			if (year == temp_y && month == temp_m && day == temp_d)
			{
				lunar_m = atoi(lm);
				lunar_d = atoi(ld);
				break;
			}
		}

		fclose(pf);
		pf = NULL;

		if (month == 1 && day == 1)
		{
			printf("输入日期是元旦节\n");
		}
		else if (month == 2 && day == 14)
		{
			printf("输入日期是情人节\n");
		}
		else if (month == 3 && day == 8)
		{
			printf("输入日期是妇女节\n");
		}
		else if (month == 3 && day == 12)
		{
			printf("输入日期是植树节\n");;
		}
		else if (month == 5 && day == 1)
		{
			printf("输入日期是劳动节\n");

		}
		else if (month == 6 && day == 1)
		{
			printf("输入日期是儿童节\n");
		}
		else if (month == 7 && day == 1)
		{
			printf("输入日期是建党节\n");
		}
		else if (month == 8 && day == 1)
		{
			printf("输入日期是建军节\n");
		}
		else if (month == 9 && day == 10)
		{
			printf("输入日期是教师节\n");
		}
		else if (month == 10 && day == 1)
		{
			printf("输入日期是国庆节\n");
		}
		else if (month == 12 && day == 24)
		{
			printf("输入日期是平安夜\n");
		}
		else if (month == 12 && day == 25)
		{
			printf("输入日期是圣诞节\n");

		}

		//农历节日
		else if (lunar_m == 1 && lunar_d == 1) {
			printf("输入日期是春节\n");
		}
		else if (lunar_m == 1 && lunar_d == 15) {
			printf("输入日期是元宵节\n");
		}
		else if (lunar_m == 5 && lunar_d == 5) {
			printf("输入日期是端午节\n");
		}
		else if (lunar_m == 7 && lunar_d == 7) {
			printf("输入日期是七夕节\n");
		}
		else if (lunar_m == 7 && lunar_d == 15) {
			printf("输入日期是中元节\n");
		}

		else if (lunar_m == 8 && lunar_d == 15) {
			printf("输入日期是中秋节\n");
		}
		else if (lunar_m == 9 && lunar_d == 9)
		{
			printf("输入日期是重阳节\n");
		}
		else if (lunar_m == 12 && lunar_d == 30) {
			printf("输入日期是除夕\n");
		}
		else
			printf("输入日期不是节日\n");

	}

}
