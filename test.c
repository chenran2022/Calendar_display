#include<stdio.h>
#include<stdbool.h>
#include<time.h>
#include<Windows.h>
#include<stdlib.h>
#include<string.h>

//�˵�
void menu();

//�ж�������������Ƿ�����
bool DateIsRight(int year, int month, int day);

//��ʾָ����ݵ�ȫ������
void DisplayYearCalendar(int year);

//��ʾָ�����µ�����
void DisplayMonthCalendar(int year, int month);

//��ʾָ�����ڵ�ũ����ũ�����գ����߹�������
//��txt�ļ�ֻ��2000��-2050���ũ�����ڣ�����ֻ�ܴ�ӡ2000-2050���ũ��
void DisplayLunarAndFestival(int lunar_m, int lunar_d, int month, int day);

//����ĳһ��Ϊ�ܼ�
int DayOfWeek(int year, int month, int day);

//����ĳһ���µ�������
int DaysOfMonth(int year, int month);

//�ж���һ���Ƿ�Ϊ����
bool IsLeapYear(int year);

//������뵱ǰʱ�������
void CalculateDays(int year, int month, int day);

//��ӡ��������Ϊ���ڼ�
void PrintDayOfWeek(int year, int month, int day);

//��ӡ���������Ƿ�Ϊ������ũ������
void IsFestival(int year, int month, int day);

//�ṹ���ŵ�ǰϵͳʱ���������
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
			printf("������Ҫ���ҵ���ݣ�");
			scanf("%d", &year);
			if (DateIsRight(year, 1, 1))
			{
				DisplayYearCalendar(year);
			}
			else
			{
				system("cls");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
				printf("�������ڴ���,����������\n");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			}
			break;
		case 2:
			printf("������Ҫ���ҵ���ݺ��·�: ");
			scanf("%d %d", &year, &month);
			if (DateIsRight(year, month, 1))
			{
				DisplayMonthCalendar(year, month);
			}
			else
			{
				system("cls");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
				printf("�������ڴ���,����������\n");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			}
			break;
		case 3:
			printf("������Ҫ���ҵ��ꡢ�¡���: ");
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
				printf("�������ڴ���,����������\n");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			}
			break;
		case 0:
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
			printf("�˳��ɹ�\n");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			break;
		default:
			system("cls");
			printf("�������,����������\n");
		}
	} while (i);
	
	return 0;
}

