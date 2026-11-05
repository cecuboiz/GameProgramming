#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <windows.h>
#include <ctype.h>
#include <string.h>     /* memset */
#define MAX_USER  4
#define MAX_QUEST 10
#define COLOR_BLUE  9    /* 밝은 파랑 */
#define COLOR_WHITE 15   /* 흰색 */
#define COLOR_GRAY  7    /* 기본 회색 */
double limit[MAX_QUEST];    /* ???? ???? */


void gotoxy(int x, int y);
void game_control(int order, char name[7], char sol[][10], double check[][10], int quest);
void display_result(int user, int order[], double check[][10], char name[][7], char sol[][10], int quest);
void display_rule(void);
int input_number(const char *msg, int min, int max);
void clear_input(void);
void clear_keys(void);  
void set_color(int color);
void print_flag(int f);
double choose_level(void);
void make_limits(double base, double limit[], int quest);
void draw_flags(int blue_up, int white_up);
int load_best(char name[], int *correct, double *time);
void save_best(const char *name, int correct, double time);

int main(void)
{
	
	int i, user_number, quest_number, rnd, temp;
	int order[4]={0, 1, 2, 3};
	char solution[4][10]={0};
	double time_check[4][10]={0};
	char user_name[4][7];
	char again;              
	srand(time(NULL));
	do {                                           /* < ?? */
		memset(solution, 0, sizeof(solution));     /* ?? ?? ??? */
		memset(time_check, 0, sizeof(time_check)); /* ?? ?? ??? */
		for(i=0;i<MAX_USER;i++) order[i]=i;        /* ?? 0,1,2,3 ?? */
		system("cls");


	printf("청기/백기 게임\n\n");
			char best_name[7];
		int best_cnt;
		double best_t;
		if (load_best(best_name, &best_cnt, &best_t))
		printf("현재 최고 기록 : %s님 (%d개 정답, %.2f초)\n\n", best_name, best_cnt, best_t);
		else
			printf("아직 최고 기록이 없습니다.\n\n");
	user_number = input_number("게임에 참가할 인원수를 임력하고 Enter(1~4)>", 1, MAX_USER);
	printf("\n");
	quest_number = input_number("문제의 개수를 입력하고 Enter(1~10)>", 1, MAX_QUEST);
	
	
	double base = choose_level();
make_limits(base, limit, quest_number);   /* 문제마다 5%씩 줄임 */

	for(i=0;i<user_number;i++)
	
	{
		printf("%d번 참가자의 이름을 입력하고 Enter>", i+1);
		scanf("%6s", user_name[i]);   /*max 6*//*drop rest*/
clear_input();                /* ?? ??? ?? */
	}
	printf("만약 한글을 사용하였다면 영문키로 바꾸십시오.\n");
	printf("아무키나 누르시오.\n");
	getch();
   printf("\n게임의 순서는 다음과 같습니다. \n");
   for(i=user_number-1;i>0;i--)     /* 뒤에서부터  */
{
    rnd=rand()%(i+1);            /* 0~i 중에서만 고름 */
    temp=order[i];
    order[i]=order[rnd];
    order[rnd]=temp;
}
   for(i=0;i<user_number;i++)
   {
	printf("%d번 : %s\n", i+1, user_name[order[i]]);
   }
   printf("아무키나 누르시오.\n");
   getch();

   for(i=0;i<user_number;i++)
	game_control(order[i], user_name[order[i]], solution, 
		time_check, quest_number);

   printf("\n\n");
   printf("모든 게임이 끝났습니다. \n");
   printf("아무키나 누르면 결과를 표시합니다. \n");
   getch();
   display_result(user_number, order, time_check, user_name, 
	solution, quest_number);
		clear_keys();
		printf("\n다시 하시겠습니까?  (y/n)>");
		again=tolower(getch());
	} while(again=='y');
   return 0;
}

void gotoxy(int x, int y)
{
      COORD Pos = {(SHORT)(x - 1), (SHORT)(y - 1)};
   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}
