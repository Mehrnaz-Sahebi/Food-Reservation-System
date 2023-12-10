#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>
#include <time.h>
#include <stdbool.h>
#include "sqlite3.h"
#include "database.h"
#include "structures.h"
#include "../Pages.h"
#include "../testcase_processor.h"



const char DATABASE_FILE_NAME[] = "project_sqlite.db";
sqlite3 *db = NULL;


//CHECK
void make_user_table() {
    char *sql = "CREATE TABLE USERS("  \
      "ID INTEGER PRIMARY KEY     NOT NULL,"
      "PASSWORD       CHAR(30)    NOT NULL," \
      "NAME           CHAR(32)    NOT NULL," \
      "FAMILY         CHAR(32)    NOT NULL," \
      "USER_ID        CHAR(10)    NOT NULL," \
      "NATIONAL_ID    CHAR(12)    NOT NULL," \
      "GENDER         CHAR(8)     NOT NULL," \
      "BIRTHDATE_Y    INT         NOT NULL," \
      "BIRTHDATE_M    INT         NOT NULL," \
      "BIRTHDATE_D    INT         NOT NULL," \
      "APPROVED       INT         NOT NULL," \
      "TYPE           INT         NOT NULL," \
      "CHARGE         LONG        NOT NULL);";

    /* Execute SQL statement */
    char *db_error_message = NULL;
    int rc = sqlite3_exec(db, sql, NULL, NULL, &db_error_message);

    if (rc != SQLITE_OK) {
        //fprintf(stderr, "SQL error: %s\n", db_error_message);
        sqlite3_free(db_error_message);
        exit(1);
    }

    sql = "CREATE UNIQUE INDEX unique_user_id ON USERS (USER_ID);";
    rc = sqlite3_exec(db, sql, NULL, NULL, &db_error_message);

    if (rc != SQLITE_OK) {
        //fprintf(stderr, "SQL error: %s\n", db_error_message);
        sqlite3_free(db_error_message);
        exit(1);
    }
    //fprintf(stdout, "Table created successfully\n");
}

//CHECK
void make_food_table() {
    char *sql = "CREATE TABLE FOODS("  \
      "ID INTEGER PRIMARY KEY     NOT NULL," \
      "FOOD_ID        CHAR(12)    NOT NULL," \
      "NAME           CHAR(32)    NOT NULL," \
      "TYPE           INT         NOT NULL," \
      "PRICE          LONG        NOT NULL);";

    /* Execute SQL statement */
    char *db_error_message = NULL;
    int rc = sqlite3_exec(db, sql, NULL, NULL, &db_error_message);

    if (rc != SQLITE_OK) {
        //fprintf(stderr, "SQL error: %s\n", db_error_message);
        sqlite3_free(db_error_message);
        exit(1);
    }

    sql = "CREATE UNIQUE INDEX unique_food_id ON FOODS (FOOD_ID);";
    rc = sqlite3_exec(db, sql, NULL, NULL, &db_error_message);

    if (rc != SQLITE_OK) {
        //fprintf(stderr, "SQL error: %s\n", db_error_message);
        sqlite3_free(db_error_message);
        exit(1);
    }
    //fprintf(stdout, "Table created successfully\n");
}

//CHECK
void make_self_table() {
    char *sql = "CREATE TABLE SELFS("  \
      "ID INTEGER PRIMARY KEY     NOT NULL," \
      "SELF_ID        CHAR(12)    NOT NULL," \
      "NAME           CHAR(32)    NOT NULL," \
      "PLACE          CHAR(32)    NOT NULL," \
      "CAPACITY       INT         NOT NULL," \
      "TYPE           INT         NOT NULL," \
      "LUNCH          INT         NOT NULL," \
      "LUNCH_START    INT         NOT NULL," \
      "LUNCH_END      INT         NOT NULL," \
      "DINNER         INT         NOT NULL," \
      "DINNER_START   INT         NOT NULL," \
      "DINNER_END     INT         NOT NULL);";

    /* Execute SQL statement */
    char *db_error_message = NULL;
    int rc = sqlite3_exec(db, sql, NULL, NULL, &db_error_message);

    if (rc != SQLITE_OK) {
        //fprintf(stderr, "SQL error: %s\n", db_error_message);
        sqlite3_free(db_error_message);
        exit(1);
    }

    sql = "CREATE UNIQUE INDEX unique_self_id ON SELFS (SELF_ID);";
    rc = sqlite3_exec(db, sql, NULL, NULL, &db_error_message);

    if (rc != SQLITE_OK) {
        //fprintf(stderr, "SQL error: %s\n", db_error_message);
        sqlite3_free(db_error_message);
        exit(1);
    }
    //fprintf(stdout, "Table created successfully\n");
}

//CHECK
void make_mealplan_table() {
    char *sql = "CREATE TABLE MEALPLANS("  \
      "ID INTEGER PRIMARY KEY     NOT NULL," \
      "SELF_ID        CHAR(12)    NOT NULL," \
      "FOOD_ID        CHAR(12)    NOT NULL," \
      "MEAL           INT         NOT NULL," \
      "YEAR           INT         NOT NULL," \
      "MONTH          INT         NOT NULL," \
      "DAY            INT         NOT NULL," \
      "AMOUNT         INT         NOT NULL," \
      "REMAINING      INT         NOT NULL);";

    /* Execute SQL statement */
    char *db_error_message = NULL;
    int rc = sqlite3_exec(db, sql, NULL, NULL, &db_error_message);

    if (rc != SQLITE_OK) {
        //fprintf(stderr, "SQL error: %s\n", db_error_message);
        sqlite3_free(db_error_message);
        exit(1);
    }

    /*sql = "CREATE UNIQUE INDEX unique_meal_id ON MEALPLANS (MEALPLAN_ID);";
    rc = sqlite3_exec(db, sql, NULL, NULL, &db_error_message);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", db_error_message);
        sqlite3_free(db_error_message);
        exit(1);
    }
    fprintf(stdout, "Table created successfully\n");*/
}


