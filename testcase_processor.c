#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>
#include <time.h>
#include "src/sqlite3.h"
#include "src/database.h"
#include "src/structures.h"
#include "Pages.h"
#include "testcase_processor.h"
#include "functions.h"


char usernames[100][12];
char last_username[12];
int flag[100]={0};
int iflag=0;

//CHECK
int check_sign_in(char* user_id){
for(int j=0;j<iflag;j++){
    if(strcmp(usernames[j],user_id)==0 && flag[j]==1){
        return 1;
    }
}
return 0;
}

//CHECK
void success(FILE* fpout){
fprintf(fpout,"%s\n","success");
return;
}
//CHECK
void not_found(FILE* fpout){
fprintf(fpout,"%s\n","not-found");
return;
}
//CHECK
void premission_denied(FILE* fpout){
fprintf(fpout,"%s\n","premission-denied");
return;
}
//CHECK
void invalid(FILE* fpout){
fprintf(fpout,"%s\n","invalid");
return;
}


void start(FILE* fpout,FILE* fpin){
int command_id;
char command[30];
char extra;
while(1){
    fscanf(fpin,"%d%*c%[^#||'\n']%c",&command_id,command,&extra);
    if(feof(fpin)){
        break;
    }
    if(strcmp(command,"login")==0){
        fprintf(fpout,"%d#",command_id);
        login(fpout,fpin);
    }
    else if(strcmp(command,"logout")==0){
        fprintf(fpout,"%d#",command_id);
        logout(fpout,fpin);
    }
    else if(strcmp(command,"change-pass")==0){
        fprintf(fpout,"%d#",command_id);
        change_pass(fpout,fpin);
    }
    else if(strcmp(command,"approve")==0){
        fprintf(fpout,"%d#",command_id);
        approve(fpout,fpin);
    }
    else if(strcmp(command,"change-student-pass")==0){
        fprintf(fpout,"%d#",command_id);
        change_student_pass(fpout,fpin);
    }
    else if(strcmp(command,"remove-student")==0){
        fprintf(fpout,"%d#",command_id);
        remove_student(fpout,fpin);
    }
    else if(strcmp(command,"deactivate")==0){
        fprintf(fpout,"%d#",command_id);
        deactivate(fpout,fpin);
    }
    else if(strcmp(command,"register")==0){
        fprintf(fpout,"%d#",command_id);
        Register(fpout,fpin);
    }
    else if(strcmp(command,"define-self")==0){
        fprintf(fpout,"%d#",command_id);
        define_self(fpout,fpin);
    }
    else if(strcmp(command,"define-food")==0){
        fprintf(fpout,"%d#",command_id);
        define_food(fpout,fpin);
    }
    else if(strcmp(command,"define-meal-plan")==0){
        fprintf(fpout,"%d#",command_id);
        define_mealplan(fpout,fpin);
    }
    else if(strcmp(command,"charge-student-account")==0){
        fprintf(fpout,"%d#",command_id);
        charge_student_account(fpout,fpin);
    }
    else if(strcmp(command,"add-news")==0){
        fprintf(fpout,"%d#",command_id);
        add_news(fpout,fpin);
    }
    else if(strcmp(command,"add-poll")==0){
        fprintf(fpout,"%d#",command_id);
        add_poll(fpout,fpin);
    }
    else if(strcmp(command,"reserve")==0){
        fprintf(fpout,"%d#",command_id);
        Reserve(fpout,fpin);
    }
    else if(strcmp(command,"take-food")==0){
        fprintf(fpout,"%d#",command_id);
        take_food(fpout,fpin);
    }
    else if(strcmp(command,"charge-account")==0){
        fprintf(fpout,"%d#",command_id);
        charge_account(fpout,fpin);
    }
    else if(strcmp(command,"send-charge")==0){
        fprintf(fpout,"%d#",command_id);
        send_charge(fpout,fpin);
    }
    else if(strcmp(command,"cancel-reserve")==0){
        fprintf(fpout,"%d#",command_id);
        cancel_reserve(fpout,fpin);
    }
    else if(strcmp(command,"daily-reserve")==0){
        fprintf(fpout,"%d#",command_id);
        daily_reserve(fpout,fpin);
    }
    else if(strcmp(command,"define-agent")==0){
        fprintf(fpout,"%d#",command_id);
        define_agent(fpout,fpin);
    }
    else if(strcmp(command,"change-self")==0){
        fprintf(fpout,"%d#",command_id);
        change_self(fpout,fpin);
    }
    else if(strcmp(command,"check-news")==0){
        fprintf(fpout,"%d#",command_id);
        check_news(fpout,fpin);
    }
    else if(strcmp(command,"vote")==0){
        fprintf(fpout,"%d#",command_id);
        vote(fpout,fpin);
    }
    else if(strcmp(command,"change-datetime")==0){
        fprintf(fpout,"%d#",command_id);
        change_date_time(fpout,fpin);
    }
    else{
        invalid(fpout);
    }

}
return;
}

