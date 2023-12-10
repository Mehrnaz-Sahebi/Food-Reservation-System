
extern struct tm* local;
extern time_t t;

void print_user(char*);
void print_self(char*);
void print_food(char*);
void print_mealplan(int);
int is_admin(char*);
void increase_user_charge(char*,long);
void decrease_user_charge(char*,long);
void decrease_mealplan_remaining(int,int);
void minusminus_mealplan_remaining(int);
void plusplus_mealplan_remaining(int);
void change_time(int,int);
void change_date(int,int, int,int);

// if t<local -1
// if t=local 0
// if t>local 1
int compare_time(int);
int compare_date(int,int,int);
int minus_time(int,int);
int can_reserve(reserve);
