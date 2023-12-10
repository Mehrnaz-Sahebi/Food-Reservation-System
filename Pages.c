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



void first_page(){
system("cls");
printf("\nHELLO!\n\n\nWELCOME\n\n\n\n\n\nEnter 1 to SIGN IN\n\n\nEnter 2 to REGISTER\n");
int t;
scanf("%d",&t);
if(t==1){
    sign_in_page();
    return;
}
if(t==2){
    register_page();
    return;
}
}

//HIDE THE PASSWORD
void sign_in_page(){
system("cls");
char user_id[12];
char password[30];
printf("\nPlease Enter your Username.\n");
scanf("%s",user_id);
getch();
printf("\nPlease Enter your Password.\n");
scanf("%s",password);

/*int i=0;
char c;
c=getch();
while(c!='\n'){
    password[i]=c;
    i++;
    c=getch();
}
for(int j=i;j<30;j++){
    password[j]='\0';
}*/
user* u=(user*)malloc(sizeof(user));
u=get_user(user_id);
int t;
if (u==NULL){
    printf("\nYou don't have an account with this username.\nEnter 1 to try to sign in again.\nEnter 2 to Register.\n");
    scanf("%d",&t);
    if(t==1){
        sign_in_page();
        return;
    }
    if(t==2){
        register_page();
        return;
    }
}
else{
    if(strcmp(u->password,password)!=0){
        printf("\nYour Password is incorrect.\nEnter 1 to try to sign in again.\nEnter 2 to go back to the last page.\n");
        scanf("%d",&t);
        if(t==1){
            sign_in_page();
            return;
        }
        if(t==2){
            first_page();
            return;
        }
    }
    if(strcmp(u->password,password)==0){
        if(u->approved==1){
            printf("\nYou're in!\n");
            getch();
            if(u->type==1){
                admin_home_page(u);
            }
            if(u->type==0){
                student_home_page(u);
            }
            return;
        }
        if(u->approved==0){
            printf("\nYou have registers but you're nor approved. Please wait.\nPress any key to go back to the last page.\n");
            getch();
            first_page();
            return;
        }
        if(u->approved==-1){
            printf("\nSorry your account has been deactivated; You can't sign in.\nPress any key to go back to the last page.\n");
            getch();
            first_page();
            return;
        }
    }
}
}

void register_page(){
system("cls");
printf("\nPlease enter the information below.\n\n");
user u;
int t;
u.id=-1;
u.approved=0;
u.charge=0;
printf("Username:\n");
scanf("%s",u.user_id);
if(get_user(u.user_id)!=NULL){
    printf("\nAn account with this user name already exists.\nPress any key to go back to the last page.\n");
    getch();
    first_page();
    return;
}
printf("First Name:\n");
scanf("%s",u.name);
printf("Last Name:\n");
scanf("%s",u.family);
printf("National ID:\n");
scanf("%s",u.national_id);
printf("Year of birth:\n");
scanf("%d",&u.birthdate_year);
printf("Month of birth:\n");
scanf("%d",&u.birthdate_month);
printf("Day of birth:\n");
scanf("%d",&u.birthdate_day);
printf("Gender:(Female or Male)\n");
scanf("%s",u.gender);
printf("Password\n");
scanf("%s",u.password);
printf("Do you want to register as 1.A STUDENT or as 2.AN ADMIN?\n");
scanf("%d",&t);
u.type=t-1;
insert_user(&u);
printf("\nThank you for signing up!\nYou can sign in as soon as you get approved.\nPlease wait.");
printf("\nPress any key to go back to the last page.\n");
getch();
first_page();
return;
}

void admin_home_page(user* u){
system("cls");
int t;
printf("\n\nWhat do you want to do?\n\n1.Change Your Password\n2.Change a student's Password.\n3.Charge a student's account.\n4.Register a user\n");
printf("5.See the list of users waiting for approval\n6.Deactivate a student.\n7.Delete a student's account\n8.Add a new self\n9.Add a new food\n");
printf("10.Add a new meal plan\n11.Add news\n12.Add a pole\n13.Log Out\n");
scanf("%d",&t);
if(t==1){
    change_password_page(u);
    return;
}
if(t==2){
    change_student_password_page(u);
    return;
}
if(t==3){
    admin_increases_student_charge_page(u);
    return;
}
if(t==4){
    admin_register_another_page(u);
    return;
}
if(t==5){
    approve_page(u);
    return;
}
if(t==6){
    admin_deactivate_student_page(u);
    return;
}
if(t==7){
    admin_delete_student_page(u);
    return;
}
if(t==8){
    admin_defines_self_page(u);
    return;
}
if(t==9){
    admin_defines_food_page(u);
    return;
}
if(t==10){
    admin_defines_mealplan_Page(u);
    return;
}
if(t==11){
    admin_add_news_page(u);
    return;
}
if(t==12){
    admin_add_pole_page(u);
    return;
}
if(t==13){
    log_out_page(u);
    return;
}
}

void student_home_page(user* u){
system("cls");
int t;
printf("\n\nWhat do you want to do?\n\n1.Reserve food\n2.Daily Reserve food\n3.Edit Reservations\n4.Check reservations\n");
printf("5.Take food\n6.Define an agent for taking food\n7.Charge your account\n8.Send charge to another student\n9.Change Password\n");
printf("10.Check news\n11.Check poles\n12.Log Out\n");
scanf("%d",&t);
if(t==1){
    student_reserve_page(u);
    return;
}
if(t==2){
    daily_reserve_page(u);
    return;
}
if(t==3){
    edit_reservations_page(u);
    return;
}
if(t==4){
    show_reserves_page(u);
}
if(t==5){
    take_food_page(u);
}
if(t==6){
    define_agent_page(u);
}
if(t==7){
    student_increase_charge_page(u);
    return;
}
if(t==8){
    student_send_charge_page(u);
    return;
}
if(t==9){
    change_password_page(u);
    return;
}
if(t==10){
    check_news_page(u);
    return;
}
if(t==11){
    check_pole_page(u);
    return;
}
if(t==12){
    log_out_page(u);
    return;
}
}