void game_control(int order, char name[7], char sol[][10], double check[][10], int quest)
{

int blue_up=0, white_up=0;     /* ← 추가: 처음엔 둘 다 내림 */
  const char *flag[]={"청기", "백기"};
   const char *question[]={"내려!", "올려!", "내리지말고", "올리지말고"};
   clock_t start, end;
   int i, rnd[4];
   char key;
   system("cls");
   gotoxy(1, 3);
   printf("%s님 순서입니다. 키 조작은 다음과 같습니다.", name);
   display_rule();
  clear_keys();   /* 기다리는 동안 누른 키 버리기 */
   for(i=0;i<quest;i++)
   {
  	system("cls");
	rnd[0]=rand()%2;
	rnd[1]=rand()%4;
		draw_flags(blue_up, white_up);   /* 현재 깃발 상태 */
	gotoxy(5, 8);
	printf("제한시간 %.2f초", limit[i]);
	start=clock();
	gotoxy(5, 10);
		printf("%d: ", i+1);
	print_flag(rnd[0]);                      /* 첫 번째 깃발 (색) */
	printf(" %s", question[rnd[1]]);
	if (rnd[1]>1)                            /* 두 부분 명령이면 */
	{
	       rnd[2]=rand()%2;
	       rnd[3]=rand()%2;
	       printf(" ");
	       print_flag(rnd[2]);               /* 두 번째 깃발 (색) */
	       printf(" %s", question[rnd[3]]);
	}
  	
    		key=0;                                        /* 0 = ?? ?? ? ?? */
	while (1) {
		if (kbhit()) {                            /* ?? ???? */
			key=tolower(getch());
			break;
		}
		if ((double)(clock()-start)/CLOCKS_PER_SEC >= limit[i])
			break;                                /* ???? ? > ?? ??? */
		Sleep(1);                                 /* CPU ?? ?? */
	}
	end=clock();
	if (key=='a') blue_up=1;          /* 청기 올려 */
	else if (key=='z') blue_up=0;     /* 청기 내려 */
	else if (key=='k') white_up=1;    /* 백기 올려 */
	else if (key=='m') white_up=0;    /* 백기 내려 */
	draw_flags(blue_up, white_up);    /* 누른 키대로 다시 그림 */
	check[order][i]=(double)(end-start)/CLOCKS_PER_SEC;
	if (rnd[1]>1)
	{
		if ((rnd[2]==0) && (rnd[3]==0) && (key=='z'))
			sol[order][i]=1;
		else if ((rnd[2]==0) && (rnd[3]==1) && (key=='a'))	
			sol[order][i]=1;
		else if ((rnd[2]==1) && (rnd[3]==0) && (key=='m'))	
			sol[order][i]=1;
		else if ((rnd[2]==1) && (rnd[3]==1) && (key=='k'))	
	                             sol[order][i]=1;
		else
			sol[order][i]=0;
	}
	else			
	{
		if ((rnd[0]==0) && (rnd[1]==0) && (key=='z'))
			sol[order][i]=1;
		else if ((rnd[0]==0) && (rnd[1]==1) && (key=='a'))	
			sol[order][i]=1;
		else if ((rnd[0]==1) && (rnd[1]==0) && (key=='m'))	
			sol[order][i]=1;
		else if ((rnd[0]==1) && (rnd[1]==1) && (key=='k'))	
			sol[order][i]=1;
		else
			sol[order][i]=0;
	}  		gotoxy(5, 14);
	if (check[order][i]>=limit[i]) {             /* ← 먼저 */
		printf("X 시간초과! (%.2f초)", check[order][i]);
		Beep(220, 300);
	}
	else if (!sol[order][i]) {                   /* ← 다음 */
		printf("X 오답! (%.2f초)", check[order][i]);
		Beep(220, 300);
	}
	else {
		printf("O 정답! (%.2f초)", check[order][i]);
		Beep(880, 120);
	}
	}
	
	Sleep(700);      /* 0.7초 보여 주기 */
	clear_keys();    /* 보는 동안 누른 키 버리기 */
    }        
          


void display_result(int user, int order[], double check[][10], char name[][7], char sol[][10], int quest)
{
   int i, j, k, best, tie=0, result[4]={0};
   double total_time[4]={0};
   system("cls");
   printf("%-10s", "");
   for(i=0;i<user;i++)
	printf("%-12s", name[order[i]]);
   printf("\n");
   for(j=0;j<quest;j++)
   {
	 printf("  %2d번    ", j+1);
	for(i=0;i<user;i++)
	{   
		if (sol[order[i]][j]  && check[order[i]][j]<limit[j])
		{
		printf("O ");
			result[order[i]]+=1;
		}
		else
			printf("X ");
		 printf("%-10.2f", check[order[i]][j]);
		if ((sol[order[i]][j]==1) && check[order[i]][j]<limit[j])
			total_time[order[i]]+=check[order[i]][j];
	}
	printf("\n");
   }
   printf("\n");
   printf("맞은개수  ");
   for(i=0;i<user;i++)
	 printf("%-12d", result[order[i]]);
   printf("\n");
   printf("소요시간  ");
   for(i=0;i<user;i++)
	  printf("%-12.2f", total_time[order[i]]);
   printf("\n");
        best=order[0];
   for(i=1;i<user;i++)
   {
       k=order[i];
       if (result[k]>result[best]) {          /* 더 많이 맞힘 → 교체 */
           best=k;
           tie=0;
       }
       else if (result[k]==result[best]) {    /* 맞은개수 같음 → 동점 */
           tie=1;
           if (total_time[k]<total_time[best])  /* 시간이 짧으면 교체 */
               best=k;
       }
   }
   if (tie)
         printf("\n우승 : %s님 (%d개 정답, %.2f초)\n", name[best], result[best], total_time[best]);

   char bn[7]; int bc; double bt;
   if (result[best]>0 &&
       (!load_best(bn, &bc, &bt)
        || result[best]>bc
        || (result[best]==bc && total_time[best]<bt))) {
       printf("*** 최고 기록 갱신! ***\n");
       save_best(name[best], result[best], total_time[best]);
   }
}

