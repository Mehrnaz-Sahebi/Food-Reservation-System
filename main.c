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



int main(int argc, char* argv[]) {
    //Set time

    t = time(NULL);
    local = localtime(&t);
    //open Tables and Files
    FILE* fpin=fopen("testcase_input.txt","r");
    printf("%s",fpin);
    FILE* fpout=fopen("testcase_output.txt","w");
    make_or_open_database();


    //change_date(2024,2,2,thursday);
    //change_time();

    user u={-1,"admin","admin","admin","admin","admin","admin",1,1,1,1,1,0};
    insert_user(&u);
//    start(fpout,fpin);
    first_page();



    close_database();
    fclose(fpout);
    fclose(fpin);
    return 0;
}