void change_password_page(user* u){
int t;
system("cls");
char new_pass[30];
char pass[30];
printf("\nEnter your password.\n");
scanf("%s",pass);
if(strcmp(pass,u->password)==0){
    printf("Enter your new password.\n");
    scanf("%s",new_pass);
    change_user_password(u->user_id,new_pass);
    printf("\nYour password has been changed successfully! Press any key to go back to the home page.\n");
    getch();
    return_to_home_page(u);
}
else{
    printf("Your Password is wrong.\nEnter 1 to try again.\nEnter 2 to go back to the home page.\n");
    scanf("%d",&t);
    if(t==1){
        change_password_page(u);
        return;
    }
    if(t==2){
        return_to_home_page(u);
        return;
    }
}
}

void return_to_home_page(user* u){
if(is_admin(u->user_id)){
        admin_home_page(u);
        return;
}
if(is_admin(u->user_id)==0){
        student_home_page(u);
        return;
}
}

void log_out_page(user* u){
int t;
system("cls");
printf("\n\nAre you sure that you want to log out?\n1.YES\n2.NO\n");
scanf("%d",&t);
if(t==1){
    free(u);
    first_page();
    return;
}
if(t==2){
    return_to_home_page(u);
    return;
}
}

void change_student_password_page(user* admin_u){
system("cls");
char new_pass[30];
char stu_id[12];
int t;
printf("\n\nEnter the student's user ID(student ID)\n");
scanf("%s",stu_id);
user* stu_u = get_user(stu_id);
if(stu_u==NULL){
    printf("There's no student with this ID.\nEnter 1 to try again.\nEnter 2 to go back to the home page\n");
    if(t==1){
        change_student_password_page(admin_u);
        return;
    }
    if(t==2){
        admin_home_page(admin_u);
        return;
    }
}
printf("Enter their new password.\n");
scanf("%s",new_pass);
change_user_password(stu_id,new_pass);
printf("\nThe student's password has been changed successfully!\nPress any key to go back to the home page.\n");
getch();
admin_home_page(admin_u);
return;
}

void admin_register_another_page(user* admin_u){
system("cls");
printf("\nPlease enter the information below.\n\n");
user u;
int t;
u.id=-1;
u.approved=1;
u.charge=0;
printf("Username\n");
scanf("%s",u.user_id);
if(get_user(u.user_id)!=NULL){
    printf("\nAn account with this user name already exists.\nEnter 1 to try again.\nEnter 2 to go back to the home page.\n");
    scanf("%d",&t);
    if(t==1){
        admin_register_another_page(admin_u);
        return;
    }
    if(t==2){
        admin_home_page(admin_u);
        return;
    }
}
printf("First Name:\n");
scanf("%s",u.name);
printf("Last Name:\n");
scanf("%s",u.family);
printf("National ID:\n");
scanf("%s",u.national_id);
printf("Year of birth:\n");
scanf("%d",&u.birthdate_year);
printf("Month of birth:\n");
scanf("%d",&u.birthdate_month);
printf("Day of birth:\n");
scanf("%d",&u.birthdate_day);
printf("Gender:(Female or Male)\n");
scanf("%s",u.gender);
printf("Password\n");
scanf("%s",u.password);
printf("Do you want to register the user as 1.A STUDENT or as 2.AN ADMIN?\n");
scanf("%d",&t);
u.type=t-1;
insert_user(&u);
printf("\nStudent has been signed up successfully?\n");
printf("\nEnter 1 to register another user.\nEnter 2 to go back to the home page.\n");
scanf("%d",&t);
if(t==1){
    admin_register_another_page(admin_u);
    return;
}
if(t==2){
    admin_home_page(admin_u);
    return;
}
}

void admin_deactivate_student_page(user* admin_u){
system("cls");
int t;
char stu_id[12];
printf("\nEnter the student ID of the student you want to deactivate.\n");
scanf("%s",stu_id);
if(get_user(stu_id)==NULL){
    printf("\nThere's no user with this Username.\nEnter 1 to try again.\nEnter 2 to go back to the home page.\n");
    scanf("%d",&t);
    if(t==1){
        admin_deactivate_student_page(admin_u);
        return;
    }
    if(t==2){
        admin_home_page(admin_u);
        return;
    }
}
if(is_admin(stu_id)){
    printf("\nYou can't deactivate an admin!.\nEnter 1 to try again.\nEnter 2 to go back to the home page.\n");
    scanf("%d",&t);
    if(t==1){
        admin_deactivate_student_page(admin_u);
        return;
    }
    if(t==2){
        admin_home_page(admin_u);
        return;
    }
}
change_user_approved(stu_id,-1);
printf("\nThe student has been deactivated successfully!\nEnter 1 to deactivate another student.\nEnter 2 to go back to the home page.");
scanf("%d",&t);
if(t==1){
    admin_deactivate_student_page(admin_u);
    return;
}
if(t==2){
    admin_home_page(admin_u);
    return;
}
}

void admin_delete_student_page(user* admin_u){
system("cls");
int t;
char stu_id[12];
printf("\nEnter the username of the account you want to delete.\n");
scanf("%s",stu_id);
if(get_user(stu_id)==NULL){
    printf("\nThere's no user with this Username.\nEnter 1 to try again.\nEnter 2 to go back to the home page.\n");
    scanf("%d",&t);
    if(t==1){
        admin_delete_student_page(admin_u);
        return;
    }
    if(t==2){
        admin_home_page(admin_u);
        return;
    }
}
if(is_admin(stu_id)){
    printf("\nYou can't delete an admin's account!.\nEnter 1 to try again.\nEnter 2 to go back to the home page.\n");
    scanf("%d",&t);
    if(t==1){
        admin_delete_student_page(admin_u);
        return;
    }
    if(t==2){
        admin_home_page(admin_u);
        return;
    }
}
printf("\nAre you sure you want to delete this account?\n1.YES\n2.No\n");
scanf("%d",&t);
if(t==2){
    admin_home_page(admin_u);
    return;
}
delete_user(stu_id);
printf("\nThe account has been deleted successfully!\nEnter 1 to delete another account.\nEnter 2 to go back to the home page.");
scanf("%d",&t);
if(t==1){
    admin_delete_student_page(admin_u);
    return;
}
if(t==2){
    admin_home_page(admin_u);
    return;
}
}

