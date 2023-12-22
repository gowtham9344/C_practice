#include <stdio.h>

static char daytab[2][13] = {
	{0,31,28,31,30,31,30,31,31,30,31,30,31},
	{0,31,29,31,30,31,30,31,31,30,31,30,31}
};

int day_of_year(int year,int month,int day){
	int i,leap;

	if(year < 0){
		printf("Year cannot be negative\n");
		return 0;
	}
	if(month <= 0){
		printf("month cannot be negative or zero\n");
		return 0;
	}
	if(day <= 0){
		printf("day cannot be negative or zero\n");
		return 0;
	}
	if(day >= 32){
		printf("day cannot be greater than 31\n");
		return 0;
	}
	if(month >= 13){
		printf("month cannot be greater than 12\n");
		return 0;
	}

	leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
        
	char* sub = *(daytab + leap);  
	char* temp = sub;
	for(;(temp-sub) < month;temp++){
		day += (*temp);
	}
	return day;
}

void month_day(int year ,int yearday, int* pmonth,int* pday){
	int i,leap;

	leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
	
	if(year < 0){
                printf("Year cannot be negative\n");
                return;
        }

	if(leap){
		if(yearday > 366 && yearday < 1){
			printf("yearday should be in between 1 to 366 for leap year");
			return;
		}
	}
	else{
		if(yearday > 365 && yearday < 1){
                        printf("yearday should be in between 1 to 365 for leap year");
                        return;
                }
	}

	char* sub = *(daytab + leap);
        char* temp = sub;

	for(;yearday > *temp;temp++)
		yearday -= (*temp);
	*pmonth = temp - sub;
	*pday = yearday;
}

int main(){
	int month = 11;
	int year = 2002;
	int day = 11;
	
	printf("The year day is %d\n",day_of_year(year,month,day));
	month_day(year,day_of_year(year,month,day),&month,&day);
	printf("The month day is %d day in %d month\n",day,month);
}