void make_reserve_table() {
    char *sql = "CREATE TABLE RESERVES("
      "ID INTEGER PRIMARY KEY     NOT NULL," \
      "USER_ID        CHAR(12)    NOT NULL," \
      "RECIEVER_ID    CHAR(12)    NOT NULL," \
      "SELF_ID        CHAR(12)    NOT NULL," \
      "MEALPLAN_ID    INT         NOT NULL," \
      "YEAR           INT         NOT NULL," \
      "MONTH          INT         NOT NULL," \
      "DAY            INT         NOT NULL," \
      "TIME           INT         NOT NULL," \
      "TYPE           INT         NOT NULL);";

    /* Execute SQL statement */
    char *db_error_message = NULL;
    int rc = sqlite3_exec(db, sql, NULL, NULL, &db_error_message);

    if (rc != SQLITE_OK) {
        //fprintf(stderr, "SQL error: %s\n", db_error_message);
        sqlite3_free(db_error_message);
        exit(1);
    }

    /*sql = "CREATE UNIQUE INDEX unique_user_id ON USERS (USER_ID);";
    rc = sqlite3_exec(db, sql, NULL, NULL, &db_error_message);

    if (rc != SQLITE_OK) {
        //fprintf(stderr, "SQL error: %s\n", db_error_message);
        sqlite3_free(db_error_message);
        exit(1);
    }
    //fprintf(stdout, "Table created successfully\n");*/
}


void make_taken_table() {
    char *sql = "CREATE TABLE TAKENS("  \
      "ID INTEGER PRIMARY KEY     NOT NULL," \
      "USER_ID        CHAR(12)    NOT NULL," \
      "RECIEVER_ID    CHAR(12)    NOT NULL," \
      "SELF_ID        CHAR(12)    NOT NULL," \
      "MEALPLAN_ID    INT         NOT NULL," \
      "YEAR           INT         NOT NULL," \
      "MONTH          INT         NOT NULL," \
      "DAY            INT         NOT NULL," \
      "TIME           INT         NOT NULL," \
      "TYPE           INT         NOT NULL);";

    /* Execute SQL statement */
    char *db_error_message = NULL;
    int rc = sqlite3_exec(db, sql, NULL, NULL, &db_error_message);

    if (rc != SQLITE_OK) {
        //fprintf(stderr, "SQL error: %s\n", db_error_message);
        sqlite3_free(db_error_message);
        exit(1);
    }

    /*sql = "CREATE UNIQUE INDEX unique_user_id ON USERS (USER_ID);";
    rc = sqlite3_exec(db, sql, NULL, NULL, &db_error_message);

    if (rc != SQLITE_OK) {
        //fprintf(stderr, "SQL error: %s\n", db_error_message);
        sqlite3_free(db_error_message);
        exit(1);
    }
    //fprintf(stdout, "Table created successfully\n");*/
}


void make_returned_table() {
    char *sql = "CREATE TABLE RETURNEDS("  \
      "ID INTEGER PRIMARY KEY     NOT NULL," \
      "USER_ID        CHAR(12)    NOT NULL," \
      "RECIEVER_ID    CHAR(12)    NOT NULL," \
      "SELF_ID        CHAR(12)    NOT NULL," \
      "MEALPLAN_ID    INT         NOT NULL," \
      "YEAR           INT         NOT NULL," \
      "MONTH          INT         NOT NULL," \
      "DAY            INT         NOT NULL," \
      "TIME           INT         NOT NULL," \
      "TYPE           INT         NOT NULL);";

    /* Execute SQL statement */
    char *db_error_message = NULL;
    int rc = sqlite3_exec(db, sql, NULL, NULL, &db_error_message);

    if (rc != SQLITE_OK) {
        //fprintf(stderr, "SQL error: %s\n", db_error_message);
        sqlite3_free(db_error_message);
        exit(1);
    }

    /*sql = "CREATE UNIQUE INDEX unique_user_id ON USERS (USER_ID);";
    rc = sqlite3_exec(db, sql, NULL, NULL, &db_error_message);

    if (rc != SQLITE_OK) {
        //fprintf(stderr, "SQL error: %s\n", db_error_message);
        sqlite3_free(db_error_message);
        exit(1);
    }
    //fprintf(stdout, "Table created successfully\n");*/
}


void make_news_table() {
    char *sql = "CREATE TABLE NEWS("  \
      "ID INTEGER PRIMARY KEY     NOT NULL," \
      "TITLE          CHAR(100)   NOT NULL," \
      "CONTENT        CHAR(400)   NOT NULL," \
      "END_YEAR       INT         NOT NULL," \
      "END_MONTH      INT         NOT NULL," \
      "END_DAY        INT         NOT NULL);";

    /* Execute SQL statement */
    char *db_error_message = NULL;
    int rc = sqlite3_exec(db, sql, NULL, NULL, &db_error_message);

    if (rc != SQLITE_OK) {
        //fprintf(stderr, "SQL error: %s\n", db_error_message);
        sqlite3_free(db_error_message);
        exit(1);
    }

    /*sql = "CREATE UNIQUE INDEX unique_user_id ON USERS (USER_ID);";
    rc = sqlite3_exec(db, sql, NULL, NULL, &db_error_message);

    if (rc != SQLITE_OK) {
        //fprintf(stderr, "SQL error: %s\n", db_error_message);
        sqlite3_free(db_error_message);
        exit(1);
    }
    //fprintf(stdout, "Table created successfully\n");*/
}


void make_poles_table() {
    char *sql = "CREATE TABLE POLES("  \
      "ID                INTEGER PRIMARY KEY      NOT NULL," \
      "QUESTION          CHAR(400)                NOT NULL," \
      "OPTION1           CHAR(200)                NOT NULL," \
      "OPTION2           CHAR(200)                NOT NULL," \
      "OPTION3           CHAR(200)                NOT NULL," \
      "OPTION4           CHAR(200)                NOT NULL," \
      "END_YEAR          INT                      NOT NULL," \
      "END_MONTH         INT                      NOT NULL," \
      "END_DAY           INT                      NOT NULL);";

    /* Execute SQL statement */
    char *db_error_message = NULL;
    int rc = sqlite3_exec(db, sql, NULL, NULL, &db_error_message);

    if (rc != SQLITE_OK) {
        //fprintf(stderr, "SQL error: %s\n", db_error_message);
        sqlite3_free(db_error_message);
        exit(1);
    }

    /*sql = "CREATE UNIQUE INDEX unique_user_id ON USERS (USER_ID);";
    rc = sqlite3_exec(db, sql, NULL, NULL, &db_error_message);

    if (rc != SQLITE_OK) {
        //fprintf(stderr, "SQL error: %s\n", db_error_message);
        sqlite3_free(db_error_message);
        exit(1);
    }
    //fprintf(stdout, "Table created successfully\n");*/
}