void approve_page(user* admin_u){
system("cls");
int i=1;
char* temp[12];
int j=0;
user* u=get_user_using_ID(i);
printf("%-8s%-34s%-34s%-14s%-10s%-8s%-14s%-32s%-22s%-9s\n\n\n","Number","First Name","Last Name","National ID","Birthdate","Gender","User ID","Password","Status","Type");
while(u!=NULL){
    if(u->approved==0){
        printf("\n%-8d",j+1);
        print_user(u->user_id);
        temp[j]=u->user_id;
        j++;
    }
    i++;
    u=get_user_using_ID(i);
}
int t;
printf("\nEnter 1 to approve students.\nEnter 2 to go back to the home page.\n");
scanf("%d",&t);
if(t==2){
    admin_home_page(admin_u);
    return;
}
printf("\nEnter the numbers of the students you want to approve in a row, Enter 0 when you're finished.\n");
while(1){
    scanf("%d",&t);
    if(t==0){
        break;
    }
    change_user_approved(temp[t-1],1);
}
printf("\nStudents were approved successfully!\nEnter 1 to see the list again.\nEnter 2 to go back to the home page.\n");
scanf("%d",&t);
if(t==1){
    approve_page(admin_u);
    return;
}
if(t==2){
    admin_home_page(admin_u);
    return;
}
}

void student_increase_charge_page(user* stu_u){
system("cls");
char user_id[12];
strcpy(user_id,stu_u->user_id);
user* new_u=get_user(user_id);
printf("\nYour current charge is %ld\n",new_u->charge);
printf("Enter the information Below to charge your account.\n");
printf("How much do you want to charge your account?\n");
long plus_charge,extra;
scanf("%ld",&plus_charge);
printf("Enter your credit card number.\n");
scanf("%ld",&extra);
printf("Enter your card's password.\n");
scanf("%ld",&extra);
increase_user_charge(stu_u->user_id,plus_charge);
user* new_stu_u=(user*)malloc(sizeof(user));
new_stu_u=get_user(stu_u->user_id);
free(stu_u);
printf("\nYour account has been charged successfully!\nYour current charge is %ld\nEnter 1 to charge again.\nEnter 2 to go back to the home page\n",new_stu_u->charge);
int t;
scanf("%d",&t);
if(t==1){
    student_increase_charge_page(new_stu_u);
    return;
}
if(t==2){
    student_home_page(new_stu_u);
    return;
}
}

void admin_increases_student_charge_page(user* admin_u){
system("cls");
int t;
char stu_id[12];
long new_charge;
printf("\nEnter the username of the account you want to charge.\n");
scanf("%s",stu_id);
if(get_user(stu_id)==NULL){
    printf("\nThere's no account with this username.\nEnter 1 to try again.\nEnter 2 to go back to the home page.\n");
    scanf("%d",&t);
    if(t==2){
        admin_home_page(admin_u);
        return;
    }
    if(t==1){
        admin_increases_student_charge_page(admin_u);
        return;
    }
}
printf("How much do you want to charge the account?\n");
scanf("%ld",&new_charge);
increase_user_charge(stu_id,new_charge);
printf("\nThe account has been charged successfully!\nEnter 1 to charge another account.\nEnter 2 to go back to the home page\n");
scanf("%d",&t);
if(t==1){
    admin_increases_student_charge_page(admin_u);
    return;
}
if(t==2){
    admin_home_page(admin_u);
    return;
}
}

void student_send_charge_page(user* sender_stu){
system("cls");
int t;
char reciever_stu_id[12];
long new_charge;
printf("\nEnter the username of the account you want to send charge to.\n");
scanf("%s",reciever_stu_id);
if(get_user(reciever_stu_id)==NULL){
    printf("\nThere's no account with this username.\nEnter 1 to try again.\nEnter 2 to go back to the home page.\n");
    scanf("%d",&t);
    if(t==2){
        student_home_page(sender_stu);
        return;
    }
    if(t==1){
        student_send_charge_page(sender_stu);
        return;
    }
}
printf("How much charge do you want to send?\n");
scanf("%ld",&new_charge);
if((sender_stu->charge-new_charge)<0){
    printf("\nYou don't have enough charge to send!\nEnter 1 to try again.\nEnter 2 to go back to the home page.\n");
    scanf("%d",&t);
    if(t==2){
        student_home_page(sender_stu);
        return;
    }
    if(t==1){
        student_send_charge_page(sender_stu);
        return;
    }
}
printf("Are you sure you want to send %ld charge to the user:\n\n",new_charge);
user* reciever_stu=get_user(reciever_stu_id);
printf("%-34s%-34s%-14s\n\n","First Name","Last Name","Student ID");
printf("%-34s%-34s%-14s\n\n",reciever_stu->name,reciever_stu->family,reciever_stu->user_id);
printf("1.YES\n2.NO");
scanf("%d",&t);
if(t==1){
    increase_user_charge(reciever_stu_id,new_charge);
    printf("\nThe charge was sent successfully!\nEnter 1 to send charge again.\nEnter 2 to go back to the home page.\n");
    int t1;
    scanf("%d",&t1);
    if(t1==1){
        student_send_charge_page(sender_stu);
        return;
    }
    if(t1==2){
        student_home_page(sender_stu);
        return;
    }
}
if(t==2){
    printf("\nEnter 1 to send charge again.\nEnter 2 to go back to the home page.\n");
    int t1;
    scanf("%d",&t1);
    if(t1==1){
        student_send_charge_page(sender_stu);
        return;
    }
    if(t1==2){
        student_home_page(sender_stu);
        return;
    }
}
}

void admin_defines_self_page(user* admin_u){
system("cls");
self s;
int t;
printf("\nEnter the information below to define a self.\n\nSelf ID:\n");
scanf("%s",s.self_id);
if(get_self(s.self_id)!=NULL){
    printf("A self with this self ID already exists.\nEnter 1 to try again.\nEnter 2 to go back to the home page.\n");
    scanf("%d",&t);
    if(t==1){
        admin_defines_self_page(admin_u);
        return;
    }
    if(t==2){
        admin_home_page(admin_u);
        return;
    }
}
printf("Self Name:\n");
scanf("%s",s.name);
printf("Place:\n");
scanf("%s",s.place);
printf("Capacity:\n");
scanf("%d",&s.capacity);
printf("Type:(1.Boyish 2.Girlish)\n");
scanf("%d",&s.type);
s.type--;
printf("Does the self serve food for 1.lunch or 2.dinner or 3.both?\n");
scanf("%d",&t);
int h,m;
if(t==1){
    s.lunch=1;
    s.dinner=0;
    printf("Enter the time lunch starts:(##:##)\n");
    scanf("%d:%d",&h,&m);
    s.lunch_start=h*100+m;
    printf("Enter the time lunch ends:(##:##)\n");
    scanf("%d:%d",&h,&m);
    s.lunch_end=h*100+m;
}
if(t==2){
    s.lunch=0;
    s.dinner=1;
    printf("Enter the time dinner starts:(##:##)\n");
    scanf("%d:%d",&h,&m);
    s.dinner_start=h*100+m;
    printf("Enter the time dinner ends:(##:##)\n");
    scanf("%d:%d",&h,&m);
    s.dinner_end=h*100+m;
}
if(t==3){
    s.lunch=1;
    s.dinner=1;
    printf("Enter the time lunch starts:(##:##)\n");
    scanf("%d:%d",&h,&m);
    s.lunch_start=h*100+m;
    printf("Enter the time lunch ends:(##:##)\n");
    scanf("%d:%d",&h,&m);
    s.lunch_end=h*100+m;
    printf("Enter the time dinner starts:(##:##)\n");
    scanf("%d:%d",&h,&m);
    s.dinner_start=h*100+m;
    printf("Enter the time dinner ends:(##:##)\n");
    scanf("%d:%d",&h,&m);
    s.dinner_end=h*100+m;
}
insert_self(&s);
printf("\nThe self has been added successfully!\nEnter 1 to add another self.\nEnter 2 to go back to the home page.\n");
scanf("%d",&t);
if(t==1){
    admin_defines_self_page(admin_u);
    return;
}
if(t==2){
    admin_home_page(admin_u);
    return;
}

}