//CHECK
void login(FILE* fpout,FILE* fpin){
char extra1[10];
char extra2[10];
char extra3;
char user_id[12];
char password[30];
if(fscanf(fpin,"%[^:]%c%[^|]%c%[^:]%c%[^\n]%c",extra1,&extra3,user_id,&extra3,extra2,&extra3,password,&extra3)!=8){
    invalid(fpout);
    return;
}
user* u;
u=get_user(user_id);
if (u==NULL){
    not_found(fpout);
    return;
}
if(strcmp(u->password,password)!=0){
    not_found(fpout);
    return;
}
if(strcmp(u->password,password)==0){
    if(u->approved==1){
        success(fpout);
        strcpy(usernames[iflag],user_id);
        strcpy(last_username,user_id);
        flag[iflag]=1;
        iflag++;
        return;
    }
    if(u->approved==0){
        premission_denied(fpout);
        return;
    }
    if(u->approved==-1){
        not_found(fpout);
        return;
    }
}
}

//CHECK
void logout(FILE* fpout,FILE* fpin){
char extra[10];
char extra1;
char user_id[12];
if(fscanf(fpin,"%[^:]%c%[^\n]%c",extra,&extra1,user_id,&extra1)!=4){
    invalid(fpout);
    return;
}
if(check_sign_in(user_id)){
    success(fpout);
    for(int j=0;j<iflag;j++){
        if(strcmp(usernames[j],user_id)==0){
            flag[j]=0;
            break;
        }
    }
    return;
}
not_found(fpout);
return;
}

//CHECK
void change_pass(FILE* fpout,FILE* fpin){
char extra1[30];
char extra3;
char user_id[12];
char old_password[30];
char new_password[30];
if(fscanf(fpin,"%[^:]%c%[^|]%c%[^:]%c%[^|]%c%[^:]%c%[^\n]%c",extra1,&extra3,user_id,&extra3,extra1,&extra3,old_password,&extra3,extra1,&extra3,new_password,&extra3)!=12){
    invalid(fpout);
    return;
}
if(check_sign_in(user_id)==0){
    not_found(fpout);
    return;
}
user* u=get_user(user_id);
if(strcmp(u->password,old_password)!=0){
    premission_denied(fpout);
    return;
}
change_user_password(user_id,new_password);
success(fpout);
return;
}

//CHECK
void approve(FILE* fpout,FILE* fpin){
char extra1[10];
char extra3;
char user_id[12];
int sign=0;
while(1){
    if(fscanf(fpin,"%[^:]%c%[^|||'\n']%c",extra1,&extra3,user_id,&extra3)!=4){
        invalid(fpout);
        return;
    }
    if(get_user(user_id)==NULL){
        sign=1;
    }
    else{
        change_user_approved(user_id,1);
    }
    if(extra3=='\n'){
        break;
    }
}
if(iflag==0){
    premission_denied(fpout);
    return;
}
if(is_admin(last_username)==0||check_sign_in(last_username)==0){
    premission_denied(fpout);
    return;
}
if(sign==1){
    not_found(fpout);
    return;
}
if(sign==0){
    success(fpout);
    return;
}
}


void change_student_pass(FILE* fpout,FILE* fpin){
char extra1[30];
char extra3;
char user_id[12];
char new_password[30];
if(fscanf(fpin,"%[^:]%c%[^|]%c%[^:]%c%[^\n]%c",extra1,&extra3,user_id,&extra3,extra1,&extra3,new_password,&extra3)!=8){
    invalid(fpout);
    return;
}
if(iflag==0){
    premission_denied(fpout);
    return;
}
if(is_admin(last_username)==0||check_sign_in(last_username)==0){
    premission_denied(fpout);
    return;
}
if(get_user(user_id)==NULL){
    not_found(fpout);
    return;
}
change_user_password(user_id,new_password);
success(fpout);
return;
}