//CHECK
void make_tables() {
    make_user_table();
    make_food_table();
    make_self_table();
    make_mealplan_table();
    make_news_table();
    make_reserve_table();
    make_taken_table();
    make_returned_table();
    make_poles_table();
}

//CHECK
void insert_user(user *new_user) {
    char sql[512];
    char *db_error_message = NULL;
    sprintf(sql, "INSERT INTO USERS (PASSWORD, NAME, FAMILY, USER_ID, NATIONAL_ID, GENDER,BIRTHDATE_Y,"
                 "BIRTHDATE_M, BIRTHDATE_D, APPROVED, TYPE, CHARGE) VALUES ('%s' , '%s' , '%s','%s','%s','%s','%d','%d','%d','%d','%d','%ld');",
            new_user->password, new_user->name, new_user->family, new_user->user_id, new_user->national_id,
            new_user->gender, new_user->birthdate_year, new_user->birthdate_month,
            new_user->birthdate_day, new_user->approved, new_user->type, new_user->charge);
    int rc = sqlite3_exec(db, sql, NULL, NULL, &db_error_message);

    if (rc != SQLITE_OK) {
        //fprintf(stderr, "SQL error: %s\n", db_error_message);
        sqlite3_free(db_error_message);
        return;
    }
    new_user->id = sqlite3_last_insert_rowid(db);
    //fprintf(stdout, "User created successfully\n");
}

//CHECK
void insert_food(food *new_food) {
    char sql[512];
    char *db_error_message = NULL;
    sprintf(sql, "INSERT INTO FOODS (FOOD_ID, NAME, TYPE, PRICE) VALUES ('%s','%s','%d','%ld');",
            new_food->food_id, new_food->name, new_food->type, new_food->price);
    int rc = sqlite3_exec(db, sql, NULL, NULL, &db_error_message);

    if (rc != SQLITE_OK) {
        //fprintf(stderr, "SQL error: %s\n", db_error_message);
        sqlite3_free(db_error_message);
        return;
    }
    new_food->id = sqlite3_last_insert_rowid(db);
    //fprintf(stdout, "FOOD created successfully\n");
}

//CHECK
void insert_self(self *new_self) {
    char sql[512];
    char *db_error_message = NULL;
    sprintf(sql, "INSERT INTO SELFS (SELF_ID, NAME, PLACE, CAPACITY, TYPE, LUNCH, LUNCH_START,LUNCH_END, DINNER, DINNER_START, DINNER_END)"
            " VALUES ('%s','%s','%s','%d','%d','%d','%d','%d','%d','%d','%d');",
            new_self->self_id, new_self->name, new_self->place, new_self->capacity, new_self->type,new_self->lunch, new_self->lunch_start,
            new_self->lunch_end, new_self->dinner, new_self->dinner_start, new_self->dinner_end);
    int rc = sqlite3_exec(db, sql, NULL, NULL, &db_error_message);

    if (rc != SQLITE_OK) {
        //fprintf(stderr, "SQL error: %s\n", db_error_message);
        sqlite3_free(db_error_message);
        return;
    }
    new_self->id = sqlite3_last_insert_rowid(db);
    //fprintf(stdout, "SELF created successfully\n");
}

//CHECK
void insert_mealplan(mealplan *new_mealplan) {
    char sql[512];
    char *db_error_message = NULL;
    sprintf(sql, "INSERT INTO MEALPLANS ( SELF_ID, FOOD_ID, MEAL, YEAR, MONTH, DAY, AMOUNT, REMAINING)"
            " VALUES ('%s','%s','%d','%d','%d','%d','%d','%d');",
            new_mealplan->self_id, new_mealplan->food_id, new_mealplan->meal, new_mealplan->year,
            new_mealplan->month,new_mealplan->day, new_mealplan->amount, new_mealplan->remaining);
    int rc = sqlite3_exec(db, sql, NULL, NULL, &db_error_message);

    if (rc != SQLITE_OK) {
        //fprintf(stderr, "SQL error: %s\n", db_error_message);
        sqlite3_free(db_error_message);
        return;
    }
    new_mealplan->id = sqlite3_last_insert_rowid(db);
    //fprintf(stdout, "MEALPLAN created successfully\n");
}


void insert_reserve(reserve* new_reserve){
char sql[512];
    char *db_error_message = NULL;
    sprintf(sql, "INSERT INTO RESERVES (USER_ID, RECIEVER_ID, SELF_ID, MEALPLAN_ID, YEAR, MONTH, DAY, TIME, TYPE) VALUES ('%s','%s','%s','%d','%d','%d','%d','%d','%d');",
            new_reserve->user_id ,new_reserve->reciever_id , new_reserve->self_id, new_reserve->mealplan_id, new_reserve->year, new_reserve->month, new_reserve->day,
            new_reserve->time, new_reserve->type);
    int rc = sqlite3_exec(db, sql, NULL, NULL, &db_error_message);

    if (rc != SQLITE_OK) {
        //fprintf(stderr, "SQL error: %s\n", db_error_message);
        sqlite3_free(db_error_message);
        return;
    }
    new_reserve->id = sqlite3_last_insert_rowid(db);
    //fprintf(stdout, "Reserve created successfully\n");
}


void insert_taken(reserve* new_taken){
char sql[512];
    char *db_error_message = NULL;
    sprintf(sql, "INSERT INTO TAKENS (USER_ID, RECIEVER_ID, SELF_ID, MEALPLAN_ID, YEAR, MONTH, DAY, TIME, TYPE) VALUES ('%s','%s','%s','%d','%d','%d','%d','%d','%d');",
            new_taken->user_id ,new_taken->reciever_id,new_taken->self_id, new_taken->mealplan_id, new_taken->year, new_taken->month, new_taken->day,
            new_taken->time, new_taken->type);
    int rc = sqlite3_exec(db, sql, NULL, NULL, &db_error_message);

    if (rc != SQLITE_OK) {
        //fprintf(stderr, "SQL error: %s\n", db_error_message);
        sqlite3_free(db_error_message);
        return;
    }
    new_taken->id = sqlite3_last_insert_rowid(db);
    //fprintf(stdout, "TAKEN created successfully\n");
}