void admin_defines_food_page(user* admin_u){
system("cls");
food f;
int t;
printf("\nEnter the information below to define a food.\n\nFood ID:\n");
scanf("%s",f.food_id);
if(get_food(f.food_id)!=NULL){
    printf("A food with this food ID already exists.\nEnter 1 to try again.\nEnter 2 to go back to the home page.\n");
    scanf("%d",&t);
    if(t==1){
        admin_defines_food_page(admin_u);
        return;
    }
    if(t==2){
        admin_home_page(admin_u);
        return;
    }
}
printf("Food Name:\n");
scanf("%s",f.name);
printf("Type:(1.Main course 2.Dessert)\n");
scanf("%d",&f.type);
f.type--;
printf("Price:\n");
scanf("%ld",&f.price);
insert_food(&f);
printf("\nThe food has been added successfully!\nEnter 1 to add another food.\nEnter 2 to go back to the home page.\n");
scanf("%d",&t);
if(t==1){
    admin_defines_food_page(admin_u);
    return;
}
if(t==2){
    admin_home_page(admin_u);
    return;
}
}

void admin_defines_mealplan_Page(user* admin_u){
system("cls");
mealplan m;
char food_id[12];
char self_id[12];
char date[10];
int year;
int month;
int day;
int amount;
int meal;
int i=1;
self* s=get_self_using_ID(i);
printf("%-8s%-14s%-34s%-34s%-15s%-8s\n\n\n","Number","Self_id","Name","Place","Meals served","Type");
while(s!=NULL){
    printf("\n%-8d",i);
    print_self(s->self_id);
    i++;
    s=get_self_using_ID(i);
}
int t;
printf("\n\nEnter the number of the self for the mealplan\n");
scanf("%d",&t);
s=get_self_using_ID(t);
strcpy(self_id,s->self_id);
printf("\nThe self was selected successfully!\nPress any key to continue.\n");
getch();
system("cls");
scanf(" %[^'\n]s",date);
sscanf(date,"%d-%d-%d",&year,&month,&day);
printf("%d,%d,%d",year,month,day);
if(s->dinner==1&&s->lunch==1){
    printf("Which meal are you defining a mealplan for?(1.lunch 2.dinner)\n");
    scanf("%d",&t);
    getch();
    meal=t-1;
}
if(s->dinner==1&&s->lunch==0){
    printf("The self you selected only serves dinner. Dinner is selected automatically as the meal you're defining a mealplan for.\n");
    meal=dinner;
}
if(s->dinner==0&&s->lunch==1){
    printf("The self you selected only serves lunch. Lunch is selected automatically as the meal you're defining a mealplan for.\n");
    meal=lunch;
}
printf("\nThe date and meal selected successfully!\nPress any key to continue.\n");
getch();
system("cls");
printf("%-8s%-14s%-34s%-15s%-13s\n\n\n","Number","food_id","Name","Price","Type");
i=1;
food* f=get_food_using_ID(i);
while(f!=NULL){
    printf("\n%-8d",i);
    print_food(f->food_id);
    i++;
    f=get_food_using_ID(i);
}
printf("\n\nEnter the number of the foods you want to select and how many of each of them is available.(format: number-amount)\nEnter 0 when you're finished\n");
strcpy(m.self_id,self_id);
m.year=year;
m.month=month;
m.day=day;
m.meal=meal;
scanf("%d-",&t);
while(t!=0){
    scanf("%d ",&amount);
    m.amount=amount;
    m.remaining=amount;
    f=get_food_using_ID(t);
    strcpy(m.food_id,f->food_id);
    insert_mealplan(&m);
    scanf("%d-",&t);
}
printf("\nmealplan was created successfully!\nEnter 1 to add create another one.\nEnter 2 to return to the home page.\n");
scanf("%d",&t);
if(t==1){
    admin_defines_mealplan_Page(admin_u);
    return;
}
if(t==2){
    admin_home_page(admin_u);
    return;
}
}

void admin_add_news_page(user* admin_u){
system("cls");
news n;
char title[200];
char content[400];
char extra;
printf("\nEnter the title of the news.\n");
scanf(" %[^\n]s",title);
printf("\nEnter the content of the news.\n");
scanf(" %[^\n]s",content);
printf("\nEnter the end date of the news.(####-##-##)\n");
scanf("%d-%d-%d",&n.end_year,&n.end_month,&n.end_day);
strcpy(n.title,title);
strcpy(n.content,content);
insert_news(&n);
printf("\nThe news was added successfully!\nEnter 1 to add another news.\nEnter 2 to go back to the home page.\n");
int t;
scanf("%d",&t);
if(t==1){
    admin_add_news_page(admin_u);
    return;
}
if(t==2){
    admin_home_page(admin_u);
    return;
}
}

void check_news_page(user* stu_u){
system("cls");
int i=1;
int j=1;
news* n=get_news_using_ID(i);
while(n!=NULL){
    if(compare_date(n->end_year,n->end_month,n->end_day)>=0){
        printf("%d.",j);
        j++;
        puts(n->title);
        puts(n->content);
        printf("\n\n");
    }
    i++;
    n=get_news_using_ID(i);
}
printf("\nPress any key to go back to the home page.\n");
getch();
student_home_page(stu_u);
return;
}