//�˵�
void menu()
{
	//��ֻд�ķ�ʽ���ļ�
	FILE* pf = fopen("menu.txt", "w");
	if (pf == NULL)
	{
		perror("fopen");
		exit(0);
	}
	fputs("	*********************************************************************************************\n", pf);
	fputs("		1:����һ����ݣ����������Ļ����ʾ������������ٶ�����������1900-2100��֮�䡣\n", pf);
	fputs("		2:�������£�������µ�������                                                   \n", pf);
	fputs("		3:���������գ��������컹�ж����죬���ڼ����Ƿ��ǹ������ա�                   \n", pf);
	fputs("		0:�˳���                                                                       \n", pf);
	fputs("	*********************************************************************************************\n", pf);
	fputs("����������ʵ�ֵĹ�����ţ�", pf);
	fclose(pf);

	//��ֻ���ķ�ʽ���ļ�
	pf = fopen("menu.txt", "r");
	if (pf == NULL)
	{
		perror("fopen");
		exit(0);
	}
	char arr[100];
	//��ȡ�ļ����ݲ����,
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
//�ж�������������Ƿ�����
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
//��ʾָ����ݵ�ȫ������
void DisplayYearCalendar(int year)
{
	int i = 0;
	for (i = 1; i <= 12; i++)
	{
		DisplayMonthCalendar(year, i);
	}
}
//��ʾָ�����µ�����
void  DisplayMonthCalendar(int year, int month)
{
	printf("----------------------", year, month);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
	printf("%4d��%2d��", year, month);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("-----------------------\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	printf("����\t��һ\t�ܶ�\t����\t����\t����\t����\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	//������һ�µĵ�һ��Ϊ�ܼ�
	//0 - �����գ�1 - ����һ��2 - ���ڶ���3 - ��������4 - �����ģ�5 - �����壬6 - ������
	int first_day = DayOfWeek(year, month, 1);

	//������һ���µ�������	
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
		//����
		//���ڶ���
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

		//�ں��ʵĵط�����,�����������ط�������ģ��ֱ��ǵ�һ�к����һ��
		if ((i != 0 && count == 7) || (i == day_month))
		{
			//ʹ��������������������ũ�����һ��
			if (i != day_month)
				count = 0;
			printf("\n");

			//��txt�ļ�ֻ��2000��-2050���ũ������
			if (year >= 2000 && year <= 2050)
			{
				//��ӡũ��

			//���ڶ���			
				if (i <= 7)
				{
					for (int j = 0; j < (first_day % 7); j++)
					{
						printf("\t");
					}
				}
				//txt�ļ����ͱ���ΪUTF-8�����Ҳ���BOM�������������
				//���ļ�ֻ��2000��-2050���ũ������
				FILE* pf = fopen("calendar.txt", "r");
				while (count1 < 7)
				{
					//ʹ��strncpy��atoi���ָ������
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

							DisplayLunarAndFestival(lunar_m, lunar_d, month, day);//��ũ����ʽ������ʾ
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

//��ʾָ�����ڵ�ũ����ũ�����գ����߹�������
//��txt�ļ�ֻ��2000��-2050���ũ�����ڣ�����ֻ�ܴ�ӡ2000-2050���ũ��
void DisplayLunarAndFestival(int lunar_m, int lunar_d, int month, int day)
{
	//����ɫͻ����ʾũ������
	if (lunar_m == 1 && lunar_d == 1) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
		printf("����");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	}
	else if (lunar_m == 1 && lunar_d == 15) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
		printf("Ԫ��");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	}
	else if (lunar_m == 5 && lunar_d == 5) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
		printf("�����");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	}
	else if (lunar_m == 7 && lunar_d == 7) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
		printf("��Ϧ");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	}
	else if (lunar_m == 7 && lunar_d == 15) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
		printf("��Ԫ��");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	}

	else if (lunar_m == 8 && lunar_d == 15) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
		printf("�����");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	}
	else if (lunar_m == 9 && lunar_d == 9)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
		printf("������");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	}
	else if (lunar_m == 12 && lunar_d == 30) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
		printf("��Ϧ");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	}

	//����ǹ�������
	else if (month == 1 && day == 1)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
		printf("Ԫ����");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

	}
	else if (month == 2 && day == 14)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
		printf("���˽�");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	}
	else if (month == 3 && day == 8)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
		printf("��Ů��");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	}
	else if (month == 3 && day == 12)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
		printf("ֲ����");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	}
	else if (month == 5 && day == 1)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
		printf("�Ͷ���");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	}
	else if (month == 6 && day == 1)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
		printf("��ͯ��");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	}

	else if (month == 7 && day == 1)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
		printf("������");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	}
	else if (month == 8 && day == 1)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
		printf("������");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	}
	else if (month == 9 && day == 10)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
		printf("��ʦ��");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	}
	else if (month == 10 && day == 1)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
		printf("�����");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

	}
	else if (month == 12 && day == 24)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
		printf("ƽ��ҹ");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	}
	else if (month == 12 && day == 25)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
		printf("ʥ����");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	}
	else
	{
		switch (lunar_d)
		{
		case 1:printf("��һ"); break;
		case 2:printf("����"); break;
		case 3:printf("����"); break;
		case 4:printf("����"); break;
		case 5:printf("����"); break;
		case 6:printf("����"); break;
		case 7:printf("����"); break;
		case 8:printf("����"); break;
		case 9:printf("����"); break;
		case 10:printf("��ʮ"); break;
		case 11:printf("ʮһ"); break;
		case 12:printf("ʮ��"); break;
		case 13:printf("ʮ��"); break;
		case 14:printf("ʮ��"); break;
		case 15:printf("ʮ��"); break;
		case 16:printf("ʮ��"); break;
		case 17:printf("ʮ��"); break;
		case 18:printf("ʮ��"); break;
		case 19:printf("ʮ��"); break;
		case 20:printf("��ʮ"); break;
		case 21:printf("إһ"); break;
		case 22:printf("إ��"); break;
		case 23:printf("إ��"); break;
		case 24:printf("إ��"); break;
		case 25:printf("إ��"); break;
		case 26:printf("إ��"); break;
		case 27:printf("إ��"); break;
		case 28:printf("إ��"); break;
		case 29:printf("إ��"); break;
		case 30:printf("��ʮ"); break;
		}
	}


}
//����ĳһ��Ϊ�ܼ�
int DayOfWeek(int year, int month, int day)
{
	//���գ�Zeller����ʽ����һ���������ڵĹ�ʽ������һ�����ڣ������������ʽ����������ڼ���
	//	w=y + y / 4 + c / 4 - 2 * c + 26 * (m + 1) / 10 + d - 1;
	//	w�����ڣ� w��7ȡģ�ã�0 - �����գ�1 - ����һ��2 - ���ڶ���3 - ��������4 - �����ģ�5 - �����壬6 - ������
	//	c�����ͣ�ע��һ������£��ڹ�ʽ��ȡֵΪ�Ѿ�������������Ҳ������ݳ���һ�ٵĽ�����������ڽ��е����ͣ�Ҳ�������ڳ��õ���ݳ���һ�ټ�һ��
	//			�����������ǹ�Ԫǰ������ҷ��������Ļ���cӦ�õ����������͵ı�ţ��繫Ԫǰ253�꣬�ǹ�Ԫǰ3���ͣ�c�͵��� - 3��
	//	y���꣨һ��������Ǻ���λ��������ǹ�Ԫǰ������ҷ���������yӦ�õ���c%100 + 100��
	//	m���£�m���ڵ���3��С�ڵ���14�����ڲ��չ�ʽ�У�ĳ���1��2��Ҫ������һ���13��14�������㣬����2003��1��1��Ҫ����2002���13��1�������㣩
	//	d����
	int c, y, week;
	if (month == 1 || month == 2)
	{
		year--;
		month += 12;
	}
	c = year / 100;
	y = year - c * 100;
	week = (y + y / 4 + c / 4 - 2 * c + 26 * (month + 1) / 10 + day - 1) % 7;
	week = (week >= 0 ? week : week + 7);//����п���Ϊ��������0 - �����գ�1 - ����һ��2 - ���ڶ���3 - ��������4 - �����ģ�5 - �����壬6 - ������
	return week;
}
//����ĳһ���µ�������
int DaysOfMonth(int year, int month)
{
	int arr[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	if (month == 2)
	{
		//��������꣬2����29��
		if (IsLeapYear(year))
			arr[1] = 29;
	}
	return arr[month - 1];
}
//�ж���һ���Ƿ�Ϊ����
bool IsLeapYear(int year)
{
	if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
		return true;
	return false;
}

//������뵱ǰʱ�������
void CalculateDays(int year, int month, int day)
{
	//��ȡ��ǰʱ��Ľṹ��
	//tm_year�Ǵ�1900�꿪ʼ�ģ�tm_mon�Ǵ�0��ʼ�ģ���1��ʾ���£���tm_mday��ʾһ�����еĵڼ���
	struct CurrentDate current_time;
	struct tm* p;
	time_t t;
	time(&t);
	p = localtime(&t);
	current_time.current_year = p->tm_year + 1900;
	current_time.current_month = p->tm_mon + 1;
	current_time.current_day = p->tm_mday;
	int days = 0;//��������������
	//���ʱ����ǽ���
	if (year == current_time.current_year && month == current_time.current_month && day == current_time.current_day)
	{
		printf("�������ھ��ǽ���\n");
	}
	//���ʱ��ȵ�ǰʱ����
	else if (year < current_time.current_year || (year == current_time.current_year && month < current_time.current_month)
		|| (year == current_time.current_year && month == current_time.current_month && day < current_time.current_day))
	{
		//�������ͬʱ
		if (year == current_time.current_year)
		{
			//����������������
			for (int i = month + 1; i < current_time.current_month; i++)
			{
				days += DaysOfMonth(year, i);
			}
			//���㲻�����µ�����
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
		//����ݲ�ͬʱ
		else
		{
			//����������������
			for (int i = year + 1; i < current_time.current_year; i++)
			{
				if (IsLeapYear(i))
					days += 366;
				else
					days += 365;
			}
			//���㵱ǰ����Ѿ�������������
			for (int i = 1; i < current_time.current_month; i++)
			{
				days += DaysOfMonth(current_time.current_year, i);
			}
			//���㵱ǰ�·��Ѿ���������
			days += current_time.current_day;
			//����������ݹ���һ�������������
			for (int i = month + 1; i < 13; i++)
			{
				days += DaysOfMonth(year, i);
			}
			//���������·ݹ���һ���µ�����
			days += (DaysOfMonth(year, month) - day);
		}
		printf("�������ھ�����컹��%d��\n", days);
	}
	//���ʱ��ȵ�ǰʱ����
	else
	{
		//�������ͬʱ
		if (year == current_time.current_year)
		{
			//����������������
			for (int i = current_time.current_month + 1; i < month; i++)
			{
				days += DaysOfMonth(year, i);
			}
			//���㲻�����µ�����
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
		//����ݲ�ͬʱ
		else
		{
			for (int i = current_time.current_year + 1; i < year; i++)
			{
				if (IsLeapYear(i))
					days += 366;
				else
					days += 365;
			}
			//������������Ѿ�������������
			for (int i = 1; i < month; i++)
			{
				days += DaysOfMonth(year, i);
			}
			//���������·��Ѿ���������
			days += day;
			//���㵱ǰ��ݹ���һ�������������
			for (int i = current_time.current_month + 1; i < 13; i++)
			{
				days += DaysOfMonth(current_time.current_year, i);
			}
			//���㵱ǰ�·ݹ���һ���µ�����
			days += (DaysOfMonth(current_time.current_year, current_time.current_month) - current_time.current_day);
		}
		printf("���쵽�������ڻ���%d��\n", days);
	}
}
//��ӡ��������Ϊ���ڼ�
void PrintDayOfWeek(int year, int month, int day)
{
	int week = DayOfWeek(year, month, day);
	switch (week)
	{
	case 1:
		printf("��������Ϊ����һ\n");
		break;
	case 2:
		printf("��������Ϊ���ڶ�\n");
		break;
	case 3:
		printf("��������Ϊ������\n");
		break;
	case 4:
		printf("��������Ϊ������\n");
		break;
	case 5:
		printf("��������Ϊ������\n");
		break;
	case 6:
		printf("��������Ϊ������\n");
		break;
	case 0:
		printf("��������Ϊ������\n");
		break;
	default:
		break;
	}
}
//��ӡ���������Ƿ�Ϊ������ũ������
void IsFestival(int year, int month, int day)
{
	if (year < 2000 || year>2050)
	{
		if (month == 1 && day == 1)
		{
			printf("����������Ԫ����\n");
		}
		else if (month == 2 && day == 14)
		{
			printf("�������������˽�\n");
		}
		else if (month == 3 && day == 8)
		{
			printf("���������Ǹ�Ů��\n");
		}
		else if (month == 3 && day == 12)
		{
			printf("����������ֲ����\n");;
		}
		else if (month == 5 && day == 1)
		{
			printf("�����������Ͷ���\n");

		}
		else if (month == 6 && day == 1)
		{
			printf("���������Ƕ�ͯ��\n");
		}
		else if (month == 7 && day == 1)
		{
			printf("���������ǽ�����\n");
		}
		else if (month == 8 && day == 1)
		{
			printf("���������ǽ�����\n");
		}
		else if (month == 9 && day == 10)
		{
			printf("���������ǽ�ʦ��\n");
		}
		else if (month == 10 && day == 1)
		{
			printf("���������ǹ����\n");
		}
		else if (month == 12 && day == 24)
		{
			printf("����������ƽ��ҹ\n");
		}
		else if (month == 12 && day == 25)
		{
			printf("����������ʥ����\n");

		}
		else
			printf("�������ڲ��ǽ���\n");
	}
	else
	{
		char arr[30];
		char y[5], m[3], d[3], lm[3], ld[3];
		int temp_y, temp_m, temp_d, lunar_m, lunar_d;
		FILE* pf = fopen("calendar.txt", "r");

		//ʹ��strncpy��atoi���ָ����������Ӧ��ũ������
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
			printf("����������Ԫ����\n");
		}
		else if (month == 2 && day == 14)
		{
			printf("�������������˽�\n");
		}
		else if (month == 3 && day == 8)
		{
			printf("���������Ǹ�Ů��\n");
		}
		else if (month == 3 && day == 12)
		{
			printf("����������ֲ����\n");;
		}
		else if (month == 5 && day == 1)
		{
			printf("�����������Ͷ���\n");

		}
		else if (month == 6 && day == 1)
		{
			printf("���������Ƕ�ͯ��\n");
		}
		else if (month == 7 && day == 1)
		{
			printf("���������ǽ�����\n");
		}
		else if (month == 8 && day == 1)
		{
			printf("���������ǽ�����\n");
		}
		else if (month == 9 && day == 10)
		{
			printf("���������ǽ�ʦ��\n");
		}
		else if (month == 10 && day == 1)
		{
			printf("���������ǹ����\n");
		}
		else if (month == 12 && day == 24)
		{
			printf("����������ƽ��ҹ\n");
		}
		else if (month == 12 && day == 25)
		{
			printf("����������ʥ����\n");

		}

		//ũ������
		else if (lunar_m == 1 && lunar_d == 1) {
			printf("���������Ǵ���\n");
		}
		else if (lunar_m == 1 && lunar_d == 15) {
			printf("����������Ԫ����\n");
		}
		else if (lunar_m == 5 && lunar_d == 5) {
			printf("���������Ƕ����\n");
		}
		else if (lunar_m == 7 && lunar_d == 7) {
			printf("������������Ϧ��\n");
		}
		else if (lunar_m == 7 && lunar_d == 15) {
			printf("������������Ԫ��\n");
		}

		else if (lunar_m == 8 && lunar_d == 15) {
			printf("���������������\n");
		}
		else if (lunar_m == 9 && lunar_d == 9)
		{
			printf("����������������\n");
		}
		else if (lunar_m == 12 && lunar_d == 30) {
			printf("���������ǳ�Ϧ\n");
		}
		else
			printf("�������ڲ��ǽ���\n");

	}

}