void insert_returned(reserve* new_returned){
char sql[512];
    char *db_error_message = NULL;
    sprintf(sql, "INSERT INTO RETURNEDS (USER_ID, RECIEVER_ID, SELF_ID, MEALPLAN_ID, YEAR, MONTH, DAY, TIME, TYPE) VALUES ('%s','%s','%s','%d','%d','%d','%d','%d','%d');",
            new_returned->user_id ,new_returned->reciever_id,new_returned->self_id, new_returned->mealplan_id, new_returned->year, new_returned->month, new_returned->day,
            new_returned->time, new_returned->type);
    int rc = sqlite3_exec(db, sql, NULL, NULL, &db_error_message);

    if (rc != SQLITE_OK) {
        //fprintf(stderr, "SQL error: %s\n", db_error_message);
        sqlite3_free(db_error_message);
        return;
    }
    new_returned->id = sqlite3_last_insert_rowid(db);
    //fprintf(stdout, "RETURNED created successfully\n");
}


void insert_news(news* new_news){
char sql[512];
    char *db_error_message = NULL;
    sprintf(sql, "INSERT INTO NEWS (TITLE, CONTENT, END_YEAR, END_MONTH, END_DAY) VALUES ('%s','%s','%d','%d','%d');",
            new_news->title ,new_news->content , new_news->end_year, new_news->end_month, new_news->end_day);
    int rc = sqlite3_exec(db, sql, NULL, NULL, &db_error_message);

    if (rc != SQLITE_OK) {
        //fprintf(stderr, "SQL error: %s\n", db_error_message);
        sqlite3_free(db_error_message);
        return;
    }
    new_news->id = sqlite3_last_insert_rowid(db);
    //fprintf(stdout, "NEWS created successfully\n");
}


void insert_pole(pole* new_pole){
char sql[512];
    char *db_error_message = NULL;
    sprintf(sql, "INSERT INTO POLES (QUESTION, OPTION1, OPTION2, OPTION3, OPTION4, END_YEAR, END_MONTH, END_DAY) VALUES ('%s','%s','%s','%s','%s','%d','%d','%d');",
            new_pole->question ,new_pole->option1 , new_pole->option2, new_pole->option3,new_pole->option4, new_pole->end_year , new_pole->end_month, new_pole->end_day);
    int rc = sqlite3_exec(db, sql, NULL, NULL, &db_error_message);

    if (rc != SQLITE_OK) {
        //fprintf(stderr, "SQL error: %s\n", db_error_message);
        sqlite3_free(db_error_message);
        return;
    }
    new_pole->id = sqlite3_last_insert_rowid(db);
    //fprintf(stdout, "POLE created successfully\n");
}


//CHECK
static int user_callback(void *data, int argc, char **argv, char **not_used) {
    if (argc != 13) {
        //printf("Error in getting a user info from the database!");
        return 1;
    }
    user *fetched_user = (user *) data;
    char *ptr;
    fetched_user->id = strtol(argv[0], &ptr, 10);
    strcpy(fetched_user->password, argv[1]);
    strcpy(fetched_user->name, argv[2]);
    strcpy(fetched_user->family, argv[3]);
    strcpy(fetched_user->user_id, argv[4]);
    strcpy(fetched_user->national_id, argv[5]);
    strcpy(fetched_user->gender, argv[6]);
    fetched_user->birthdate_year = (int)strtol(argv[7], &ptr, 10);
    fetched_user->birthdate_month = (int)strtol(argv[8], &ptr, 10);
    fetched_user->birthdate_day = (int)strtol(argv[9], &ptr, 10);
    fetched_user->approved = (int)strtol(argv[10], &ptr, 10);
    fetched_user->type = (int)strtol(argv[11], &ptr, 10);
    fetched_user->charge = (long)strtol(argv[12], &ptr, 10);
    return 0;
}

//CHECK
static int food_callback(void *data, int argc, char **argv, char **not_used) {
    if (argc != 5) {
        //printf("Error in getting a food info from the database!");
        return 1;
    }
    food *fetched_food = (food *) data;
    char *ptr;
    fetched_food->id = strtol(argv[0], &ptr, 10);
    strcpy(fetched_food->food_id, argv[1]);
    strcpy(fetched_food->name, argv[2]);
    fetched_food->type = (int)strtol(argv[3], &ptr, 10);
    fetched_food->price = (long)strtol(argv[4], &ptr, 10);
    return 0;
}

//CHECK
static int self_callback(void *data, int argc, char **argv, char **not_used) {
    if (argc != 12) {
        //printf("Error in getting a self info from the database!");
        return 1;
    }
    self *fetched_self = (self *) data;
    char *ptr;
    fetched_self->id = strtol(argv[0], &ptr, 10);
    strcpy(fetched_self->self_id, argv[1]);
    strcpy(fetched_self->name, argv[2]);
    strcpy(fetched_self->place, argv[3]);
    fetched_self->capacity = (int)strtol(argv[4], &ptr, 10);
    fetched_self->type = (int)strtol(argv[5], &ptr, 10);
    fetched_self->lunch = (int)strtol(argv[6], &ptr, 10);
    fetched_self->lunch_start = (int)strtol(argv[7], &ptr, 10);
    fetched_self->lunch_end = (int)strtol(argv[8], &ptr, 10);
    fetched_self->dinner = (int)strtol(argv[9], &ptr, 10);
    fetched_self->dinner_start = (int)strtol(argv[10], &ptr, 10);
    fetched_self->dinner_end = (int)strtol(argv[11], &ptr, 10);
    return 0;
}