void student_reserve_page(user *stu_u){
system("cls");
int i=1;
int j=1;
char temp[50][12];
self* s=get_self_using_ID(i);
printf("%-8s%-14s%-34s%-34s%-15s%-8s\n\n\n","Number","Self_id","Name","Place","Meals served","Type");
while(s!=NULL){
    if(s->type==0&&strcmpi(stu_u->gender,"male")==0||s->type==1&&strcmpi(stu_u->gender,"female")==0){
        printf("\n%-8d",j);
        print_self(s->self_id);
        strcpy(temp[j-1],s->self_id);
        j++;

    }
    i++;
    s=get_self_using_ID(i);
}
printf("\nChoose one of the selves and Enter its number.\n");
int tself;
scanf("%d",&tself);
system("cls");
int a[12];
int b[12];
int c[12];
int year=local->tm_year+1900;
int month=local->tm_mon+1;
int day=local->tm_mday;
printf("\n");
day+=2;
for(int k=3;k<15;k++){
    day++;
    if(day>30){
        month++;
        day=day-30;
        if(month>12){
            year++;
            month=month-12;
        }
    }
    printf("%d. %d/%.2d/%.2d\n",k-2,year,month,day);
    a[k-3]=year;
    b[k-3]=month;
    c[k-3]=day;
}
printf("\nChoose a date and Enter its number.\n");
int tdate;
scanf("%d",&tdate);
year=a[tdate-1];
month=b[tdate-1];
day=c[tdate-1];
system("cls");
printf("\nWhich meal do you want to reserve?(1.Lunch 2.Dinner)\n");
int meal;
scanf("%d",&meal);
meal--;
system("cls");
int temp2[50];
long price[50];
i=1;
j=1;
mealplan* m=get_mealplan_using_ID(i);
printf("%-8s%-14s%-34s%-15s%-13s%-10s\n\n\n","Number","food_id","Name","Price","Type","Remaining");
while(m!=NULL){
    if(strcmp(m->self_id,temp[tself-1])==0&&m->year==year&&m->month==month&&m->day==day&&m->remaining>0&&meal==m->meal){
        printf("\n%-8d",j);
        print_food(m->food_id);
        printf("%-10d\n",m->remaining);
        temp2[j-1]=m->id;
        food* f=get_food(m->food_id);
        price[j-1]=f->price;
        j++;
    }
    i++;
    m=get_mealplan_using_ID(i);
}
printf("\nChoose the foods you want and Enter their numbers in a row. Enter 0 when you're finished.\n");
int tfood;
scanf("%d",&tfood);
long sumprice=0;
while(tfood!=0){
    reserve r;
    r.day=local->tm_mday;
    r.month=local->tm_mon+1;
    r.year=local->tm_year+1900;
    r.mealplan_id=temp2[tfood-1];
    r.time=(local->tm_hour*100)+(local->tm_min);
    r.type=before;
    strcpy(r.user_id,stu_u->user_id);
    mealplan* m=get_mealplan_using_ID(temp2[tfood-1]);
    strcpy(r.self_id,m->self_id);
    strcpy(r.reciever_id,stu_u->user_id);
    insert_reserve(&r);
    sumprice+=price[tfood-1];
    minusminus_mealplan_remaining(temp2[tfood-1]);
    scanf("%d",&tfood);
}
decrease_user_charge(stu_u->user_id,sumprice);
user* new_u=get_user(stu_u->user_id);
if(new_u->charge<0){
    printf("You don't have enough charge to reserve those items. First increase your charge them the reserves will be done for you.\n");
    getch();
    student_increase_charge_page(stu_u);
    return;
}
printf("\nThe foods were reserved successfully!\nEnter 1 to do another reservation.\nEnter 2 to go back to the home page.\n");
int t;
scanf("%d",&t);
if(t==1){
    student_reserve_page(stu_u);
    return;
}
if(t==2){
    student_home_page(stu_u);
    return;
}
}

void daily_reserve_page(user* stu_u){
system("cls");
int i=1;
int j=1;
int temp[50];
printf("%-8s%-34s%-34s%-15s%-10s%-15s\n\n\n","number","Self Name","Food Name","Remaining","Price","Type");
mealplan* m=get_mealplan_using_ID(i);
while(m!=NULL){
    self* s=get_self(m->self_id);
    food* f=get_food(m->food_id);
    int lunch_end=minus_time(s->lunch_end,30);
    int dinner_end=minus_time(s->dinner_end,30);
    if(compare_time(s->lunch_start)<=0&&compare_time(lunch_end)>=0&&m->meal==lunch&&m->remaining>0&&compare_date(m->year,m->month,m->day)==0){
        printf("%-8d%-34s%-34s%-15d%-10d",j,s->name,f->name,m->remaining,(f->price)*2);
        if(f->type==dessert){
            printf("%-15s","Dessert\n");
        }
        if(f->type==main_course){
            printf("%-15s","Main Course\n");
        }
        temp[j-1]=m->id;
        j++;
    }
    if(compare_time(s->dinner_start)<=0&&compare_time(dinner_end)>=0&&m->meal==dinner&&m->remaining>0&&compare_date(m->year,m->month,m->day)==0){
        printf("%-8d%-34s%-34s%-15d%-10d",j,s->name,f->name,m->remaining,(f->price)*2);
        if(f->type==dessert){
            printf("%-15s","Dessert\n");
        }
        if(f->type==main_course){
            printf("%-15s","Main Course\n");
        }
        temp[j-1]=m->id;
        j++;
    }
    i++;
    m=get_mealplan_using_ID(i);
}
printf("\nEnter the numbers of the foods you want to reserve.Enter 0 when you're finished.\n");
int t;
scanf("%d",&t);
long sumprice=0;
while(t!=0){
    reserve r;
    r.day=local->tm_mday;
    r.month=local->tm_mon+1;
    r.year=local->tm_year+1900;
    r.mealplan_id=temp[t-1];
    r.time=(local->tm_hour*100)+(local->tm_min);
    r.type=daily;
    strcpy(r.user_id,stu_u->user_id);
    strcpy(r.reciever_id,stu_u->user_id);
    mealplan* m=get_mealplan_using_ID(temp[t-1]);
    strcpy(r.self_id,m->self_id);
    insert_reserve(&r);
    food* f=get_food(m->food_id);
    sumprice+=f->price;
    minusminus_mealplan_remaining(temp[t-1]);
    scanf("%d",&t);
}
decrease_user_charge(stu_u->user_id,2*sumprice);
user* new_u=get_user(stu_u->user_id);
if(new_u->charge<0){
    printf("You don't have enough charge to reserve those items. First increase your charge them the reserves will be done for you.\n");
    getch();
    student_increase_charge_page(stu_u);
    return;
}
printf("\nThe foods were reserved successfully!\nEnter 1 to do another reservation.\nEnter 2 to go back to the home page.\n");
scanf("%d",&t);
if(t==1){
    daily_reserve_page(stu_u);
    return;
}
if(t==2){
    student_home_page(stu_u);
    return;
}
}