void remove_student(FILE* fpout,FILE* fpin){
char extra[10];
char extra1;
char user_id[12];
if(fscanf(fpin,"%[^:]%c%[^\n]%c",extra,&extra1,user_id,&extra1)!=4){
    invalid(fpout);
    return;
}
if(iflag==0){
    premission_denied(fpout);
    return;
}
if(is_admin(last_username)==0||check_sign_in(last_username)==0){
    premission_denied(fpout);
    return;
}
if(get_user(user_id)==NULL){
    not_found(fpout);
    return;
}
delete_user(user_id);
success(fpout);
return;
}

void deactivate(FILE* fpout,FILE* fpin){
char extra[10];
char extra1;
char user_id[12];
if(fscanf(fpin,"%[^:]%c%[^\n]%c",extra,&extra1,user_id,&extra1)!=4){
    invalid(fpout);
    return;
}
if(iflag==0){
    premission_denied(fpout);
    return;
}
if(is_admin(last_username)==0||check_sign_in(last_username)==0){
    premission_denied(fpout);
    return;
}
if(get_user(user_id)==NULL){
    not_found(fpout);
    return;
}
change_user_approved(user_id,-1);
success(fpout);
return;
}

void Register(FILE* fpout,FILE* fpin){
char extra1[30];
char extra3;
char birthdate[10];
char type[7];
user u;
if(fscanf(fpin,"%[^:]%c%[^|]%c%[^:]%c%[^|]%c%[^:]%c%[^|]%c%[^:]%c%[^|]%c%[^:]%c%[^|]%c%[^:]%c%[^|]%c%[^:]%c%[^|]%c%[^:]%c%[^\n]%c",
          extra1,&extra3,u.name,&extra3,extra1,&extra3,u.family,&extra3,extra1,
          &extra3,u.user_id,&extra3,extra1,&extra3,u.password,&extra3,extra1,&extra3,u.national_id,&extra3,extra1,&extra3,birthdate,&extra3,extra1,
          &extra3,u.gender,&extra3,extra1,&extra3,type,&extra3)!=32){
    invalid(fpout);
    return;
}
sscanf(birthdate,"%d-%d-%d",&u.birthdate_year,&u.birthdate_month,&u.birthdate_day);
if(strcmp(type,"admin")==0){
    u.type=1;
}
else{
    u.type=0;
}
u.charge=0;
u.id=-1;
if(get_user(u.user_id)!=NULL){
    premission_denied(fpout);
    return;
}
if(iflag==0){
    u.approved=0;
    insert_user(&u);
    success(fpout);
    return;
}
if(check_sign_in(last_username)==0){
    u.approved=0;
    insert_user(&u);
    success(fpout);
    return;
}
if(check_sign_in(last_username)==1&&is_admin(last_username)){
    u.approved=1;
    insert_user(&u);
    success(fpout);
    return;
}
if(check_sign_in(last_username)==1&&is_admin(last_username)==0){
    premission_denied(fpout);
    return;
}
}

void define_self(FILE* fpout,FILE* fpin){
char extra1[30];
char extra3;
char type[7];
char meal[6];
int dinner_start;
int dinner_end;
int lunch_start;
int lunch_end;
self s;
fscanf(fpin," %[^:]%*c%[^|]%*c",extra1,s.self_id);
fscanf(fpin," %[^:]%*c%[^|]%*c",extra1,s.name);
fscanf(fpin," %[^:]%*c%[^|]%*c",extra1,s.place);
fscanf(fpin," %[^:]%*c%d%*c",extra1,&s.capacity);
fscanf(fpin," %[^:]%*c%[^|]%*c",extra1,type);
fscanf(fpin," %[^:]%*c%[^|]%*c",extra1,meal);
fscanf(fpin," %[^:]%*c%d-%d%*c",extra1,&lunch_start,&lunch_end);
fscanf(fpin," %[^:]%*c%d-%d%*c",extra1,&dinner_start,&dinner_end);
s.lunch_start=lunch_start;
s.lunch_end=lunch_end;
s.dinner_start=dinner_start;
s.dinner_end=dinner_end;
if(strcmpi(type,"boyish")==0){
    s.type=0;
}
else{
    s.type=1;
}
if(strcmpi(meal,"lunch")==0){
    s.lunch=1;
    s.dinner=0;
}
if(strcmpi(meal,"dinner")==0){
    s.lunch=0;
    s.dinner=1;
}if(strcmpi(meal,"both")==0){
    s.lunch=1;
    s.dinner=1;
}
s.id=-1;
if(get_self(s.self_id)!=NULL||iflag==0){
    premission_denied(fpout);
    return;
}
if(check_sign_in(last_username)&&is_admin(last_username)){
    insert_self(&s);
    success(fpout);
    return;
}
premission_denied(fpout);
return;

}