//CHECK
static int mealplan_callback(void *data, int argc, char **argv, char **not_used) {
    if (argc != 9) {
        //printf("Error in getting a mealplan info from the database!");
        return 1;
    }
    mealplan *fetched_mealplan = (mealplan *) data;
    char *ptr;
    fetched_mealplan->id = strtol(argv[0], &ptr, 10);
    strcpy(fetched_mealplan->self_id, argv[1]);
    strcpy(fetched_mealplan->food_id, argv[2]);
    fetched_mealplan->meal = (int)strtol(argv[3], &ptr, 10);
    fetched_mealplan->year = (int)strtol(argv[4], &ptr, 10);
    fetched_mealplan->month = (int)strtol(argv[5], &ptr, 10);
    fetched_mealplan->day = (int)strtol(argv[6], &ptr, 10);
    fetched_mealplan->amount = (int)strtol(argv[7], &ptr, 10);
    fetched_mealplan->remaining = (int)strtol(argv[8], &ptr, 10);
    return 0;
}


static int reserve_callback(void *data, int argc, char **argv, char **not_used) {
    if (argc != 10) {
        //printf("Error in getting a reserve info from the database!");
        return 1;
    }
    reserve *fetched_reserve = (reserve *) data;
    char *ptr;
    fetched_reserve->id = strtol(argv[0], &ptr, 10);
    strcpy(fetched_reserve->user_id, argv[1]);
    strcpy(fetched_reserve->reciever_id, argv[2]);
    strcpy(fetched_reserve->self_id, argv[3]);
    fetched_reserve->mealplan_id = (int)strtol(argv[4], &ptr, 10);
    fetched_reserve->year = (int)strtol(argv[5], &ptr, 10);
    fetched_reserve->month = (int)strtol(argv[6], &ptr, 10);
    fetched_reserve->day = (int)strtol(argv[7], &ptr, 10);
    fetched_reserve->time = (int)strtol(argv[8], &ptr, 10);
    fetched_reserve->type = (int)strtol(argv[9], &ptr, 10);
    return 0;
}


static int taken_callback(void *data, int argc, char **argv, char **not_used) {
    if (argc != 10) {
        //printf("Error in getting a taken info from the database!");
        return 1;
    }
    reserve *fetched_taken = (reserve *) data;
    char *ptr;
    fetched_taken->id = strtol(argv[0], &ptr, 10);
    strcpy(fetched_taken->user_id, argv[1]);
    strcpy(fetched_taken->reciever_id, argv[2]);
    strcpy(fetched_taken->self_id, argv[3]);
    fetched_taken->mealplan_id = (int)strtol(argv[4], &ptr, 10);
    fetched_taken->year = (int)strtol(argv[5], &ptr, 10);
    fetched_taken->month = (int)strtol(argv[6], &ptr, 10);
    fetched_taken->day = (int)strtol(argv[7], &ptr, 10);
    fetched_taken->time = (int)strtol(argv[8], &ptr, 10);
    fetched_taken->type = (int)strtol(argv[9], &ptr, 10);
    return 0;
}


static int returned_callback(void *data, int argc, char **argv, char **not_used) {
    if (argc != 10) {
        //printf("Error in getting a returned info from the database!");
        return 1;
    }
    reserve *fetched_returned = (reserve *) data;
    char *ptr;
    fetched_returned->id = strtol(argv[0], &ptr, 10);
    strcpy(fetched_returned->user_id, argv[1]);
    strcpy(fetched_returned->reciever_id, argv[2]);
    strcpy(fetched_returned->self_id, argv[3]);
    fetched_returned->mealplan_id = (int)strtol(argv[4], &ptr, 10);
    fetched_returned->year = (int)strtol(argv[5], &ptr, 10);
    fetched_returned->month = (int)strtol(argv[6], &ptr, 10);
    fetched_returned->day = (int)strtol(argv[7], &ptr, 10);
    fetched_returned->time = (int)strtol(argv[8], &ptr, 10);
    fetched_returned->type = (int)strtol(argv[9], &ptr, 10);
    return 0;
}


static int news_callback(void *data, int argc, char **argv, char **not_used) {
    if (argc != 6) {
        //printf("Error in getting a news info from the database!");
        return 1;
    }
    news *fetched_news= (news *) data;
    char *ptr;
    fetched_news->id = strtol(argv[0], &ptr, 10);
    strcpy(fetched_news->title, argv[1]);
    strcpy(fetched_news->content, argv[2]);
    fetched_news->end_year = (int)strtol(argv[3], &ptr, 10);
    fetched_news->end_month = (int)strtol(argv[4], &ptr, 10);
    fetched_news->end_day = (int)strtol(argv[5], &ptr, 10);
    return 0;
}


static int pole_callback(void *data, int argc, char **argv, char **not_used) {
    if (argc != 9) {
        //printf("Error in getting a pole info from the database!");
        return 1;
    }
    pole *fetched_pole= (pole *) data;
    char *ptr;
    fetched_pole->id = strtol(argv[0], &ptr, 10);
    strcpy(fetched_pole->question, argv[1]);
    strcpy(fetched_pole->option1, argv[2]);
    strcpy(fetched_pole->option2, argv[3]);
    strcpy(fetched_pole->option3, argv[4]);
    strcpy(fetched_pole->option4, argv[5]);
    fetched_pole->end_year = (int)strtol(argv[6], &ptr, 10);
    fetched_pole->end_month = (int)strtol(argv[7], &ptr, 10);
    fetched_pole->end_day = (int)strtol(argv[8], &ptr, 10);
    return 0;
}

//CHECK
user *get_user(const char *user_id) {
    user *fetched_user = (user *) malloc(sizeof(user));
    if (fetched_user == NULL) {
        //printf("Error: Cannot allocate memory for a new user!");
        return NULL;
    }
    char sql[100];
    sprintf(sql, "SELECT * FROM USERS WHERE USER_ID = '%s';", user_id);

    /* Execute SQL statement */
    char *db_error_message = NULL;
    fetched_user->id = -1;
    int rc = sqlite3_exec(db, sql, user_callback, (void *) fetched_user, &db_error_message);

    if (rc != SQLITE_OK) {
        //fprintf(stderr, "SQL error: %s\n", db_error_message);
        sqlite3_free(db_error_message);
        return NULL;
    }
    //fprintf(stdout, "Operation done successfully\n");
    if (fetched_user->id == -1) {
        free(fetched_user);
        return NULL;
    }
    return fetched_user;
}

