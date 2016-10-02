#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define GRN  "\x1B[32m"
#define YEL  "\x1B[33m"
#define RED  "\x1B[31m"
#define BLU  "\x1B[34m"
#define MAG  "\x1B[35m"
#define CYN  "\x1B[36m"
#define WHT  "\x1B[37m"
#define RESET  "\x1B[0m"
#define TRUE 1
#define CH '_'
#define MAXCH 51
#define MAXNO 91
#define LEAP_YEAR      (year % 4 == 0 && year % 100!= 0 || year % 400 == 0) 
/*=============================getting key code ==============================*/

int getkey(){

	char key;
	key = getchar();
		if(key == 'P');
			return 25;

		if(key == 'I')
			return 23;
		else 
			return 0;
	
} 
void printchar( char c){
	int i;
	printf( "\n\t");
	for( i = 0; i <= MAXCH ; i++)
		printf("%c",c);
	printf("\n");
}

/*============================ calculating first day of week =================================*/
int monthday[] = {31,28,31,30,31,30,31,31,30,31,30,31};
char *monthname[]={"January","February","March","April","May","June","July",
                "August","September","October","November","Decembeer"};
char *monthname1[]={"JAN","FEB","MAR","APR","MAY","JUN","JUL","AUG","SEP",
                        "OCT","NOV","DEC"};

int fm( int date, int month, int year){
	int leap, fmonth;
	if(year % 4 == 0 && year % 100!=0 || year % 400 == 0)
		leap = 1;
	else
		leap = 0;
	fmonth = 3 + ( 2- leap ) * ((month + 2) / (2 * month)) + ( 5 * month + month/9) /2;
	fmonth = fmonth % 7;
	return fmonth;
}
int firstday(int date, int month, int year){
	int firstday , yy , century;
	yy = year % 100;
	century = year / 100 ;
	firstday = 1.25 * yy + fm(date , month, year) + date - 2 * (century % 4);
	firstday = firstday % 7;
	return firstday;
}

/* ============= ==================to save calender file=============== ======*/
void savefile(int M,int y, int z){
	int i , j;
	char filename[12];
	char stryear[5];
	FILE *fp;
	strcpy(filename , monthname1[M - 1]);
	strcat(filename , stryear);
	strcat(filename,".txt");
	if((fp = fopen(filename,"w")) == NULL){
		printf("cannot create file\n");
		exit(1);
	}
	fprintf( fp, "\n\n\t\t%s%d\n\n\t", monthname[M - 1],y);
	for( i =1 ; i < MAXNO ; i++)
		fprintf(fp,"_");
	fprintf(fp,"\n");
	for( i =1 ; i <= z ; i++)
		fprintf(fp, "\t_");
	j = z;
	for( i =1 ; i <= monthday[M-1] ; i++){
		if( j++ % 7 == 0)
		fprintf(fp,"\n");
		fprintf( fp, "\t%2d", i);
		}
	fprintf(fp ,"\n\t");
	for( i=1 ; i <= MAXNO ; i++)
		fprintf( fp, "_");
		
	fclose(fp);
}
int main(){
	int monthday[] = {31,28,31,30,31,30,31,31,30,31,30,31};
	char *monthname[]={"January","February","March","April","May","June","July",
                "August","September","October","November","Decembeer"};
	
char *monthname1[]={"JAN","FEB","MAR","APR","MAY","JUN","JUL","AUG","SEP",
                        "OCT","NOV","DEC"};

	int month,year, i,j,z,keycode,k=1;
label: printf("calender\n");
	while( TRUE){

		printf("enter month in mm-yyyy format\n");
		scanf("%d-%d",&month,&year);
		if(year < 0){
			printf("invalid input\n");
			continue;
			}
		if(month >12 || month < 1){
			printf("invalid input\n");
			continue;
			}
		break;
		}
	do{
	/* ======calculate first day of week====*/

		 z = firstday( 1, month, year);
		printf("\n\n\t\t");
		printf("%s%d\n",monthname[month - 1],year);

	/*============= checking leap year or not==========*/

		monthday[1] = LEAP_YEAR ?29:28;

	/*=======output==========*/

		printchar(CH); 
		printf("\t");
		printf(YEL "SUN");
		printf(WHT"	MON	TUE	WED	THU	FRI	SAT");
		printchar(CH);
		/*=========== setting position======*/
		for( i = 1; i<=z ; i++)
			printf("\t-");
			j = z;
			k=0;
	/*========printing dates==========*/
		
		for( i =1 ;i <=monthday[month -1]; i++){
			//if( j++ %7 == 0){
			
		
			if(j++ % 7==0){
		
							
				printf("\n\t");
		
				printf("%2d",i );
				}
			
			else{
				printf("	%2d",i);
				//j++;
				} 
			}
		printchar(CH);
		printf("\n\n\t\t(*) use LEFT RIGHT UP DOWN arrow");
		printf("\n\n\t\t(*) press P to save calender");
		printf("\n\n\t\t(*) press I for new month and new year");
		printf("\n\n\t\t(*) press ESC to exit");
		keycode = getkey();

	/* ===== getting key code ====*/

		if ( keycode == 72)
			year++;
		if( keycode == 80 )
			year--;
		if( keycode == 77)
			month++;
			if( month > 12){
				month = 1;
				year++;
			}
		if( keycode == 75)
			month--;
			if( month < 1){
				month = 12;
				year--;
			}
		if(keycode == 25)
			savefile(month, year, z);
		if( keycode == 23)
			goto label;
			
	
	}while(keycode!=0);
	exit(0);
	return 0;
}