void define_food(FILE* fpout,FILE* fpin){
char extra1[60];
char extra3;
char type[7];
food f;
if(fscanf(fpin,"%[^:]%c%[^|]%c%[^:]%c%[^|]%c%[^:]%c%[^|]%c%[^:]%c%ld\n",
          extra1,&extra3,f.food_id,&extra3,extra1,&extra3,f.name,&extra3,extra1,
          &extra3,type,&extra3,extra1,&extra3,&f.price)!=15){
    invalid(fpout);
    return;
}
if(strcmpi(type,"dessert")==0){
    f.type=1;
}
else{
    f.type=0;
}
f.id=-1;
if(get_food(f.food_id)!=NULL||iflag==0){
    premission_denied(fpout);
    return;
}
if(check_sign_in(last_username)&&is_admin(last_username)){
    insert_food(&f);
    success(fpout);
    return;
}
premission_denied(fpout);
return;

}

void charge_student_account(FILE* fpout,FILE* fpin){
char extra1[60];
char extra3;
long amount;
char user_id[12];
if(fscanf(fpin,"%[^:]%c%[^|]%c%[^:]%c%ld\n",
          extra1,&extra3,user_id,&extra3,extra1,&extra3,&amount)!=7){
    invalid(fpout);
    return;
}
if(iflag==0){
    premission_denied(fpout);
    return;
}
if(is_admin(last_username)==0){
    premission_denied(fpout);
    return;
}
if(get_user(user_id)==NULL){
    not_found(fpout);
    return;
}
if(is_admin(last_username)&&check_sign_in(last_username)){
    increase_user_charge(user_id,amount);
    success(fpout);
    return;
}
}


void charge_account(FILE* fpout,FILE* fpin){
char extra1[60];
char extra3;
long amount;
if(fscanf(fpin,"%[^:]%c%ld|%[^:]%c%[^|]%c%[^:]%c%[^'\n']%c",
          extra1,&extra3,&amount,extra1,&extra3,extra1,&extra3,extra1,&extra3,extra1,&extra3)!=11){
    invalid(fpout);
    return;
}
if(iflag==0){
    premission_denied(fpout);
    return;
}
if(is_admin(last_username)==1||check_sign_in(last_username)==0){
    premission_denied(fpout);
    return;
}
increase_user_charge(last_username,amount);
success(fpout);
return;
}


void send_charge(FILE* fpout,FILE* fpin){
char extra1[60];
char extra3;
long amount;
char user_id[12];
char name[32];
if(fscanf(fpin,"%[^:]%c%[^|]%c%[^:]%c%ld|%[^:]%c%[^'\n']%c",
          extra1,&extra3,user_id,&extra3,extra1,&extra3,&amount,extra1,&extra3,name,&extra3)!=11){
    invalid(fpout);
    return;
}
if(iflag==0){
    premission_denied(fpout);
    return;
}
if(is_admin(last_username)==1||check_sign_in(last_username)==0){
    premission_denied(fpout);
    return;
}
user* u=get_user(user_id);
if(get_user(user_id)==NULL||get_user(user_id)!=NULL&&strcmpi(name,u->name)!=0){
    not_found(fpout);
    return;
}
u=get_user(last_username);
if((u->charge-amount)<0){
    premission_denied(fpout);
    return;
}

increase_user_charge(user_id,amount);
decrease_user_charge(last_username,amount);
success(fpout);
return;
}