//CHECK
food *get_food(const char *food_id) {
    food *fetched_food = (food *) malloc(sizeof(food));
    if (fetched_food == NULL) {
        //printf("Error: Cannot allocate memory for a new food!");
        return NULL;
    }
    char sql[100];
    sprintf(sql, "SELECT * FROM FOODS WHERE FOOD_ID = '%s';", food_id);

    /* Execute SQL statement */
    char *db_error_message = NULL;
    fetched_food->id = -1;
    int rc = sqlite3_exec(db, sql, food_callback, (void *) fetched_food, &db_error_message);

    if (rc != SQLITE_OK) {
        //fprintf(stderr, "SQL error: %s\n", db_error_message);
        sqlite3_free(db_error_message);
        return NULL;
    }
    //fprintf(stdout, "Operation done successfully\n");
    if (fetched_food->id == -1) {
        free(fetched_food);
        return NULL;
    }
    return fetched_food;
}

//CHECK
self *get_self(const char *self_id) {
    self *fetched_self = (self *) malloc(sizeof(self));
    if (fetched_self == NULL) {
        //printf("Error: Cannot allocate memory for a new self!");
        return NULL;
    }
    char sql[100];
    sprintf(sql, "SELECT * FROM SELFS WHERE SELF_ID = '%s';", self_id);

    /* Execute SQL statement */
    char *db_error_message = NULL;
    fetched_self->id = -1;
    int rc = sqlite3_exec(db, sql, self_callback, (void *) fetched_self, &db_error_message);

    if (rc != SQLITE_OK) {
        //fprintf(stderr, "SQL error: %s\n", db_error_message);
        sqlite3_free(db_error_message);
        return NULL;
    }
    //fprintf(stdout, "Operation done successfully\n");
    if (fetched_self->id == -1) {
        free(fetched_self);
        return NULL;
    }
    return fetched_self;
}