void show_reserves_page(user* stu_u){
system("cls");
printf("%-8s%-14s%-8s%-34s%-34s%-15s%-15s%-12s%-12s\n\n\n","Number","Date","Meal","Self Name","Food Name","Price","Type","Start time","End time");
int year=local->tm_year+1900;
int month=local->tm_mon+1;
int day=local->tm_mday;
printf("\n");
for(int k=0;k<15;k++){
    if(day>30){
        month++;
        day=day-30;
        if(month>12){
            year++;
            month=month-12;
        }
    }
    char date[10];
    sprintf(date,"%d/%.2d/%.2d",year,month,day);
    printf("%-8d%-14s",k+1,date);
    int i=1;
    int j=1;
    reserve* r=get_reserve_using_ID(i);
    while(r!=NULL){
        mealplan* m=get_mealplan_using_ID(r->mealplan_id);
        if(strcmp(r->user_id,stu_u->user_id)==0&&m->year==year&&m->month==month&&m->day==day){
            food* f=get_food(m->food_id);
            self* s=get_self(r->self_id);
            if(j>1){
                printf("                      ");
            }
            if(m->meal==dinner){
                printf("%-8s","Dinner");
            }
            if(m->meal==lunch){
                printf("%-8s","Lunch");
            }
            printf("%-34s%-34s%-15ld",s->name,f->name,f->price);
            if(f->type==dessert){
                printf("%-15s","Dessert");
            }
            if(f->type==main_course){
                printf("%-15s","Main Course");
            }
            if(m->meal==dinner){
                printf("%-2d:%-9d%-2d:%-9d\n",s->dinner_start/100,s->dinner_start%100,s->dinner_end/100,s->dinner_end%100);
            }
            if(m->meal==lunch){
                printf("%-2d:%-9d%-2d:%-9d\n",s->lunch_start/100,s->lunch_start%100,s->lunch_end/100,s->lunch_end%100);
            }
            j++;
        }
        i++;
        r=get_reserve_using_ID(i);
    }
    day++;
    printf("\n\n");
}
printf("\n\nPress any key to go back to the home page.\n");
getch();
student_home_page(stu_u);
return;
}

void edit_reservations_page(user* stu_u){
system("cls");
int temp[100];
printf("%-8s%-14s%-8s%-34s%-34s%-15s%-15s%-12s%-12s\n\n\n","Number","Date","Meal","Self Name","Food Name","Price","Type","Start time","End time");
int year=local->tm_year+1900;
int month=local->tm_mon+1;
int day=local->tm_mday;
printf("\n");
for(int k=0;k<15;k++){
    if(day>30){
        month++;
        day=day-30;
        if(month>12){
            year++;
            month=month-12;
        }
    }
    char date[10];
    sprintf(date,"%d/%.2d/%.2d",year,month,day);
    int i=1;
    int j=1;
    reserve* r=get_reserve_using_ID(i);
    while(r!=NULL){
        mealplan* m=get_mealplan_using_ID(r->mealplan_id);
        if(strcmp(r->user_id,stu_u->user_id)==0&&m->year==year&&m->month==month&&m->day==day){
            food* f=get_food(m->food_id);
            self* s=get_self(r->self_id);
            printf("%-8d%-14s",j,date);
            if(m->meal==dinner){
                printf("%-8s","Dinner");
            }
            if(m->meal==lunch){
                printf("%-8s","Lunch");
            }
            printf("%-34s%-34s%-15ld",s->name,f->name,f->price);
            if(f->type==dessert){
                printf("%-15s","Dessert");
            }
            if(f->type==main_course){
                printf("%-15s","Main Course");
            }
            if(m->meal==dinner){
                printf("%-2d:%-9d%-2d:%-9d\n",s->dinner_start/100,s->dinner_start%100,s->dinner_end/100,s->dinner_end%100);
            }
            if(m->meal==lunch){
                printf("%-2d:%-9d%-2d:%-9d\n",s->lunch_start/100,s->lunch_start%100,s->lunch_end/100,s->lunch_end%100);
            }
            temp[j-1]=r->id;
            j++;
        }
        i++;
        r=get_reserve_using_ID(i);
    }
    day++;
    printf("\n\n");
}
printf("\n\nWhat do you want to do?\n1.Cancel a reservation\n2.Change the self of the reservation\n");



int t;
int x;
scanf("%d",&x);
if(x==1){
    printf("Enter the number of the reservation you want to cancel.\n");
    int cancel_t;
    scanf("%d",&cancel_t);
    reserve* r=get_reserve_using_ID(temp[cancel_t-1]);
    mealplan* m=get_mealplan_using_ID(r->mealplan_id);
    self* s=get_self(r->self_id);
    food* f=get_food(m->food_id);
    if((compare_date(m->year,m->month,m->day)>0)||
       (compare_date(m->year,m->month,m->day)==0&&compare_time(minus_time(s->lunch_start,60))>=0&&m->meal==lunch)||
       (compare_date(m->year,m->month,m->day)==0&&compare_time(minus_time(s->dinner_start,60))>=0&&m->meal==dinner)
       ){
        reserve new_returned;
        strcpy(new_returned.user_id,r->user_id);
        strcpy(new_returned.reciever_id,r->reciever_id);
        strcpy(new_returned.self_id,r->self_id);
        new_returned.mealplan_id=r->mealplan_id;
        new_returned.type=r->type;
        new_returned.year=local->tm_year+1900;
        new_returned.month=local->tm_mon+1;
        new_returned.day=local->tm_mday;
        new_returned.time=(local->tm_hour*100)+local->tm_min;
        insert_returned(&new_returned);
        delete_reserve(temp[cancel_t-1]);
        increase_user_charge(new_returned.user_id,(0.9*(float)f->price));
        plusplus_mealplan_remaining(r->mealplan_id);
        printf("\nThe reservation has been cancelled successfully!\nEnter 1 to edit the reservations again.\nEnter 2 to go back to the home page.\n");
        scanf("%d",&t);
        switch(t){
        case(1):
            edit_reservations_page(stu_u);
            break;
            return;
        case(2):
            student_home_page(stu_u);
            break;
            return;
        }
    }
    else{
        printf("\nYou can't cancel this reservation.\nEnter 1 to edit the reservations again.\nEnter 2 to go back to the home page.\n");
        scanf("%d",&t);
        switch(t){
        case(1):
            edit_reservations_page(stu_u);
            break;
            return;
        case(2):
            student_home_page(stu_u);
            break;
            return;
        }
    }
}




if(x==2){
    printf("Enter the number of the reservation you want to change its self.\n");
    int change_t1;
    scanf("%d",&change_t1);
    system("cls");
    int i=1;
    int j=1;
    char temp2[50][12];
    self* s=get_self_using_ID(i);
    printf("%-8s%-14s%-34s%-34s%-15s%-8s\n\n\n","Number","Self_id","Name","Place","Meals served","Type");
    while(s!=NULL){
        if(s->type==0&&strcmpi(stu_u->gender,"male")==0||s->type==1&&strcmpi(stu_u->gender,"female")==0){
            printf("\n%-8d",j);
            print_self(s->self_id);
            strcpy(temp2[j-1],s->self_id);
            j++;
        }
        i++;
        s=get_self_using_ID(i);
    }
    printf("\nChoose one of the selves and Enter its number.\n");
    int change_t2;
    scanf("%d",&change_t2);
    reserve* r=get_reserve_using_ID(temp[change_t1-1]);
    mealplan* m=get_mealplan_using_ID(r->mealplan_id);
    s=get_self(r->self_id);
    if((compare_date(m->year,m->month,m->day)>0)||
       (compare_date(m->year,m->month,m->day)==0&&compare_time(s->lunch_start-300)>=0&&m->meal==lunch)||
       (compare_date(m->year,m->month,m->day)==0&&compare_time(s->dinner_start-300)>=0&&m->meal==dinner)
       ){
        change_reserve_self_id(temp[change_t1-1],temp2[change_t2-1]);
        printf("\nThe self was changed successfully!\nEnter 1 to edit the reservations again.\nEnter 2 to go back to the home page.\n");
        scanf("%d",&t);
        switch(t){
        case(1):
            edit_reservations_page(stu_u);
            break;
            return;
        case(2):
            student_home_page(stu_u);
            break;
            return;
        }
    }
    else{
        printf("\nYou can't change this reservation.\nEnter 1 to edit the reservations again.\nEnter 2 to go back to the home page.\n");
        scanf("%d",&t);
        switch(t){
        case(1):
            edit_reservations_page(stu_u);
            break;
            return;
        case(2):
            student_home_page(stu_u);
            break;
            return;
        }
    }
}

}