void define_mealplan(FILE* fpout,FILE* fpin){
char extra1[30];
char extra3;
char meal[7];
mealplan m;
fscanf(fpin," %[^:]%*c%[^|]%*c",extra1,m.self_id);
fscanf(fpin," %[^:]%*c%d-%d-%d%*c",extra1,&m.year,&m.month,&m.day);
fscanf(fpin," %[^:]%*c%[^|]%*c",extra1,meal);
fscanf(fpin," %[^:]%*c%[^|]%*c",extra1,m.food_id);
fscanf(fpin," %[^:]%*c%d%*c",extra1,&m.amount);
//printf("%d-%d-%d\n",m.year,m.month,m.day);
if(iflag==0){
    premission_denied(fpout);
    return;
}
if(is_admin(last_username)==0||check_sign_in(last_username)==0){
    premission_denied(fpout);
    return;
}
if(get_food(m.food_id)==NULL||get_self(m.self_id)==NULL){
    not_found(fpout);
    return;
}
if(strcmpi(meal,"dinner")==0){
    m.meal=dinner;
}
if(strcmpi(meal,"lunch")==0){
    m.meal=lunch;
}
m.remaining=m.amount;
insert_mealplan(&m);
success(fpout);
return;
}


void add_news(FILE* fpout,FILE* fpin){
char extra1[30];
char extra3;
char title[200];
char content[400];
int year;
int month;
int day;
if(fscanf(fpin,"%[^:]%c %[^|]%c%[^:]%c %[^|]%c%[^:]%c%d-%d-%d\n",extra1,&extra3,title,&extra3,extra1,&extra3,content,&extra3,extra1,&extra3,&year,&month,&day)!=13){
    invalid(fpout);
    return;
}
if(iflag==0){
    premission_denied(fpout);
    return;
}
if(check_sign_in(last_username)==0||is_admin(last_username)==0){
    premission_denied(fpout);
    return;
}
news n;
strcpy(n.title,title);
strcpy(n.content,content);
n.end_day=day;
n.end_month=month;
n.end_year=year;
insert_news(&n);
success(fpout);
return;
}


void Reserve(FILE* fpout,FILE* fpin){
char extra1[60];
char extra3;
char type[7];
char self_id[12];
char food_id[12];
int year;
int month;
int day;
if(fscanf(fpin,"%[^:]%c%[^|]%c%[^:]%c%d-%d-%d|%[^:]%c%[^|]%c%[^:]%c%[^'\n']%c",
          extra1,&extra3,self_id,&extra3,extra1,&extra3,&year,&month,&day,extra1,&extra3,type,&extra3,extra1,&extra3,food_id,&extra3)!=17){
    invalid(fpout);
    return;
}
//printf("%d/%d/%d\n",year,month,day);
if(iflag==0){
    premission_denied(fpout);
    return;
}
if(is_admin(last_username)||check_sign_in(last_username)==0){
    premission_denied(fpout);
    return;
}
int meal;
if(strcmpi(type,"dinner")==0){
    meal=1;
}
if(strcmpi(type,"lunch")==0){
    meal=0;
}
int i=1;
mealplan* m=get_mealplan_using_ID(i);
user* u=get_user(last_username);
while(m!=NULL){
    //printf("%s,%d,%d,%d,%d,%d\n",m->self_id,m->year,m->month,m->day,m->remaining,m->meal);
    self* s=get_self(m->self_id);
    if(strcmp(m->self_id,self_id)==0&&m->year==year&&m->month==month&&m->day==day&&m->remaining>0&&meal==m->meal&&strcmp(m->food_id,food_id)==0){
        if(compare_date(year,month,day-3)<0||compare_date(year,month,day-14)>0||strcmpi("female",u->gender)==0&&s->type==boyish||strcmpi("male",u->gender)==0&&s->type==girlish){
            premission_denied(fpout);
            return;
        }
        else{

            food* f=get_food(m->food_id);
            reserve r;
            r.year=local->tm_year+1900;
            r.month=local->tm_mon+1;
            r.day=local->tm_mday;
            r.time=(local->tm_hour*100)+local->tm_min;
            r.mealplan_id=i;
            r.type=before;
            strcpy(r.user_id,last_username);
            strcpy(r.reciever_id,last_username);
            strcpy(r.self_id,m->self_id);
            if(can_reserve(r)==0){
                premission_denied(fpout);
                return;
            }
            if(can_reserve(r)==1){
                minusminus_mealplan_remaining(i);
                decrease_user_charge(last_username,f->price);
                insert_reserve(&r);
                success(fpout);
                return;
            }
        }
    }
    i++;
    m=get_mealplan_using_ID(i);
}
not_found(fpout);
return;


}