//CHECK
void change_user_password(char* user_ID,char* new_password){
    char *zErrMsg = 0;
    int rc;
    char sq1[100];
    const char* data = "user_callback function called";
    sprintf( sq1,"UPDATE USERS set PASSWORD = '%s' where USER_ID = '%s' ; ",new_password,user_ID);
    rc = sqlite3_exec(db,sq1, user_callback, (void*)data, &zErrMsg);
    if( rc != SQLITE_OK ) {
        //fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
    else {
        //fprintf(stdout, "Operation done successfully\n");
    }
    return;
}


void change_reserve_reciever(int reserve_id,char* new_reciever){
    char *zErrMsg = 0;
    int rc;
    char sq1[100];
    const char* data = "reserve_callback function called";
    sprintf( sq1,"UPDATE RESERVES set RECIEVER_ID = '%s' where ID = '%d' ; ",new_reciever,reserve_id);
    rc = sqlite3_exec(db,sq1, reserve_callback, (void*)data, &zErrMsg);
    if( rc != SQLITE_OK ) {
        //fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
    else {
        //fprintf(stdout, "Operation done successfully\n");
    }
    return;
}

//CHECK
void change_user_approved(char* user_ID,int new_approved){
    char *zErrMsg = 0;
    int rc;
    char sq1[100];
    const char* data = "user_callback function called";
    sprintf( sq1,"UPDATE USERS set APPROVED = '%d' where USER_ID = '%s' ; ",new_approved,user_ID);
    rc = sqlite3_exec(db,sq1, user_callback, (void*)data, &zErrMsg);
    if( rc != SQLITE_OK ) {
        //fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
    else {
        //fprintf(stdout, "Operation done successfully\n");
    }
    return;
}

//CHECK
void change_user_charge(char* user_ID,long new_charge){
    char *zErrMsg = 0;
    int rc;
    char sq1[100];
    const char* data = "user_callback function called";
    sprintf( sq1,"UPDATE USERS set CHARGE = '%ld' where USER_ID = '%s' ; ",new_charge,user_ID);
    rc = sqlite3_exec(db,sq1, user_callback, (void*)data, &zErrMsg);
    if( rc != SQLITE_OK ) {
        //fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
    else {
        //fprintf(stdout, "Operation done successfully\n");
    }
    return;
}


void change_mealplan_remaining(int ID,int new_remaining){
    char *zErrMsg = 0;
    int rc;
    char sq1[100];
    const char* data = "mealplan_callback function called";
    sprintf( sq1,"UPDATE MEALPLANS set REMAINING = '%d' where ID = '%d' ; ",new_remaining,ID);
    rc = sqlite3_exec(db,sq1, mealplan_callback, (void*)data, &zErrMsg);
    if( rc != SQLITE_OK ) {
        //fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
    else {
        //fprintf(stdout, "Operation done successfully\n");
    }
    return;
}


void change_reserve_self_id(int ID,char* new_selfid){
    char *zErrMsg = 0;
    int rc;
    char sq1[100];
    const char* data = "reserve_callback function called";
    sprintf( sq1,"UPDATE RESERVES set SELF_ID = '%s' where ID = '%d' ; ",new_selfid,ID);
    rc = sqlite3_exec(db,sq1, reserve_callback, (void*)data, &zErrMsg);
    if( rc != SQLITE_OK ) {
        //fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
    else {
        //fprintf(stdout, "Operation done successfully\n");
    }
    return;
}

//CHECK
void delete_user(char* user_ID){
char *zErrMsg = 0;
int rc;
char sq1[100];
const char* data = "user_callback function called";
sprintf( sq1,"DELETE from USERS where USER_ID = '%s' ; ",user_ID);
    rc = sqlite3_exec(db,sq1, user_callback, (void*)data, &zErrMsg);
    if( rc != SQLITE_OK ) {
        //fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
    else {
        //fprintf(stdout, "Operation done successfully\n");
    }
    return;
}

//CHECK
void delete_food(char* food_ID){
char *zErrMsg = 0;
int rc;
char sq1[100];
const char* data = "food_callback function called";
sprintf( sq1,"DELETE from FOODS where FOOD_ID = '%s' ; ",food_ID);
    rc = sqlite3_exec(db,sq1, food_callback, (void*)data, &zErrMsg);
    if( rc != SQLITE_OK ) {
        //fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
    else {
        //fprintf(stdout, "Operation done successfully\n");
    }
    return;
}

//CHECK
void delete_self(char* self_ID){
char *zErrMsg = 0;
int rc;
char sq1[100];
const char* data = "self_callback function called";
sprintf( sq1,"DELETE from SELFS where SELF_ID = '%s' ; ",self_ID);
    rc = sqlite3_exec(db,sq1, self_callback, (void*)data, &zErrMsg);
    if( rc != SQLITE_OK ) {
        //fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
    else {
        //fprintf(stdout, "Operation done successfully\n");
    }
    return;
}


void delete_mealplan(char* mealplan_ID){
char *zErrMsg = 0;
int rc;
char sq1[100];
const char* data = "mealplan_callback function called";
sprintf( sq1,"DELETE from MEALPLANS where MEALPLAN_ID = '%s' ; ",mealplan_ID);
    rc = sqlite3_exec(db,sq1, mealplan_callback, (void*)data, &zErrMsg);
    if( rc != SQLITE_OK ) {
        //fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
    else {
        //fprintf(stdout, "Operation done successfully\n");
    }
    return;
}


void delete_reserve(int ID){
char *zErrMsg = 0;
int rc;
char sq1[100];
const char* data = "reserve_callback function called";
sprintf( sq1,"DELETE from RESERVES where ID = '%d' ; ",ID);
    rc = sqlite3_exec(db,sq1, reserve_callback, (void*)data, &zErrMsg);
    if( rc != SQLITE_OK ) {
        //fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
    else {
        //fprintf(stdout, "Operation done successfully\n");
    }
    return;
}


void delete_taken(int ID){
char *zErrMsg = 0;
int rc;
char sq1[100];
const char* data = "taken_callback function called";
sprintf( sq1,"DELETE from TAKENS where ID = '%d' ; ",ID);
    rc = sqlite3_exec(db,sq1, reserve_callback, (void*)data, &zErrMsg);
    if( rc != SQLITE_OK ) {
        //fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
    else {
        //fprintf(stdout, "Operation done successfully\n");
    }
    return;
}


void delete_returned(int ID){
char *zErrMsg = 0;
int rc;
char sq1[100];
const char* data = "returned_callback function called";
sprintf( sq1,"DELETE from RETURNEDS where ID = '%d' ; ",ID);
    rc = sqlite3_exec(db,sq1, reserve_callback, (void*)data, &zErrMsg);
    if( rc != SQLITE_OK ) {
        //fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
    else {
        //fprintf(stdout, "Operation done successfully\n");
    }
    return;
}


void delete_news(int ID){
char *zErrMsg = 0;
int rc;
char sq1[100];
const char* data = "news_callback function called";
sprintf( sq1,"DELETE from NEWS where ID = '%d' ; ",ID);
    rc = sqlite3_exec(db,sq1, news_callback, (void*)data, &zErrMsg);
    if( rc != SQLITE_OK ) {
        //fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
    else {
        //fprintf(stdout, "Operation done successfully\n");
    }
    return;
}


void delete_pole(int ID){
char *zErrMsg = 0;
int rc;
char sq1[100];
const char* data = "pole_callback function called";
sprintf( sq1,"DELETE from POLES where ID = '%d' ; ",ID);
    rc = sqlite3_exec(db,sq1, news_callback, (void*)data, &zErrMsg);
    if( rc != SQLITE_OK ) {
        //fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
    else {
        //fprintf(stdout, "Operation done successfully\n");
    }
    return;
}


user* get_user_using_ID(int ID){
user *fetched_user = (user *) malloc(sizeof(user));
    if (fetched_user == NULL) {
        //printf("Error: Cannot allocate memory for a new user!");
        return NULL;
    }
    char sql[100];
    sprintf(sql, "SELECT * FROM USERS WHERE ID = '%d';", ID);

    /* Execute SQL statement */
    char *db_error_message = NULL;
    fetched_user->id = -1;
    int rc = sqlite3_exec(db, sql, user_callback, (void *) fetched_user, &db_error_message);

    if (rc != SQLITE_OK) {
        //fprintf(stderr, "SQL error: %s\n", db_error_message);
        sqlite3_free(db_error_message);
        return NULL;
    }
    //fprintf(stdout, "Operation done successfully\n");
    if (fetched_user->id == -1) {
        free(fetched_user);
        return NULL;
    }
    return fetched_user;
}


self* get_self_using_ID(int ID){
self *fetched_self = (self *) malloc(sizeof(self));
    if (fetched_self == NULL) {
        //printf("Error: Cannot allocate memory for a new self!");
        return NULL;
    }
    char sql[100];
    sprintf(sql, "SELECT * FROM SELFS WHERE ID = '%d';", ID);

    /* Execute SQL statement */
    char *db_error_message = NULL;
    fetched_self->id = -1;
    int rc = sqlite3_exec(db, sql, self_callback, (void *) fetched_self, &db_error_message);

    if (rc != SQLITE_OK) {
        //fprintf(stderr, "SQL error: %s\n", db_error_message);
        sqlite3_free(db_error_message);
        return NULL;
    }
    //fprintf(stdout, "Operation done successfully\n");
    if (fetched_self->id == -1) {
        free(fetched_self);
        return NULL;
    }
    return fetched_self;
}


food* get_food_using_ID(int ID){
food *fetched_food = (food*) malloc(sizeof(food));
    if (fetched_food == NULL) {
        //printf("Error: Cannot allocate memory for a new food!");
        return NULL;
    }
    char sql[100];
    sprintf(sql, "SELECT * FROM FOODS WHERE ID = '%d';", ID);

    /* Execute SQL statement */
    char *db_error_message = NULL;
    fetched_food->id = -1;
    int rc = sqlite3_exec(db, sql, food_callback, (void *) fetched_food, &db_error_message);

    if (rc != SQLITE_OK) {
        //fprintf(stderr, "SQL error: %s\n", db_error_message);
        sqlite3_free(db_error_message);
        return NULL;
    }
    //fprintf(stdout, "Operation done successfully\n");
    if (fetched_food->id == -1) {
        free(fetched_food);
        return NULL;
    }
    return fetched_food;
}


mealplan* get_mealplan_using_ID(int ID){
mealplan *fetched_mealplan = (mealplan*) malloc(sizeof(mealplan));
    if (fetched_mealplan == NULL) {
        //printf("Error: Cannot allocate memory for a new mealplan!");
        return NULL;
    }
    char sql[100];
    sprintf(sql, "SELECT * FROM MEALPLANS WHERE ID = '%d';", ID);

    /* Execute SQL statement */
    char *db_error_message = NULL;
    fetched_mealplan->id = -1;
    int rc = sqlite3_exec(db, sql, mealplan_callback, (void *) fetched_mealplan, &db_error_message);

    if (rc != SQLITE_OK) {
        //fprintf(stderr, "SQL error: %s\n", db_error_message);
        sqlite3_free(db_error_message);
        return NULL;
    }
    //fprintf(stdout, "Operation done successfully\n");
    if (fetched_mealplan->id == -1) {
        free(fetched_mealplan);
        return NULL;
    }
    return fetched_mealplan;
}


reserve* get_reserve_using_ID(int ID){
reserve *fetched_reserve = (reserve *) malloc(sizeof(reserve));
    if (fetched_reserve == NULL) {
        //printf("Error: Cannot allocate memory for a new reserve!");
        return NULL;
    }
    char sql[100];
    sprintf(sql, "SELECT * FROM RESERVES WHERE ID = '%d';", ID);

    /* Execute SQL statement */
    char *db_error_message = NULL;
    fetched_reserve->id = -1;
    int rc = sqlite3_exec(db, sql, reserve_callback, (void *) fetched_reserve, &db_error_message);

    if (rc != SQLITE_OK) {
        //fprintf(stderr, "SQL error: %s\n", db_error_message);
        sqlite3_free(db_error_message);
        return NULL;
    }
    //fprintf(stdout, "Operation done successfully\n");
    if (fetched_reserve->id == -1) {
        free(fetched_reserve);
        return NULL;
    }
    return fetched_reserve;
}


reserve* get_taken_using_ID(int ID){
reserve *fetched_taken = (reserve *) malloc(sizeof(reserve));
    if (fetched_taken == NULL) {
        //printf("Error: Cannot allocate memory for a new taken!");
        return NULL;
    }
    char sql[100];
    sprintf(sql, "SELECT * FROM TAKENS WHERE ID = '%d';", ID);

    /* Execute SQL statement */
    char *db_error_message = NULL;
    fetched_taken->id = -1;
    int rc = sqlite3_exec(db, sql, taken_callback, (void *) fetched_taken, &db_error_message);

    if (rc != SQLITE_OK) {
        //fprintf(stderr, "SQL error: %s\n", db_error_message);
        sqlite3_free(db_error_message);
        return NULL;
    }
    //fprintf(stdout, "Operation done successfully\n");
    if (fetched_taken->id == -1) {
        free(fetched_taken);
        return NULL;
    }
    return fetched_taken;
}


reserve* get_returned_using_ID(int ID){
reserve *fetched_returned = (reserve *) malloc(sizeof(reserve));
    if (fetched_returned == NULL) {
        //printf("Error: Cannot allocate memory for a new returned!");
        return NULL;
    }
    char sql[100];
    sprintf(sql, "SELECT * FROM RETURNEDS WHERE ID = '%d';", ID);

    /* Execute SQL statement */
    char *db_error_message = NULL;
    fetched_returned->id = -1;
    int rc = sqlite3_exec(db, sql, returned_callback, (void *) fetched_returned, &db_error_message);

    if (rc != SQLITE_OK) {
        //fprintf(stderr, "SQL error: %s\n", db_error_message);
        sqlite3_free(db_error_message);
        return NULL;
    }
    //fprintf(stdout, "Operation done successfully\n");
    if (fetched_returned->id == -1) {
        free(fetched_returned);
        return NULL;
    }
    return fetched_returned;
}


news* get_news_using_ID(int ID){
news *fetched_news = (news *) malloc(sizeof(news));
    if (fetched_news== NULL) {
        //printf("Error: Cannot allocate memory for a new news!");
        return NULL;
    }
    char sql[100];
    sprintf(sql, "SELECT * FROM NEWS WHERE ID = '%d';", ID);

    /* Execute SQL statement */
    char *db_error_message = NULL;
    fetched_news->id = -1;
    int rc = sqlite3_exec(db, sql, news_callback, (void *) fetched_news, &db_error_message);

    if (rc != SQLITE_OK) {
        //fprintf(stderr, "SQL error: %s\n", db_error_message);
        sqlite3_free(db_error_message);
        return NULL;
    }
    //fprintf(stdout, "Operation done successfully\n");
    if (fetched_news->id == -1) {
        free(fetched_news);
        return NULL;
    }
    return fetched_news;
}


pole* get_pole_using_ID(int ID){
pole *fetched_pole = (pole *) malloc(sizeof(pole));
    if (fetched_pole== NULL) {
        //printf("Error: Cannot allocate memory for a new pole!");
        return NULL;
    }
    char sql[100];
    sprintf(sql, "SELECT * FROM POLES WHERE ID = '%d';", ID);

    /* Execute SQL statement */
    char *db_error_message = NULL;
    fetched_pole->id = -1;
    int rc = sqlite3_exec(db, sql, pole_callback, (void *) fetched_pole, &db_error_message);

    if (rc != SQLITE_OK) {
        //fprintf(stderr, "SQL error: %s\n", db_error_message);
        sqlite3_free(db_error_message);
        return NULL;
    }
    //fprintf(stdout, "Operation done successfully\n");
    if (fetched_pole->id == -1) {
        free(fetched_pole);
        return NULL;
    }
    return fetched_pole;
}


void make_or_open_database() {
    // check if db-file exist from before
    FILE *db_file = fopen(DATABASE_FILE_NAME, "rb");
    bool db_was_exist = false;
    if (db_file != NULL) {
        db_was_exist = true;
        fclose(db_file);
    }
    if (sqlite3_open(DATABASE_FILE_NAME, &db) != SQLITE_OK) {
        //fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        exit(1);
    }
    //fprintf(stdout, "Opened database successfully\n");
    if (!db_was_exist) {
        make_tables();
    }
}


void close_database() {
    sqlite3_close(db);
}


