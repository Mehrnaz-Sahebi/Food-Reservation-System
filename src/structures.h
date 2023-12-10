#ifndef STRUCTURES_H
#define STRUCTURES_H

enum week{sunday,monday,tuesday,wednesday,thursday,friday,saturday};
enum user_type{student,admin};
enum food_type{main_course,dessert};
enum self_type{boyish,girlish};
enum meal_type{lunch,dinner};
enum reserve_type{before,daily};


typedef struct {
    long id;
    char password[30];
    char name[32];
    char family[32];
    char user_id[12];
    char national_id[12];
    char gender[6];
    int birthdate_year;
    int birthdate_month;
    int birthdate_day;
    int approved; //1 approved //0 waiting //-1 deactive
    int type;  //0 student //1 admin
    long charge;
} user;

typedef struct {
    long id;
    char food_id[12];
    char name[32];
    int type; //0 main course //1 desert
    long price;
} food;

typedef struct{
    long id;
    char self_id[12];
    char name[32];
    char place[32];
    int capacity;
    int type;  //0 boyish //1 girlish
    int lunch; //0 no //1 yes
    int lunch_start;
    int lunch_end;
    int dinner;  //0 no //1 yes
    int dinner_start;
    int dinner_end;
} self;

typedef struct{
    long id;
    char self_id[12];
    char food_id[12];
    int meal; //0 lunch //1 dinner
    int year;
    int month;
    int day;
    int amount;
    int remaining;
} mealplan;


typedef struct{
    long id;
    char title[100];
    char content[400];
    int end_year;
    int end_month;
    int end_day;
}news;

typedef struct{
    long id;
    char user_id[12];
    char reciever_id[12];
    char self_id[12];
    int mealplan_id;
    int year;
    int month;
    int day;
    int time;
    int type; //0 before //1 daily
}reserve;

typedef struct{
    long id;
    char question[400];
    char option1[200];
    char option2[200];
    char option3[200];
    char option4[200];
    int end_year;
    int end_month;
    int end_day;
}pole;

#endif //STRUCTURES_H