void daily_reserve(FILE* fpout,FILE* fpin){
char extra1[60];
char extra3;
char self_id[12];
char food_id[12];
if(fscanf(fpin,"%[^:]%c%[^|]%c%[^:]%c%[^'\n']%c",
          extra1,&extra3,self_id,&extra3,extra1,&extra3,food_id,&extra3)!=8){
    invalid(fpout);
    return;
}
if(iflag==0){
    premission_denied(fpout);
    return;
}
if(is_admin(last_username)||check_sign_in(last_username)==0){
    premission_denied(fpout);
    return;
}
int i=1;
mealplan* m=get_mealplan_using_ID(i);
while(m!=NULL){
    if(strcmp(m->food_id,food_id)==0&&strcmp(m->self_id,self_id)==0){
        self* s=get_self(self_id);
        food* f=get_food(food_id);
        int lunch_end=minus_time(s->lunch_end,30);
        int dinner_end=minus_time(s->dinner_end,30);
        if((compare_time(s->lunch_start)<=0&&compare_time(lunch_end)>=0&&m->meal==lunch&&m->remaining>0&&compare_date(m->year,m->month,m->day)==0)||
            (compare_time(s->dinner_start)<=0&&compare_time(dinner_end)>=0&&m->meal==dinner&&m->remaining>0&&compare_date(m->year,m->month,m->day)==0)){
            reserve r;
            r.day=local->tm_mday;
            r.month=local->tm_mon+1;
            r.year=local->tm_year+1900;
            r.mealplan_id=m->id;
            r.type=daily;
            r.time=(local->tm_hour*100)+(local->tm_min);
            strcpy((r.user_id),last_username);
            strcpy((r.reciever_id),last_username);
            strcpy((r.self_id),m->self_id);
            insert_reserve(&r);
            decrease_user_charge(last_username,2*(f->price));
            minusminus_mealplan_remaining(m->id);
            success(fpout);
            return;
        }
        else{
            premission_denied(fpout);
            return;
        }
    }
    i++;
    m=get_mealplan_using_ID(i);
}
not_found(fpout);
return;
}


void cancel_reserve(FILE* fpout,FILE* fpin){
char extra1[30];
char extra3;
char meal[6];
int year;
int month;
int day;
if(fscanf(fpin,"%[^:]%c%d-%d-%d%[^:]%c%[^\n]%c",extra1,&extra3,&year,&month,&day,extra1,&extra3,meal,&extra3)!=9){
    invalid(fpout);
    return;
}
int mmeal;
if(strcmpi(meal,"lunch")==0){
    mmeal=lunch;
}
if(strcmpi(meal,"dinner")==0){
    mmeal=dinner;
}
if(iflag==0){
    premission_denied(fpout);
    return;
}
if(is_admin(last_username)||check_sign_in(last_username)==0){
    premission_denied(fpout);
    return;
}
int i=1;
int j=0;
reserve* r=get_reserve_using_ID(i);
while(r!=NULL){
    mealplan* m=get_mealplan_using_ID(r->mealplan_id);
    food *f=get_food(m->food_id);
    self *s=get_self(r->self_id);
    if(m->year==year&&m->day==day&&m->month==month&&m->meal==mmeal&&strcmp(r->user_id,last_username)==0){
        if((compare_date(m->year,m->month,m->day)>0)||
       (compare_date(m->year,m->month,m->day)==0&&compare_time(minus_time(s->lunch_start,60))>=0&&m->meal==lunch)||
       (compare_date(m->year,m->month,m->day)==0&&compare_time(minus_time(s->dinner_start,60))>=0&&m->meal==dinner)
        ){
            reserve new_returned;
            strcpy(new_returned.user_id,last_username);
            strcpy(new_returned.reciever_id,last_username);
            strcpy(new_returned.self_id,r->self_id);
            new_returned.mealplan_id=r->mealplan_id;
            new_returned.year=local->tm_year+1900;
            new_returned.month=local->tm_mon+1;
            new_returned.day=local->tm_mday;
            new_returned.time=(local->tm_hour*100)+local->tm_min;
            new_returned.type==r->type;
            insert_returned(&new_returned);
            delete_reserve(i);
            increase_user_charge(new_returned.user_id,(0.9*(float)f->price));
            plusplus_mealplan_remaining(r->mealplan_id);
            j=1;
        }
        else{
            premission_denied(fpout);
            return;
        }
    }
    i++;
    r=get_reserve_using_ID(i);
}

if(j==0){
    not_found(fpout);
    return;
}
if(j==1){
    success(fpout);
    return;
}
}