void display_rule(void)
{
	int i; 
	gotoxy(1,4);
	printf("게임시작전까지 키를 누르지 마세요!");
	gotoxy(1, 6);
print_flag(0); printf(" 올려 : a    "); print_flag(1); printf(" 올려 : k");
gotoxy(1, 7);
print_flag(0); printf(" 내려 : z    "); print_flag(1); printf(" 내려: m");
	Sleep(2000);
		gotoxy(1, 8);
	printf("곧 게임을 시작합니다. 준비하세요!");
	for(i=3;i>=1;i--) {
		gotoxy(5, 10);
		printf("%d   ", i);     /* 3 > 2 > 1 (?? ??? ????) */
		Beep(600, 150);         /* ? */
		Sleep(1000);            /* 1? */
	}
	gotoxy(5, 10);
	printf("시작!");
	Beep(1000, 300);            /* ? */

}
int input_number(const char *msg, int min, int max)
{
    int n;
    while (1) {
        printf("%s", msg);
        if (scanf("%d", &n) == 1 && n >= min && n <= max)
            return n;                       // з?в утга бол буцаана
        printf("%d~%d 사이의 숫자를 입력하세요.\n", min, max);
        while (getchar() != '\n');          // буруу оруулсан тэмдэгтийг хаяна
    }
}
void clear_input(void)
{
    while (getchar() != '\n');   /* ?? ??? Enter?? ?? */
}
void clear_keys(void)
{
    while (kbhit()) getch();   /* 버퍼에 남은 키를 모두 버름 */

}
void set_color(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
void print_flag(int f)
{
    if (f==0) { set_color(COLOR_BLUE);  printf("청기"); }
    else      { set_color(COLOR_WHITE); printf("백기"); }
    set_color(COLOR_GRAY);       /* 다시 기본색 */
}
double choose_level(void)
{
    int level=input_number("\n난이도(1:쉬움 1.5초, 2:보통 1.0초, 3:어려움 0.7초)>", 1, 3);
    if (level==1) return 1.5;
    else if (level==2) return 1.0;
    return 0.7;
}
void make_limits(double base, double limit[], int quest)
{
    int i;
    for(i=0;i<quest;i++)
        limit[i]=base*(1.0-0.05*i);   /* 1번 100%, 2번 95%, 3번 90% ... */
}
void draw_flags(int blue_up, int white_up)
{
    int y;
    for(y=16;y<=21;y++) {                 /* 깃대 + 이전 깃발 지우기 */
        gotoxy(10, y); printf("|      ");
        gotoxy(30, y); printf("|      ");
    }
    set_color(COLOR_BLUE);                /* 청기 */
    y = blue_up ? 16 : 20;                /* 올림이면 위, 내림이면 아래 */
    gotoxy(11, y);   printf("#####");
    gotoxy(11, y+1); printf("#####");
    set_color(COLOR_WHITE);               /* 백기 */
    y = white_up ? 16 : 20;
    gotoxy(31, y);   printf("#####");
    gotoxy(31, y+1); printf("#####");
    set_color(COLOR_GRAY);
    gotoxy(9, 22);  printf("청기");
    gotoxy(29, 22); printf("백기");
}
int load_best(char name[], int *correct, double *time)
{
    FILE *fp=fopen("best.txt", "r");          /* ?? ??? ?? */
    if (fp==NULL) return 0;                    /* ?? ?? = ?? ?? */
    int ok=(fscanf(fp, "%6s %d %lf", name, correct, time)==3);
    fclose(fp);
    return ok;                                 /* 3? ? ???? 1 */
}
void save_best(const char *name, int correct, double time)
{
    FILE *fp=fopen("best.txt", "w");          /* ?? ?? (????) */
    if (fp==NULL) return;
    fprintf(fp, "%s %d %.2f\n", name, correct, time);
    fclose(fp);
}