void take_food_page(user* stu_u){
system("cls");
int i=1;
int j=1;
int t;
int temp[50];
printf("Your foods:\n");
printf("%-8s%-8s%-34s%-34s%-15s%-12s%-12s\n\n","Number","Meal","Self Name","Food Name","Type","Start time","End time");
reserve* r =get_reserve_using_ID(i);
while(r!=NULL){
    mealplan* m=get_mealplan_using_ID(r->mealplan_id);
    self* s=get_self(r->self_id);
    food* f=get_food(m->food_id);
    if(strcmp(r->reciever_id,stu_u->user_id)==0&&strcmp(r->user_id,stu_u->user_id)==0&&compare_date(m->year,m->month,m->day)==0&&
    ((m->meal==dinner&&compare_time(s->dinner_end)>=0&&compare_time(s->dinner_start)<=0)||(m->meal==lunch&&compare_time(s->lunch_end)>=0
    &&compare_time(s->lunch_start)<=0))){

        printf("%-8d",j);
        if(m->meal==lunch){
            printf("%-8s","Lunch");
        }
        if(m->meal==dinner){
            printf("%-8s","Dinner");
        }
        printf("%-34s%-34s",s->name,f->name);
        if(f->type==dessert){
            printf("%-15s","Dessert");
        }
        if(f->type==main_course){
            printf("%-15s","Main Course");
        }
        if(m->meal==dinner){
            printf("%-2d:%-9d%-2d:%-9d\n",s->dinner_start/100,s->dinner_start%100,s->dinner_end/100,s->dinner_end%100);
        }
        if(m->meal==lunch){
            printf("%-2d:%-9d%-2d:%-9d\n",s->lunch_start/100,s->lunch_start%100,s->lunch_end/100,s->lunch_end%100);
        }
        temp[j-1]=i;
        j++;
    }
    i++;
    r=get_reserve_using_ID(i);
}
i=1;
printf("\n\n\nYour friends' foods(they have made you their agent.):\n");
printf("%-8s%-8s%-34s%-34s%-15s%-12s%-12s\n\n","Number","Meal","Self Name","Food Name","Type","Start time","End time");
r =get_reserve_using_ID(i);
while(r!=NULL){
    mealplan* m=get_mealplan_using_ID(r->mealplan_id);
    self* s=get_self(r->self_id);
    food* f=get_food(m->food_id);
    if(strcmp(r->reciever_id,stu_u->user_id)==0&&strcmp(r->user_id,stu_u->user_id)!=0&&compare_date(m->year,m->month,m->day)==0&&
    ((m->meal==dinner&&compare_time(s->dinner_end)>=0&&compare_time(s->dinner_start)<=0)||(m->meal==lunch&&compare_time(s->lunch_end)>=0
    &&compare_time(s->lunch_start)<=0))){

        printf("%-8d",j);
        if(m->meal==lunch){
            printf("%-8s","Lunch");
        }
        if(m->meal==dinner){
            printf("%-8s","Dinner");
        }
        printf("%-34s%-34s",s->name,f->name);
        if(f->type==dessert){
            printf("%-15s","Dessert");
        }
        if(f->type==main_course){
            printf("%-15s","Main Course");
        }
        if(m->meal==dinner){
            printf("%-2d:%-9d%-2d:%-9d\n",s->dinner_start/100,s->dinner_start%100,s->dinner_end/100,s->dinner_end%100);
        }
        if(m->meal==lunch){
            printf("%-2d:%-9d%-2d:%-9d\n",s->lunch_start/100,s->lunch_start%100,s->lunch_end/100,s->lunch_end%100);
        }
        temp[j-1]=i;
        j++;
    }
    i++;
    r=get_reserve_using_ID(i);
}
printf("\nEnter the number of the foods you want to take. Enter 0 when you're finished.\n");
scanf("%d",&t);
while(t!=0){
    r=get_reserve_using_ID(temp[t-1]);
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
    delete_reserve(r->id);
    scanf("%d",&t);
}
printf("\nThe foods were taken successfully!\nEnter 1 to view this page again.\nEnter 2 to go back to the home page.\n");
scanf("%d",&t);
if(t==1){
    take_food_page(stu_u);
    return;
}
if(t==2){
    student_home_page(stu_u);
    return;
}
}