void change_self(FILE* fpout,FILE* fpin){
char extra1[30];
char extra3;
char meal[6];
char new_self_id[12];
int year;
int month;
int day;
if(fscanf(fpin,"%[^:]%c%d-%d-%d%[^:]%c%[^|]%c%[^:]%c%[^\n]%c",extra1,&extra3,&year,&month,&day,extra1,&extra3,meal,&extra3,extra1,&extra3,new_self_id,
          &extra3)!=13){
    invalid(fpout);
    return;
}
int mmeal;
if(strcmpi(meal,"lunch")==0){
    mmeal=lunch;
}
if(strcmpi(meal,"dinner")==0){
    mmeal=dinner;
}
if(iflag==0){
    premission_denied(fpout);
    return;
}
if(is_admin(last_username)||check_sign_in(last_username)==0){
    premission_denied(fpout);
    return;
}
if(get_self(new_self_id)==NULL){
    not_found(fpout);
    return;
}
self *ns=get_self(new_self_id);
user* u=get_user(last_username);
if(!(ns->type==boyish&&strcmpi(u->gender,"male")==0||ns->type==girlish&&strcmpi(u->gender,"female")==0)){
    premission_denied(fpout);
    return;
}
int i=1;
reserve* r=get_reserve_using_ID(i);
while(r!=NULL){
    mealplan* m=get_mealplan_using_ID(r->mealplan_id);
    food *f=get_food(m->food_id);
    self *s=get_self(r->self_id);
    if(m->year==year&&m->day==day&&m->month==month&&m->meal==mmeal&&strcmp(r->user_id,last_username)==0){
        if((compare_date(m->year,m->month,m->day)>0)||
       (compare_date(m->year,m->month,m->day)==0&&compare_time(s->lunch_start-300)>=0&&m->meal==lunch)||
       (compare_date(m->year,m->month,m->day)==0&&compare_time(s->dinner_start-300)>=0&&m->meal==dinner)
       ){
            change_reserve_self_id(i,new_self_id);
            success(fpout);
            return;
        }
        else{
            premission_denied(fpout);
            return;
        }
    }
    i++;
    r=get_reserve_using_ID(i);
}
not_found(fpout);
return;
}



void take_food(FILE* fpout,FILE* fpin){
char extra1[60];
char extra3;
char meal[6];
char self_id[12];
int year;
int month;
int day;

if(fscanf(fpin,"%[^:]%c%[^|]%c%[^:]%c%d-%d-%d|%[^:]%c%[^'\n']%c",
          extra1,&extra3,self_id,&extra3,extra1,&extra3,&year,&month,&day,extra1,
          &extra3,meal,&extra3)!=13){
    invalid(fpout);
    return;
}
if(iflag==0){
    premission_denied(fpout);
    return;
}
if(is_admin(last_username)||check_sign_in(last_username)==0){
    premission_denied(fpout);
    return;
}
if(get_self(self_id)==NULL){
    not_found(fpout);
    return;
}
int mmeal;
if(strcmpi(meal,"dinner")==0){
    mmeal=1;
}
else{
    mmeal=0;
}
int i=1;
int j=1;
int t;
reserve* r =get_reserve_using_ID(i);
while(r!=NULL){
    mealplan* m=get_mealplan_using_ID(r->mealplan_id);
    if(strcmp(r->reciever_id,last_username)==0&&year==m->year&&day==m->day&&month==m->month&&m->meal==mmeal&&strcmp(self_id,r->self_id)==0){
        self* s=get_self(r->self_id);
        if(compare_time(s->lunch_start)<0&&compare_time(s->lunch_end)>0&&mmeal==lunch||compare_time(s->dinner_start)<0&&compare_time(s->dinner_end)>0&&mmeal==dinner){
            reserve new_taken;
            new_taken.year=local->tm_year+1900;
            new_taken.month=local->tm_mon+1;
            new_taken.day=local->tm_mday;
            new_taken.mealplan_id=r->mealplan_id;
            new_taken.type=r->type;
            strcpy(new_taken.user_id,r->user_id);
            strcpy(new_taken.reciever_id,r->reciever_id);
            strcpy(new_taken.self_id,r->self_id);
            new_taken.time=(local->tm_hour*100)+local->tm_min;
            insert_taken(&new_taken);
            delete_reserve(i);
            success(fpout);
            return;
        }
        else{
            premission_denied(fpout);
            return;
        }
    }
    i++;
    r=get_reserve_using_ID(i);
}
premission_denied(fpout);
return;
}

