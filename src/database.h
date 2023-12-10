#ifndef DATABASE_H
#define DATABASE_H
#include "structures.h"


void make_or_open_database();
void close_database();
void make_tables();
void make_food_table();
void make_user_table();
void make_self_table();
void make_mealplan_table();
void make_news_table();
void make_poles_table();
void make_reserve_table();
void make_taken_table();
void make_returned_table();
void insert_user(user*);
void insert_food(food *);
void insert_self(self *);
void insert_mealplan(mealplan *);
void insert_reserve(reserve *);
void insert_taken(reserve *);
void insert_returned(reserve *);
void insert_news(news *);
void insert_pole(pole *);
static int user_callback(void *, int, char **, char **);
static int food_callback(void *, int, char **, char **);
static int self_callback(void *, int, char **, char **);
static int mealplan_callback(void *, int, char **, char **);
static int reserve_callback(void *, int, char **, char **);
static int taken_callback(void *, int, char **, char **);
static int returned_callback(void *, int, char **, char **);
static int news_callback(void *, int, char **, char **);
static int pole_callback(void *, int, char **, char **);
user * get_user(const char *);
food * get_food(const char *);
self * get_self(const char *);


user* get_user_using_ID(int );
food* get_food_using_ID(int );
self* get_self_using_ID(int );
mealplan* get_mealplan_using_ID(int );
reserve* get_reserve_using_ID(int );
reserve* get_taken_using_ID(int );
reserve* get_returned_using_ID(int );
news* get_news_using_ID(int );
pole* get_pole_using_ID(int );


void change_user_password(char* ,char* );
void change_user_approved(char* ,int );
void change_user_charge(char*,long);
void change_reserve_reciever(int,char*);
void change_mealplan_remaining(int,int );
void change_reserve_self_id(int ,char*);


void delete_user(char* );
void delete_food(char* );
void delete_self(char* );
void delete_mealplan(char* );
void delete_reserve(int );
void delete_taken(int );
void delete_returned(int );
void delete_news(int );
void delete_pole(int );




#endif //DATABASE_H