void define_agent_page(user* stu_u){
system("cls");
int temp[100];
printf("%-8s%-14s%-8s%-34s%-34s%-15s%-15s%-12s%-12s\n\n\n","Number","Date","Meal","Self Name","Food Name","Reciever id","Type","Start time","End time");
int year=local->tm_year+1900;
int month=local->tm_mon+1;
int day=local->tm_mday;
printf("\n");
for(int k=0;k<15;k++){
    if(day>30){
        month++;
        day=day-30;
        if(month>12){
            year++;
            month=month-12;
        }
    }
    char date[10];
    sprintf(date,"%d/%.2d/%.2d",year,month,day);
    int i=1;
    int j=1;
    reserve* r=get_reserve_using_ID(i);
    while(r!=NULL){
        mealplan* m=get_mealplan_using_ID(r->mealplan_id);
        food* f=get_food(m->food_id);
        self* s=get_self(r->self_id);
        if((k!=0&&strcmp(r->user_id,stu_u->user_id)==0&&m->year==year&&m->month==month&&m->day==day)||(
           k==0&&strcmp(r->user_id,stu_u->user_id)==0&&m->year==year&&m->month==month&&m->day==day&&
           (m->meal==dinner&&compare_time(s->dinner_start)>=0||m->meal==lunch&&compare_time(s->lunch_start)>=0))){
            printf("%-8d%-14s",j,date);
            if(m->meal==dinner){
                printf("%-8s","Dinner");
            }
            if(m->meal==lunch){
                printf("%-8s","Lunch");
            }
            printf("%-34s%-34s%-15ld",s->name,f->name,r->reciever_id);
            if(f->type==dessert){
                printf("%-15s","Dessert");
            }
            if(f->type==main_course){
                printf("%-15s","Main Course");
            }
            if(m->meal==dinner){
                printf("%-2d:%-9d%-2d:%-9d\n",s->dinner_start/100,s->dinner_start%100,s->dinner_end/100,s->dinner_end%100);
            }
            if(m->meal==lunch){
                printf("%-2d:%-9d%-2d:%-9d\n",s->lunch_start/100,s->lunch_start%100,s->lunch_end/100,s->lunch_end%100);
            }
            temp[j-1]=r->id;
            j++;
        }
        i++;
        r=get_reserve_using_ID(i);
    }
    day++;
}
int t;
printf("\n\nChoose the number of the meal you want to define an agent for.\n");
scanf("%d",&t);
printf("Enter the username of your agent.\n");
char agent_user[12];
scanf("%s",agent_user);
if(get_user(agent_user)==NULL){
    printf("\nThere's no user with this username.\nEnter 1 to try again.\nEnter 2 to go back to the home page.\n");
    int x;
    scanf("%d",&x);
    if(x==1){
        define_agent_page(stu_u);
        return;
    }
    if(x==2){
        student_home_page(stu_u);
        return;
    }
}
else if(is_admin(agent_user)){
    printf("\nThis user is an admin.\nEnter 1 to try again.\nEnter 2 to go back to the home page.\n");
    int x;
    scanf("%d",&x);
    if(x==1){
        define_agent_page(stu_u);
        return;
    }
    if(x==2){
        student_home_page(stu_u);
        return;
    }
}
else{
    change_reserve_reciever(temp[t-1],agent_user);
    printf("\nThe agent was selected successfully!.\nEnter 1 to define another agent.\nEnter 2 to go back to the home page.\n");
    int x;
    scanf("%d",&x);
    if(x==1){
        define_agent_page(stu_u);
        return;
    }
    if(x==2){
        student_home_page(stu_u);
        return;
    }
}
}

void admin_add_pole_page(user* admin_u){
system("cls");
pole p;
char content[400];
char option1[200];
char option2[200];
char option3[200];
char option4[200];
char extra;
printf("\nEnter the question of the pole.\n");
scanf(" %[^\n]s",content);
printf("\nEnter the first option.\n");
scanf(" %[^\n]s",option1);
printf("\nEnter the second option.\n");
scanf(" %[^\n]s",option2);
printf("\nEnter the third option.\n");
scanf(" %[^\n]s",option3);
printf("\nEnter the fourth option.\n");
scanf(" %[^\n]s",option4);
printf("\nEnter the end date of the pole.(####-##-##)\n");
scanf("%d-%d-%d",&p.end_year,&p.end_month,&p.end_day);
printf("%d,%d.%d",p.end_year,p.end_month,p.end_day);
strcpy(p.question,content);
strcpy(p.option1,option1);
strcpy(p.option2,option2);
strcpy(p.option3,option3);
strcpy(p.option4,option4);
insert_pole(&p);
printf("\nThe pole was added successfully!\nEnter 1 to add another pole.\nEnter 2 to go back to the home page.\n");
int t;
scanf("%d",&t);
if(t==1){
    admin_add_pole_page(admin_u);
    return;
}
if(t==2){
    admin_home_page(admin_u);
    return;
}
}

void check_pole_page(user* stu_u){
system("cls");
int i=1;
int j=1;
pole* p=get_pole_using_ID(i);
while(p!=NULL){
    if(compare_date(p->end_year,p->end_month,p->end_day)>=0){
        printf("%d.",j);
        j++;
        puts(p->question);
        printf("a)");
        puts(p->option1);
        printf("b)");
        puts(p->option2);
        printf("c)");
        puts(p->option3);
        printf("d)");
        puts(p->option4);
        printf("\n\n");
    }
    i++;
    p=get_pole_using_ID(i);
}
printf("\nWhich pole do you want to vote for?\n");
int t;
scanf("%d",&t);
printf("\nEnter your vote.\n");
getche();
getch();
printf("\nYour vote was submitted.\nPress any key to go back to the home page.\n");
getch();
student_home_page(stu_u);
return;
}