void define_agent(FILE* fpout,FILE* fpin){
char extra1[60];
char extra3;
char type[7];
char new_reciever[12];
int year;
int month;
int day;
if(fscanf(fpin,"%[^:]%c%d-%d-%d|%[^:]%c%[^|]%c%[^:]%c%[^'\n']%c",
          extra1,&extra3,&year,&month,&day,extra1,&extra3,type,&extra3,extra1,&extra3,new_reciever,&extra3)!=13){
    invalid(fpout);
    return;
}
if(iflag==0){
    premission_denied(fpout);
    return;
}
if(is_admin(last_username)||check_sign_in(last_username)==0){
    premission_denied(fpout);
    return;
}
if(get_user(new_reciever)==NULL){
    not_found(fpout);
    return;
}
int meal;
if(strcmpi(type,"dinner")==0){
    meal=1;
}
else{
    meal=0;
}
int i=1;
reserve* r=get_reserve_using_ID(i);
while(r!=NULL){
    mealplan* m=get_mealplan_using_ID(r->mealplan_id);
    self* s=get_self(r->self_id);
    if(m->meal==meal&&strcmp(last_username,r->user_id)==0&&year==m->year&&month==m->month&&day==m->day&&compare_date(year,month,day)==0&&(m->meal==dinner&&compare_time(s->dinner_start)>0||m->meal==lunch&&compare_time(s->lunch_start)>=0)||
       m->meal==meal&&strcmp(last_username,r->user_id)==0&&year==m->year&&month==m->month&&day==m->day&&compare_date(year,month,day)>0){
        change_reserve_reciever(i,new_reciever);
        success(fpout);
        return;
       }
    i++;
    r=get_reserve_using_ID(i);
}
not_found(fpout);
return;
}

void check_news(FILE* fpout,FILE* fpin){
if(iflag==0){
    premission_denied(fpout);
    return;
}
if(is_admin(last_username)||check_sign_in(last_username)==0){
    premission_denied(fpout);
    return;
}
int i=1;
news* n=get_news_using_ID(i);
while(n!=NULL){
    if(compare_date(n->end_year,n->end_month,n->end_day)>=0){
        success(fpout);
        return;
    }
    i++;
    n=get_news_using_ID(i);
}
not_found(fpout);
return;
}


void add_poll(FILE* fpout,FILE* fpin){
char extra1[30];
char extra3;
char option1[200];
char option2[200];
char option3[200];
char option4[200];
char question[400];
int year;
int month;
int day;
if(fscanf(fpin,"%[^:]%c %[^|]%c%[^:]%c %[^|]%c%[^:]%c %[^|]%c%[^:]%c %[^|]%c%[^:]%c %[^|]%c%[^:]%c%d-%d-%d\n",extra1,&extra3,question,&extra3,extra1,
&extra3,option1,&extra3,extra1,&extra3,option2,&extra3,extra1,&extra3,option3,&extra3,extra1,&extra3,option4,&extra3,extra1,&extra3,&year,&month,&day)!=25){
    invalid(fpout);
    return;
}
if(iflag==0){
    premission_denied(fpout);
    return;
}
if(check_sign_in(last_username)==0||is_admin(last_username)==0){
    premission_denied(fpout);
    return;
}
pole p;
strcpy(p.question,question);
strcpy(p.option1,option1);
strcpy(p.option2,option2);
strcpy(p.option3,option3);
strcpy(p.option4,option4);
p.end_day=day;
p.end_month=month;
p.end_year=year;
insert_pole(&p);
success(fpout);
return;
}


void vote(FILE* fpout,FILE* fpin){
if(iflag==0){
    premission_denied(fpout);
    return;
}
if(is_admin(last_username)||check_sign_in(last_username)==0){
    premission_denied(fpout);
    return;
}
int i=1;
pole* p=get_pole_using_ID(i);
while(p!=NULL){
    if(compare_date(p->end_year,p->end_month,p->end_day)>=0){
        success(fpout);
        return;
    }
    i++;
    p=get_pole_using_ID(i);
}
not_found(fpout);
return;
}

void change_date_time(FILE* fpout,FILE* fpin){
int year;
int month;
int day;
int time;
char extra[30];
if(fscanf(fpin,"%[^:]%*c%d-%d-%d%*c%[^:]%*c%d%*c",extra,&year,&month,&day,extra,&time)!=6){
    invalid(fpout);
    return;
}
change_date(year,month,day,1);
change_time(time/100,time%100);
success(fpout);
return;
}
