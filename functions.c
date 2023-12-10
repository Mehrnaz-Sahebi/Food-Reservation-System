#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>
#include <time.h>
#include "functions.h"
#include "src/sqlite3.h"
#include "src/database.h"
#include "src/structures.h"


struct tm* local;
time_t t ;


void print_user(char* user_ID){
user* u=get_user(user_ID);
printf("%-34s%-34s%-14s%.4d.%-2d.%-2d%-8s%-14s%-32s",u->name,u->family,u->national_id,u->birthdate_year,u->birthdate_month,u->birthdate_day,u->gender,u->user_id,u->password);
if(u->approved==0){
    printf("%-22s","waiting for approval");
}
if(u->approved==-1){
    printf("%-22s","deactive");
}
if(u->approved==1){
    printf("%-22s","active");
}
if(u->type==1){
    printf("%-9s\n","admin");
}
if(u->type==0){
    printf("%-9s\n","student");
}
return;
}

void print_self(char* self_ID){
self* s=get_self(self_ID);
printf("%-14s%-34s%-34s",s->self_id,s->name,s->place);

if(s->dinner==1&&s->lunch==1){
    printf("%-15s","Both");
}
if(s->dinner==0&&s->lunch==1){
    printf("%-15s","Lunch");
}
if(s->dinner==1&&s->lunch==0){
    printf("%-15s","Dinner");
}
if(s->type==boyish){
    printf("%-8s\n","Boyish");
}
if(s->type==girlish){
    printf("%-8s\n","Girlish");
}
return;
}

void print_food(char* food_ID){
food* f=get_food(food_ID);
printf("%-14s%-34s%-15ld",f->food_id,f->name,f->price);

if((f->type)=dessert){
    printf("%-13s","dessert");
}
if((f->type)=main_course){
    printf("%-13s","Main course");
}
return;
}

void print_mealplan(int ID){
mealplan* m=get_mealplan_using_ID(ID);
printf("%s,%s,%d,%d,%d,%d,%d,%d,%d",m->self_id,m->food_id,m->amount,m->remaining,m->meal,m->year,m->month,m->day,m->id);
return;
}

//CHECK
int is_admin(char* user_ID){
user* u=get_user(user_ID);
return u->type;
}

//CHECK
void increase_user_charge(char* user_ID,long plus_charge){
user* u=get_user(user_ID);
long new_charge=(u->charge)+plus_charge;
change_user_charge(user_ID,new_charge);
return;
}

void decrease_user_charge(char* user_ID,long minus_charge){
user* u=get_user(user_ID);
long new_charge=(u->charge)-minus_charge;
change_user_charge(user_ID,new_charge);
return;
}

void decrease_mealplan_remaining(int ID,int minus_remaining){
mealplan* m=get_mealplan_using_ID(ID);
int new_remaining=(m->remaining)-minus_remaining;
change_mealplan_remaining(ID,new_remaining);
return;
}

void minusminus_mealplan_remaining(int ID){
mealplan* m=get_mealplan_using_ID(ID);
if(m->remaining>0){
    decrease_mealplan_remaining(ID,1);
}
return;
}

void plusplus_mealplan_remaining(int ID){
mealplan* m=get_mealplan_using_ID(ID);
decrease_mealplan_remaining(ID,-1);
return;
}


void change_time(int hour,int minute){
local->tm_hour=hour;
local->tm_min=minute;
return;
}

void change_date(int year,int month, int day,int weekday){
local->tm_year=year-1900;
local->tm_mon=month-1;
local->tm_mday=day;
local->tm_wday=weekday;
}

int compare_time(int t){
int hour=t/100;
int min=t%100;
if(local->tm_hour>hour){
    return -1;
}
if(local->tm_hour<hour){
    return 1;
}
if(local->tm_hour==hour){
    if(local->tm_min>min){
        return -1;
    }
    if(local->tm_min<min){
        return 1;
    }
}
return 0;
}


int compare_date(int year,int month,int day){
int currenty=local->tm_year+1900;
int currentm=local->tm_mon+1;
if(currenty>year){
    return -1;
}
if(currenty<year){
    return 1;
}
if(currenty==year){
    if(currentm>month){
        return -1;
    }
    if(currentm<month){
        return 1;
    }
    if(currentm==month){
        if(local->tm_mday>day){
            return -1;
        }
        if(local->tm_mday<day){
            return 1;
        }
    }
}
return 0;
}

int minus_time(int time, int minus){
int new_min=time%100;
int new_hour=time/100;
new_min-=minus;
if(new_min>0){
    new_hour--;
    new_min+=60;
}
return new_hour*100+new_min;
}

int can_reserve(reserve r){
mealplan* m=get_mealplan_using_ID(r.mealplan_id);
food* f=get_food(m->food_id);
int i=1;
reserve* r2=get_reserve_using_ID(i);
while(r2!=NULL){
    mealplan* m2=get_mealplan_using_ID(i);
    food* f2=get_food(m->food_id);
    user* u2=get_user(r2->user_id);
    if(m->year==m2->year&&m->month==m2->month&&m->day==m2->day&&m->meal==m2->meal&&strcmp(r.user_id,r2->user_id)==0&&u2->charge>=f2->price){
        /*if(strcmp(r.self_id,r2->self_id)==0)
            return 1;
        else
            return 0;
        */
        return 1;
    }
    i++;
    r2=get_reserve_using_ID(i);
}
return 1;
}


