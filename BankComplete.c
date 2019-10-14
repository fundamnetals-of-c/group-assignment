/*******************************************************************************
 * 48430 Fundamentals of C Programming - Assignment 3
 * Name: James Walsh
 * Student ID: 99143152
 * Name: Sebastien Liao
 * Student ID: 13689043
 * Name: Walter Chan
 * Student ID: 12569582
 * Name: Tam-Hoang Nguyen
 * Student ID: 13589256
 * Name: Eleftherios Asiminaris
 * Student ID: 12889097
 * Date of submission: -/-/2019
 * A brief statement on what you could achieve (less than 50 words):
 * 
 * 
 * A brief statement on what you could NOT achieve (less than 50 words):
 * 
 * 
*******************************************************************************/

/*******************************************************************************
 * List header files - do NOT use any other header files. Note that stdlib.h is
 * included in case you want to use any of the functions in there. However the
 * task can be achieved with stdio.h and string.h only.
*******************************************************************************/
#include <stdio.h> /*scanf printf fscanf fprintf fflush fopen fclose*/
#include <string.h> /*strlen strcmp strcpy strcat*/
#include <stdlib.h> 
#include <time.h> /*time localtime*/

/*******************************************************************************
 * List preprocessing directives - DEFINES
*******************************************************************************/

#define DEFINES "defined"
#define USER_MAX_NUM_LEN 6
#define USER_NUM_LETTER_LEN 2
#define USER_MAX_PW_LEN 32
#define USER_MAX_LVL_LEN 5
#define SQ_MAX_LEN 30
#define ANSWER_MAX_LEN 10
#define MAX_TYPE_LEN 15

/*defines for testing valid date_time inputs*/
#define MONTHS_LOWER 1
#define MONTHS_UPPER 12
#define DAYS_LOWER 1
#define DAYS_UPPER 32
#define HOURS_LOWER 0
#define HOURS_UPPER 23
#define MINUTES_LOWER 0
#define MINUTES_UPPER 60

/*******************************************************************************
 * List structs - you may define struct date_time and struct flight only. Each
 * struct definition should have only the fields mentioned in the assignment
 * description.
*******************************************************************************/
typedef struct users
{
    char user_num[USER_MAX_NUM_LEN + 1];
    char user_pw[USER_MAX_PW_LEN + 1];
    char user_lvl[USER_MAX_LVL_LEN + 1];
    double acc_balance;
    struct users * next;
} users_t;

typedef struct logged_user
{ 
    char user_num[USER_MAX_NUM_LEN + 1];
    char user_pw[USER_MAX_PW_LEN + 1];
    char user_lvl[USER_MAX_LVL_LEN + 1];
    double acc_balance;
}logged_user_t;

typedef struct user_security_questions
{
    char sq1[SQ_MAX_LEN];
    char ans1[ANSWER_MAX_LEN];
    char sq2[SQ_MAX_LEN];
    char ans2[ANSWER_MAX_LEN];
    char sq3[SQ_MAX_LEN];
    char ans3[ANSWER_MAX_LEN];
}user_security_questions_t;

typedef struct date_time
{
    int year;
    int month;
    int day;
    int hour;
    int minute;
} date_time_t;

typedef struct transaction_details
{
    date_time_t trans_dt;
    char type[MAX_TYPE_LEN+1];
    double principal;
    double trans_val;
    double acc_balance;
} transaction_details_t;

typedef struct transactions
{
    transaction_details_t trans_detail;
    struct transactions * next ;
} transactions_t;

/*******************************************************************************
 * Function prototypes - define your own functions if required.
*******************************************************************************/
/*menus*/
int login_menu(logged_user_t * logged_user); /*james*/
void print_menu(logged_user_t * user); /*james*/
void dev_menu(logged_user_t * user); /*james*/
void admin_menu(logged_user_t * user); /*james*/
void user_menu(logged_user_t * user); /*james*/

void print_users(users_t * user); /*james*/

/*user functions*/
double get_balance(const logged_user_t * user); /*james*/
int deposit(logged_user_t * user, double value); /*tam*/
int withdraw(logged_user_t * user, double value); /*tam*/
int transfer(logged_user_t * user, 
                const char target_acc[USER_MAX_NUM_LEN],
                double value); /*james*/
int print_statement(const char user_ID[USER_MAX_NUM_LEN]); /*terry*/
int change_password(const char user_ID[USER_MAX_NUM_LEN]); /*james*/

/*admin functions*/
int add_user(users_t * user); /*james*/
int delete_user(users_t * user); /*james*/
int store_users(users_t * user); /*james*/
int read_users(users_t * users); /*james*/
int write_users(users_t * users); /*james*/

int validate_user_ID(const char user_ID[]); /*james*/
int validate_user_pw(const char user_pw[]); /*walter*/
void create_sq(); /*seb*/
int trans_cmp(const struct date_time trans_dt, const struct date_time date_dt);
void validate_sq(const char user_ID[USER_MAX_NUM_LEN]); /*seb*/
int validate_date_time(const struct date_time time); /*james*/

const char* encryption(int key, char string[]); /*seb and walter*/
const char* decryption(int key, char string[]); /*seb and walter*/
void format_trans_type(char type[]); /*terry*/

/*******************************************************************************
 * Main
*******************************************************************************/
int main(void)
{
    /*SETUP OF VARIABLES USED IN THE MAJORITY OF THE CODE*/
    logged_user_t * logged_user;
    logged_user = malloc(sizeof(logged_user_t));

    users_t * start = NULL;
    start = malloc(sizeof(users_t));

    if(start == NULL)
    {
        printf("mem error");
        return -1;
    }
    strcpy(start->user_lvl,"start");
    start->next = NULL;
    
    #ifdef DEBUG
    printf("created linked list");
    #endif
int i;
scanf("%d",&i);
if(i != 1)
{
    #ifdef DEBUG
    printf("USER/ADMIN MENU");
    #endif
    while(login_menu(logged_user) != 1);
}
else
{
    #ifdef DEBUG
    printf("DEV MENU");
    #endif
    strcpy(logged_user->user_lvl,"test");
}
    print_menu(logged_user);
    
    return 0;
}

/*******************************************************************************
 * Description
 * this function takes a user struct and inputs user data into it.
 * this function will return a 1 is the input matched the stored data in the 
 * users.txt file and will return a -1 if it couldn't find the user name or the
 * password is incorrect for a valid user name
 * INPUTS:
 * logged_user_t
 * OUTPUTS:
 * 1 if valid, -1 if invalid
 * POST:
 * this function will end with the logged user being filled with local user 
 * data based on inputs
*******************************************************************************/
int login_menu(logged_user_t * logged_user)
{
    /*setup user inputs*/
    char userID[USER_MAX_NUM_LEN + 1];
    char userPW[USER_MAX_PW_LEN + 1];
    printf("please enter a user name: ");
    scanf("%s", userID);

    /*validate user ID*/
    printf("please enter your password: ");
    scanf("%s", userPW);

    /*place into struct*/
    #ifdef DEBUG
    printf("USER NUM: %s\n"
        "USER PASSWORD: %s\n");
    #endif
    strcpy(logged_user->user_num,userID);
    strcpy(logged_user->user_pw,userPW);
    
    /*check against database*/
    logged_user_t logger;
    FILE *fptr = NULL;
    fptr = fopen("users.txt","r");

    if(fptr == NULL)
    {
        printf("mem error file location doesnt exsist");
    }

    /*sort through file until found*/
    /*int login_attempt = 0;*/
    while(fptr != NULL)
    {
        /*fill the logger struct with temp data*/
        if(fread(&logger, sizeof(logged_user_t), 1, fptr) == 0)
        {
            printf("incorrect ID or password\n");
	    validate_sq(userID);
	    /*
            switch(login_attempt) {
                case 0:
                    printf("You have two more attempts\n");
                    break;
                case 1:
                    printf("You have one last attempt\n");
                    break;
                case 2:
                    validate_sq();
                    return -1; 
                    break;
            }
            printf("please enter again your user name: ");
            scanf("%s", userID);

            printf("please enter again your password: ");
            scanf("%s", userPW);

            strcpy(logged_user->user_num,userID);
            strcpy(logged_user->user_pw,userPW);
            login_attempt++;*/
        }
        /*check the logger information against user input*/
        if(strcmp(logger.user_pw, userPW) == 0 && 
            strcmp(logger.user_num, userID) == 0)
        {
            strcpy(logged_user->user_lvl,"test");
            strcpy(logged_user->user_lvl, logger.user_lvl);
            logged_user->acc_balance = logger.acc_balance;
            printf("Welcome\n");
            fclose(fptr);
            return 1;
        }
    }
    return -1;
}

/*******************************************************************************
 * Description
 * this function will change the command line display based on the user level 
 * that belongs to the loggered user function. the logged_user_t will return 
 * with the lastest user data. cannot be const as it is pass through this 
 * function into further functions
 * INPUTS:
 * logged_user_t
 * OUTPUTS:
 * - nothing
 * POST:
 * will be filled with the lasted user data after the user has choosen to log 
 * out
*******************************************************************************/
void print_menu(logged_user_t * user)
{ 
    if(strcmp(user->user_lvl,"test") == 0)
    {
        dev_menu(user);
    }
    else if(strcmp(user->user_lvl,"admin") == 0)
    {
        admin_menu(user);
    }
    else if(strcmp(user->user_lvl,"user") == 0)
    {
        user_menu(user);
    }
    else
    {
        printf("unable to match user level with a valid user level\n");
    }        
}

/*******************************************************************************
 * Description
 * this is the menu that will be given to the devs, with special functions 
 * such as choosing the user rather then having it forced into args of some 
 * functions
 * this is where devs can choose what function they require
 * INPUTS:
 * logged_user_t
 * OUTPUTS:
 * -nothing
 * POST:
 * will be filled with the lasted user data after the user has choosen to log 
 * out
*******************************************************************************/
void dev_menu(logged_user_t * user)
{

    users_t * start = NULL;
    start = malloc(sizeof(users_t));
char poop[8] = "string";
char user_ID[10];

    if(start == NULL)
    {
        printf("mem error");
        return;
    }
    strcpy(start->user_lvl,"start");
    start->next = NULL;

    double val;
    int user_input = -1;
    while(1)
    {
        printf("\n"
        "admin options:\n"
        "1. add user\n"
        "2. remove user\n"
        "3. view user statement\n"
        "user options:\n"
        "4. view balance\n"
        "5. withdraw funds\n"
        "6. deposit funds\n"
        "7. transfer funds\n"
        "8. chnage password\n"
        "dev options:\n"
        "9. view all user account numbers\n"
        "10. log out\n"
	"11. Encrypt\n"
	"12. Decrypt\n"
        "13. Validate PW\n");
    
        scanf("%d", &user_input);
read_users(start);
        switch(user_input)
        {
            case 1 :
                    printf("add user\n");
                    add_user(start);
print_users(start);
                    break;
            case 2 :
                    printf("remove user\n");
                    delete_user(start);
                    break;
            case 3 :
                    printf("view a users statement\n");
                    printf("enter target users account number");
                    scanf("%s", user_ID);
                    print_statement(user_ID);
                    break;
            case 4 :
                    printf("view balance\n");
                    printf("your balance is: $%.2lf\n", get_balance(user));
                    break;
            case 5 :
                    printf("withdraw funds\n");
                    printf("Please enter how much you wish to withdraw:>");
                    scanf("%lf", &val);
                    withdraw(user, val);
                    break;
            case 6 :
                    printf("deposit funds\n");
                    printf("Please enter how much you wish to deposit:>");
                    scanf("%lf", &val);
                    deposit(user, val);
                    break;
            case 7 :
                    printf("transfer funds\n");
                    transfer(user, "25",1);
                    break;
            case 8 :
                    printf("change user password\n");
                    printf("enter target users account number");
                    scanf("%s", user_ID);
                    change_password(user_ID);
                    break;
            case 9 :
                    printf("view all account numbers\n");
                    print_users(start);
                    break;
            case 10:
                    printf("logging out\n");
                    return;
	    case 11: 
                    printf("Encrypt; Key, String:\n");
		    encryption(1, poop);
                    break;
	    case 12:
                    printf("Decrypt; Key, String:\n");
		    decryption(1, poop);
                    break;
                case 13:
                    printf("Validate PW, String:\n");
                    scanf("%s", poop);
		            validate_user_pw(poop);
                    break;
            default:
                    printf("Invalid input\n");
                    break;
        }
    }
}

/*******************************************************************************
 * Description
 * this is the menu that will be given to the admins, with special functions 
 * such as choosing the user rather then having it forced into args of some 
 * functions
 * this is where admins can choose what function they require
 * INPUTS:
 * logged_user_t
 * OUTPUTS:
 * -nothing
 * POST:
 * will be filled with the lasted user data after the user has choosen to log 
 * out
*******************************************************************************/
void admin_menu(logged_user_t * user)
{
    users_t * start = NULL;
    start = malloc(sizeof(users_t));

    if(start == NULL)
    {
        printf("mem error");
        return ;
    }
    strcpy(start->user_lvl,"start");
    start->next = NULL;

    int user_input = -1;
    while(1)
    {
        printf("\n"
        "1. add user\n"
        "2. remove user\n"
        "3. view user statement\n"
        "4. log out\n");
    
        scanf("%d", &user_input);
        switch(user_input)
        {
            case 1 :
                    printf("add user\n");
                    add_user(start);
                    print_users(start);
                    break;
            case 2 :
                    printf("remove user\n");
                    break;
            case 3 :
                    printf("view a users statement\n");
                    break;
            case 4 :
                    printf("logging out\n");
                    return;
            default:
                    printf("Invalid input\n");
                    break;
        }
    }
}

/*******************************************************************************
 * Description
 * this is the menu that will be given to the users, with all functions having 
 * args forced into the functions 
 * functions
 * this is where users can choose banking actions they need
 * INPUTS:
 * logged_user_t
 * OUTPUTS:
 * -nothing
 * POST:
 * will be filled with the lasted user data after the user has choosen to log 
 * out
*******************************************************************************/
void user_menu(logged_user_t * user)
{
    int user_input = -1;
    double val = 0;
    char user_ID[10];
    while(1)
    {
        printf("\n"
        "1. view balance\n"
        "2. withdraw funds\n"
        "3. deposit funds\n"
        "4. transfer funds\n"
        "5. view user statement\n"
        "6. change password\n"
        "7. log out\n");
    
        scanf("%d", &user_input);
        switch(user_input)
        {
            case 1 :
                    printf("view balance\n");
                    printf("%.2lf",get_balance(user));
                    break;
            case 2 :
                    printf("withdraw funds\n");
                    printf("how much funds would like to withdraw>");
                    scanf("%lf", &val);
                    withdraw(user, val);
                    break;
            case 3 :
                    printf("deposit funds\n");
                    printf("how much funds would like to deposit>");
                    scanf("%lf", &val);
                    deposit(user, val);
                    break;
            case 4 :
                    printf("transfer funds\n");
                    printf("what account ID would you like to transfer to>");
                    scanf("%s", user_ID);
                    printf("how much funds would like to transfer>");
                    scanf("%lf", &val);
                    transfer(user, user_ID, val);
                    break;
            case 5 :
                    printf("view user statement");
                    print_statement(user->user_num);
                    break;
            case 6 :
                    printf("change password");
                    change_password(user->user_num);
                    break;
            case 7 :
                    printf("logging out\n");
                    return;
            default:
                    printf("Invalid input\n");
                    break;
        }
    }
}
/*******************************************************************************
 * Description
 * this function will ask for user information and store it into a linked list
 * it will then write the user data into a file when finished
 * this allows the program to store as many users with no end
 * the function will return the number of members in temp storage
 * INPUTS:
 * users_t
 * OUTPUTS:
 * int 
 * POST:
 * users_t will be filled with the temp new members
*******************************************************************************/
int add_user(users_t * user)
{
    /*set up temp variables to store user entry*/
    char user_num[USER_MAX_NUM_LEN + 1];
    char user_pw[USER_MAX_PW_LEN + 1];
    char user_lvl[USER_MAX_LVL_LEN + 1];
    double acc_balance;

    /*entering user data*/
    printf("Enter user information\n");
    printf("Enter the new user number: \n");
    scanf("%s", user_num);
    /*validate*/
    printf("Enter the new user password: \n");
    scanf("%s", user_pw);
    /*validate*/
    printf("Enter the user level");
    /*validate*/
    scanf("%s", user_lvl);
    printf("Enter user initial account balance");
    scanf("%lf", &acc_balance);

    users_t * it = user;
    
    /*check if this is the first user*/
    if(strcmp(it->user_lvl, "test") == 0)
    {
        strcpy(it->user_num, encryption(1, user_num));
        strcpy(it->user_pw, user_pw);
        strcpy(it->user_lvl, user_lvl);
        it->acc_balance = acc_balance;
        store_users(it);
    }
    else
    {
        while(it->next != NULL)
        {
            it = it->next;
        }
        it->next = malloc(sizeof(users_t));
        /*entering user data into struct*/
        strcpy(it->next->user_num, encryption(1, user_num));
        strcpy(it->next->user_pw, user_pw);
        strcpy(it->next->user_lvl, user_lvl);
        it->next->acc_balance = acc_balance;
        it->next->next = NULL;
        store_users(it->next);
    }    
    return 1;
}

/*******************************************************************************
 * Description
 * this function will print the group of new users
 * INPUTS:
 * users_t
 * OUTPUTS:
 * -nothing
 * POST:
 * what happens to pointers and data after the function
*******************************************************************************/
void print_users(users_t * user)
{
    users_t * it = user;

    while(it != NULL)
    {
        printf("%s\n", decryption(1,it->user_num));
        it = it->next;
    }
}

/*******************************************************************************
 * Description
 * this function returns the logged in users balance
 * INPUTS:
 * logged_user_t
 * OUTPUTS:
 * double (user balance)
 * POST:
 * pointers stay constant
*******************************************************************************/
double get_balance(const logged_user_t * user)
{
    return user->acc_balance;
}

/*******************************************************************************
 * Description
 * this function allows a user to deposit an ammount of money into their account
 * and adjust the users account balance
 * INPUTS:
 * logged_user_t, double
 * OUTPUTS:
 * -1 is invalid, 1 is valid
 * POST:
 * logged_user_t is filled with the most up to date account balance
*******************************************************************************/
int deposit(logged_user_t * user, double value)
{
    /*set temp variables*/
    date_time_t dt;
    transaction_details_t transaction_details;    

    /*inport local computer time for transaction history*/
    time_t rawtime;
    struct tm * timeinfo;

    time ( &rawtime );
    timeinfo = localtime ( &rawtime );

    dt.year = timeinfo->tm_year + 1900;
    dt.month = timeinfo->tm_mon + 1;
    dt.day = timeinfo->tm_mday;
    dt.minute = timeinfo->tm_min;

    /*fill transaction information*/
    transaction_details.trans_dt = dt;
    strcpy(transaction_details.type, "deposit");
    transaction_details.principal = user->acc_balance;
    transaction_details.trans_val = value;
    transaction_details.acc_balance = 
        transaction_details.principal + transaction_details.trans_val;

    /*update account balance*/
    user->acc_balance = transaction_details.acc_balance;

    /*find file to fill transaction data into*/
    FILE *fptr = NULL;
    char file_name[USER_MAX_NUM_LEN + 5];
    strcpy(file_name, user->user_num);
    strcat(file_name, ".txt");
    fptr = fopen(file_name, "a");

    /*check the data base has no errors*/
    if(fptr == NULL)
    {
        printf("error when openning data base");
        return -1;
    }

    /*write to database*/
    fwrite(&transaction_details, sizeof(transaction_details_t), 1, fptr);
    fclose(fptr);
    return 1;
}

/*******************************************************************************
 * Description
 * this is a user function use to withdraw money from their account and write 
 * it to their transaction history file
 * INPUTS:
 * logged_user_t, double
 * OUTPUTS:
 * -1 if invalid, 1 is valid
 * POST:
 * logged_user_t with new balance added
*******************************************************************************/
int withdraw(logged_user_t * user, double value)
{
    /*set temp variables*/
    date_time_t dt;
    transaction_details_t transaction_details;    

    /*import local computer time for transaction*/
    time_t rawtime;
    struct tm * timeinfo;

    time ( &rawtime );
    timeinfo = localtime ( &rawtime );

    dt.year = timeinfo->tm_year + 1900;
    dt.month = timeinfo->tm_mon + 1;
    dt.day = timeinfo->tm_mday;
    dt.hour = timeinfo->tm_hour;
    dt.minute = timeinfo->tm_min;

    /*check if user has enough balance to withdraw*/
    if(user->acc_balance < value)
    {
        printf("error: not enough funds within account");
        transaction_details.trans_dt = dt;
        strcpy(transaction_details.type, "low fund");
        transaction_details.principal = user->acc_balance;
        transaction_details.trans_val = -1 * value;
        transaction_details.acc_balance = user->acc_balance;
    }
    else
    {
        transaction_details.trans_dt = dt;
        strcpy(transaction_details.type, "withdraw");
        transaction_details.principal = user->acc_balance;
        transaction_details.trans_val = value;
        transaction_details.acc_balance = 
            transaction_details.principal - transaction_details.trans_val;

    }
    /*update user account balance*/
    user->acc_balance = transaction_details.acc_balance;
    
    /*open the file to fill the data base*/
    FILE *fptr = NULL;
    char file_name[USER_MAX_NUM_LEN + 5];
    strcpy(file_name, user->user_num);
    strcat(file_name, ".txt");
    fptr = fopen(file_name, "a");

    /*check the database has no errors opening*/
    if(fptr == NULL)
    {
        printf("error when openning data base");
        return -1;
    }

    /*write transaction to file*/
    fwrite(&transaction_details, sizeof(transaction_details_t), 1, fptr);
    fclose(fptr);
    return 1;
}

/*******************************************************************************
 * Description
 * this function takes the logged in user and will transfer an ammount of money
 * from their account into the target account and write this transfer on both
 * users transaction statements
 * INPUTS:
 * logged_user_t, char[], double
 * OUTPUTS:
 * -1 if invalid, 1 if valid
 * POST:
 * what happens to pointers and data after the function
*******************************************************************************/
int transfer(logged_user_t * user, const char target_acc[], double value)
{
    /*set up temp variables*/
    date_time_t dt;
    transaction_details_t transaction_details; 
    logged_user_t logger;   

    /*import local time from computer*/
    time_t rawtime;
    struct tm * timeinfo;

    time ( &rawtime );
    timeinfo = localtime ( &rawtime );

    dt.year = timeinfo->tm_year + 1900;
    dt.month = timeinfo->tm_mon + 1;
    dt.day = timeinfo->tm_mday;
    dt.hour = timeinfo->tm_hour;
    dt.minute = timeinfo->tm_min;

    /*open file database to check users*/
    FILE *fptr = NULL;
    fptr = fopen("users.txt","r");

    if(fptr == NULL)
    {
        printf("mem error file location doesnt exsist");
    }

    /*test if account exists*/
    while(fptr != NULL)
    {
        if(fread(&logger, sizeof(logged_user_t), 1, fptr) == 0)
        {
            printf("Invalid account ID\n");
            fclose(fptr);
            return -1;
        }
        if(strcmp(logger.user_num, target_acc) == 0)
        {
            fclose(fptr);
            break;
        }
    }
    /*check if the account has enough to transfer*/
    if(user->acc_balance < value)
    {
        printf("error: not enough funds within account");
        transaction_details.trans_dt = dt;
        strcpy(transaction_details.type, "low funds");
        transaction_details.principal = user->acc_balance;
        transaction_details.trans_val = -1 * value;
        transaction_details.acc_balance = user->acc_balance;
        return user->acc_balance;
    }
    else
    {
        transaction_details.trans_dt = dt;
        strcpy(transaction_details.type, "transaction out");
        transaction_details.principal = user->acc_balance;
        transaction_details.trans_val = -1 * value;
        transaction_details.acc_balance = 
            transaction_details.principal - transaction_details.trans_val;
    }
    /*update user account balance*/
    user->acc_balance = transaction_details.acc_balance;
    /*write to user transaction database*/
    fptr = NULL;
    char file_name[USER_MAX_NUM_LEN + 5];
    strcpy(file_name, user->user_num);
    strcat(file_name, ".txt");
    fptr = fopen(file_name, "a");

    if(fptr == NULL)
    {
        printf("error when openning data base");
        return -1;
    }

    fwrite(&transaction_details, sizeof(transaction_details_t), 1, fptr);
    fclose(fptr);

    /*create linked lists to rewrite*/
    users_t * start = NULL;
    start = malloc(sizeof(users_t));

    if(start == NULL)
    {
        printf("mem error");
        return -1;
    }
    strcpy(start->user_lvl,"start");
    start->next = NULL;

    read_users(start);
    
    /*obtain and write data*/ 
    users_t * it = start;
    while(it != NULL)
    {
        if(strcmp(decryption(1, it->user_num), target_acc) == 0)
        {
            break;
        }
        it = it->next;
    }
/*debug
    printf("target user: %s bal: %lf",it->user_num, it->acc_balance); 
*/
    transaction_details.trans_dt = dt;
    strcpy(transaction_details.type, "transaction in");
    transaction_details.principal = it->acc_balance;
    transaction_details.trans_val = 1 * value;
    transaction_details.acc_balance = 
        transaction_details.principal + transaction_details.trans_val;       

    /*update target user account balance*/
    it->acc_balance = transaction_details.acc_balance;

    /*write transaction history on reciever*/
    fptr = NULL;
    strcpy(file_name, it->user_num);
    strcat(file_name, ".txt");
    fptr = fopen(file_name, "a");

    if(fptr == NULL)
    {
        printf("error when openning data base");
        return -1;
    }

    /*write transactio details to file*/
    fwrite(&transaction_details, sizeof(transaction_details_t), 1, fptr);
    fclose(fptr);

    /*update all users in the linked list*/
    write_users(start);
    return 1;
}

/*******************************************************************************
 * Description
 * this function will allow the user to change their password
 * INPUTS:
 * char[USER_MAX_PW_LEN]
 * OUTPUTS:
 * -1 if invalid, 1 if valid
 * POST:
 * array is constant no change
*******************************************************************************/
int change_password(const char user_ID[USER_MAX_NUM_LEN])
{
    char pw_holder[USER_MAX_PW_LEN];

    /*create linked lists*/
    users_t * start = NULL;
    start = malloc(sizeof(users_t));

    if(start == NULL)
    {
        printf("mem error cannot allocate memory");
        return -1;
    }
    strcpy(start->user_lvl,"start");
    start->next = NULL;

    read_users(start);

    /*obtain user position*/ 
    users_t * it = start;
    while(it != NULL)
    {
        if(strcmp(it->user_num, user_ID) == 0)
        {
            break;
        }
        it = it->next;
    }
    
    printf("What would you like to change your password to>");
    scanf("%s", pw_holder);

    /*validate pw*/
    
    strcpy(it->user_pw, pw_holder);

    write_users(start);
    printf("password successfully changed");   
    
    return 1;
}

/*******************************************************************************
 * Description
 * this function will allow the user to print the statement for the user account
 * between two dates
 * INPUTS:
 * char[USER_MAX_NUM_LEN]
 * OUTPUTS:
 * -1 if invalid, no of statements
 * POST:
 * array is constant no change
*******************************************************************************/
int print_statement(const char user_ID[USER_MAX_NUM_LEN])
{
    /*ask for date*/
    date_time_t start_dt;
    date_time_t end_dt;
    date_time_t dt;
    int flag = 0;
    transaction_details_t transaction;   

    /*while dates arent valid*/ 
    while(flag == 0)
    {
        printf("Please enter that date you should like to see from:\n");
        start_dt = dt;
        end_dt = dt;
        /*while start date isnt valid*/
        while(validate_date_time(start_dt) == -1)
        {
            printf("Enter year, month, date, hour and minute ");
            printf("separated by spaces>\n");
            scanf("%d %d %d %d %d", 
                &start_dt.year,
                &start_dt.month, 
                &start_dt.day, 
                &start_dt.hour, 
                &start_dt.minute);
        }
        printf("Please enter that date you should like to see to:\n");
        /*while end date isnt valid*/
        while(validate_date_time(end_dt) == -1)
        {
            printf("Enter year, month, date, hour and minute ");
            printf("separated by spaces>\n");
            scanf("%d %d %d %d %d", 
                &end_dt.year,
                &end_dt.month, 
                &end_dt.day, 
                &end_dt.hour, 
                &end_dt.minute);
        }
        /*if valid dates change the flag to break the while*/
        if(trans_cmp(start_dt, end_dt) == -1)
        {
            flag = 1;
        }
        else
            printf("Invalid start and/or end date\n");
    }
    
    /*set up file data base pointer*/
    FILE *fptr = NULL;
    char file_name[USER_MAX_NUM_LEN + 5];
    strcpy(file_name, user_ID);
    strcat(file_name, ".txt");
    fptr = fopen(file_name, "r");

    /*check if file is read*/
    if(fptr == NULL)
    {
        printf("error when openning data base");
        return -1;
    }

    /*while file isnt at the end keep reading data*/
    /*break on first valid transaction*/
    while(fptr != NULL)
    {
        /*check if there is anything left to read in file*/
        if(fread(&transaction, sizeof(transaction_details_t), 1, fptr) == 0)
        {
            printf("no transactions found\n");
            fclose(fptr);
            return -1;
        }
        if(trans_cmp(transaction.trans_dt, start_dt) == 1)
        {
            break;
        }
    }
    /*print transaction history header*/
    printf("transaction history:\n");
    printf("transaction       transaction\n");
    printf("date        time  type            ammount balance\n");
    /*print all the valid transactions until end date reached*/
    while(trans_cmp(end_dt,transaction.trans_dt) == 1)
    {
        if(fread(&transaction, sizeof(transaction_details_t), 1, fptr) == 0)
        {
            printf("End of statement\n");
            fclose(fptr);
            break;
        }
        format_trans_type(transaction.type);
        printf("%02d/%02d/%04d  %02d:%02d %s $%.2lf $%.2lf\n", 
            transaction.trans_dt.day,
            transaction.trans_dt.month,
            transaction.trans_dt.year,
            transaction.trans_dt.hour,
            transaction.trans_dt.minute,
            transaction.type,
            transaction.trans_val,
            transaction.acc_balance);
    }

return 0;
}

/*******************************************************************************
 * Description
 * this function comapre two dates with the early date being on the first 
 * argument and the later date being on the second argument
 * INPUTS:
 * date_time_t, date_time_t
 * OUTPUTS:
 * -1 if invalid, 1 if valid
 * POST:
 * arrays is constant no change
*******************************************************************************/
int trans_cmp(const struct date_time trans_dt, const struct date_time date_dt)
{
    if(trans_dt.year < date_dt.year)
        return -1;
    if(trans_dt.year == date_dt.year &&
        trans_dt.month < date_dt.month)
        return -1;
    if(trans_dt.year == date_dt.year &&
        trans_dt.month == date_dt.month &&
        trans_dt.day < date_dt.day)
        return -1;
    if(trans_dt.year == date_dt.year &&
        trans_dt.month == date_dt.month &&
        trans_dt.day == date_dt.day &&
        trans_dt.hour < date_dt.hour)
        return -1;
    if(trans_dt.year == date_dt.year &&
        trans_dt.month == date_dt.month &&
        trans_dt.day == date_dt.day &&
        trans_dt.hour == date_dt.hour &&
        trans_dt.minute < date_dt.minute)
        return -1;
    
    return 1;
}
/*******************************************************************************
 * Description
 * this function will find and delete a user based on user ID
 * INPUTS:
 * users_t*
 * OUTPUTS:
 * int num of deleted users 
 * POST:
 * the pointer will contain the same data but without the user that was removed
*******************************************************************************/
int delete_user(users_t * user)
{
    /*needs to account for first and last pos, first can be done within an quick it->user check before falling into the while
end can be done by checking next next and if next next is NULL just leave it*/
    char user_num[USER_MAX_NUM_LEN];
    printf("what is the user account number you would like to delete: ");
    scanf("%s", user_num);

    users_t * temp = NULL;
    users_t * it = user;
    
    while(it->next != NULL)
    {
        if(strcmp(it->next->user_num, user_num) == 0)
        {
            printf("hit %s\n", it->user_num);
            temp = it->next;
            it->next = temp->next;
        }
        else
{
printf("miss %s\n", it->user_num);
}
it = it->next;
    }
return 1;
}

/*******************************************************************************
 * Description
 * appends new users to the users database file
 * INPUTS:
 * users_t
 * OUTPUTS:
 * -1 if invalid, 1 if successful
 * POST:
 * nothing chnages within pointer
*******************************************************************************/
int store_users(users_t * user)
{
    FILE *fptr = NULL;
    fptr = fopen("users.txt", "a");
    if(fptr == NULL)
    {
        printf("error when openning data base");
        return -1;
    }
    logged_user_t write_user;
    strcpy(write_user.user_num, user->user_num);
    strcpy(write_user.user_pw, user->user_pw);
    strcpy(write_user.user_lvl, user->user_lvl);
    write_user.acc_balance = user->acc_balance;

    fwrite(&write_user, sizeof(logged_user_t), 1, fptr);
    fclose(fptr);
    return 1;
}
/*******************************************************************************
 * Description
 * INPUTS:
 * what is required to input into this function
 * OUTPUTS:
 * what gets returned
 * POST:
 * what happens to pointers and data after the function
*******************************************************************************/
int read_users(users_t * users)
{
    logged_user_t logged_user;
    users_t * it = users;
    FILE *fptr = NULL;
    fptr = fopen("users.txt","r");

    if(fptr == NULL)
    {
        printf("mem error file location doesnt exsist");
    }
    /*sort through file until found*/

    while(fptr != NULL)
    {
        if(fread(&logged_user, sizeof(logged_user_t), 1, fptr) == 0)
        {
            return -1;
        }
        if(strcmp(users->user_lvl,"start") == 0)
        {
            /*local store first user*/
            strcpy(users->user_num,logged_user.user_num);
            strcpy(users->user_pw,logged_user.user_pw);
            strcpy(users->user_lvl,logged_user.user_lvl);
            users->acc_balance = logged_user.acc_balance;
            users->next = NULL;
        }
        else
        {
            /*search for next empty list*/
            while(it->next != NULL)
            {
                it = it->next;
            }

            /*local store users*/
            it->next = malloc(sizeof(users_t));
            strcpy(it->next->user_num,logged_user.user_num);
            strcpy(it->next->user_pw,logged_user.user_pw);
            strcpy(it->next->user_lvl,logged_user.user_lvl);
            it->next->acc_balance = logged_user.acc_balance;
            it->next->next = NULL;
        }
    }
    return 1;
}

/*******************************************************************************
 * Description
 * this function writes a linked list of any size into the users file
 * INPUTS:
 * users_t
 * OUTPUTS:
 * -1 if invalid, 1 if completed task
 * POST:
 * no user data changes
*******************************************************************************/
int write_users(users_t * users)
{
    FILE *fptr = NULL;
    fptr = fopen("users.txt","w");
    logged_user_t holder;

    if(fptr == NULL)
    {
        printf("mem error: couldn't create user file");
        return -1;
    }

    users_t * it = users;
    while(it != NULL)
    {
        strcpy(holder.user_num,it->user_num);
        strcpy(holder.user_pw,it->user_pw);
        strcpy(holder.user_lvl,it->user_lvl);
        holder.acc_balance = it->acc_balance;
        fwrite(&holder, sizeof(logged_user_t), 1, fptr);
        it = it->next;
    }
    fclose(fptr);
    return 1;
}

/*******************************************************************************
 * Description
 * This function inputs a user ID string and will validate that it is 
 * valid as per the group outline such as first two chars being letters and
 * having to be capital letters, followed by 1 to 4 intergers. this function 
 * will not change the user ID string
 * inputs:
 * - user_ID
 * outputs:
 * - 1 is input is valid, -1 is the input isn't valid
*******************************************************************************/
int validate_user_ID(const char user_ID[])
{
    /*initlise incrementing variable*/
    int i;
    /*test if flightcode is longer then the maximum determined size if it is 
    return an error*/
    if((int)strlen(user_ID) > USER_MAX_NUM_LEN)
    {
        return -1;
    }
    /*iterate through the letters of the flight code checking they are capiital
	letters*/
    for(i = 0; i < USER_NUM_LETTER_LEN; i++)
    {
        /*test if the flightcode letters are between A - Z or 65 - 90*/
        if(user_ID[i] < 'A' || user_ID[i] > 'Z')
        {
            return -1;
        }
    }
    for(i = USER_NUM_LETTER_LEN; i < USER_MAX_NUM_LEN; i++)
    {
        /*test if the flightcode is at the end of the string as flightcode can 
        be less then 6 chars*/
        if(user_ID[i] == '\0' && i > USER_NUM_LETTER_LEN)
        {
            return 1;
        }
        /*test if the flightcode numbers are between '0' - '9' or 48 - 57*/
        else if(user_ID[i] < '0' || user_ID[i] > '9')
        {
            return -1;
        }
    }
    return 1;
}

/*******************************************************************************
 * Description
 * INPUTS:
 * Takes user_pw[], which is an assumed string.
 * OUTPUTS:
 * Returns the number of characters in that string, -1 if the password is invalid.
 * POST:
 * what happens to pointers and data after the function, I dunno.
*******************************************************************************/
int validate_user_pw(const char user_pw[])
{
    int i, upper = 0, lower = 0, digit = 0, special = 0;
    if (user_pw == NULL || strlen(user_pw) == 0)
    {
        return -1;
    }
    for (i = 0; i < strlen(user_pw); i++) {
        /*printf("%d\n", user_pw[i]);*/
        if (user_pw[i] >= 'a' && user_pw[i] <= 'z'){
            lower++;
        }
        if (user_pw[i] >= 'A' && user_pw[i] <= 'Z'){
            upper++;
        }
        if (user_pw[i] >= '0' && user_pw[i] <= '9'){
            digit++;
        }
        if (user_pw[i] >= 33 && user_pw[i] <= 47){
            special++;
        }
        if (user_pw[i] >= 58 && user_pw[i] <= 64){
            special++;
        }
        
    }
    if ((lower + upper + digit + special) != strlen(user_pw)){
        printf("Please use at least 1 of Lower & Upper Case, Number and special characters\n");
        return -1;
    }
    else if ((lower < 1) || (upper < 1) || (digit < 1) || (special < 1)) {	
    printf("Please use at least 1 of Lower & Upper Case, Number and special characters\n");	
    return -1;
    }
    return (lower + upper + digit + special);
}

/*******************************************************************************
 * Description
 * INPUTS:
 * what is required to input into this function
 * OUTPUTS:
 * what gets returned
 * POST:
 * what happens to pointers and data after the function
*******************************************************************************/
void create_sq() { 
    user_security_questions_t userSq;
    char sq[SQ_MAX_LEN];
    char ans[ANSWER_MAX_LEN];
    int NumberSq = 1;
    int option;
    int questionNb;
    printf("1. Choose among a list of security questions\n"
           "2. Create your own security questions\n"
           "Choose an option : ");
    scanf("%d", &option);
    printf("Choose 3 security questions:\n");
    if(option == 1) {
        printf("1. What is you oldest sibling's middle name ?\n"
               "2. In what city or town did your mother and father meet ?\n"
               "3. What was the last name of your third grade teacher ?\n"
               "4. What is your mother's maiden name ?\n"
               "5. In what city or town was your first job ?\n"
               "6. What was the name of your elementary school ?\n"
               "7. In what city or town does your nearest sibling live ?\n"
               "8. What is your pet's name ?\n");
    }
    while(NumberSq < 4 ) {
        switch(option){
            case 1:
                printf("Enter the number corresponding to the question : ");
                scanf("%d", &questionNb);
                switch(questionNb){
                    case 1:
                        strcpy(sq,"What is you oldest sibling's middle name ?");
                        break;
                    case 2:
                        strcpy(sq,"In what city or town did your mother and father meet ?");
                        break;
                    case 3:
                        strcpy(sq,"What was the last name of your third grade teacher ?");
                        break;
                    case 4:
                        strcpy(sq,"What is your mother's maiden name ?");
                        break;
                    case 5:
                        strcpy(sq,"In what city or town was your first job ?");
                        break;
                    case 6:
                        strcpy(sq,"What was the name of your elementary school ?");
                        break;
                    case 7:
                        strcpy(sq,"In what city or town does your nearest sibling live ?");
                        break;
                    case 8:
                        strcpy(sq,"What is your pet's name ?");
                        break;
                }
                printf("Answer %d : ", NumberSq);
                scanf("%s",ans);
                break;    
            case 2:
                printf("Question %d : ", NumberSq);
                scanf("%s", sq);
                printf("Answer %d : ", NumberSq);
                scanf("%s",ans);
                break;
        }
        
        switch(NumberSq) {
            case 1 :
                strcpy(userSq.sq1, sq);
                strcpy(userSq.ans1, ans);
                break;
            case 2 :
                strcpy(userSq.sq2, sq);
                strcpy(userSq.ans2, ans);
                break;
            case 3 :
                strcpy(userSq.sq3, sq);
                strcpy(userSq.ans3, ans);
                break;
            default:
                break;	
        }
        NumberSq++;
    }
    /*questions and answers should be stored in the text files*/
}

/*******************************************************************************
 * Description
 * this function validates if the date time function is logical and valid with
 * the real world representation of time
 * INPUTS:
 * date_time_t
 * OUTPUTS:
 * -1 if invalid, 1 if valid
 * POST:
 * const array no change
*******************************************************************************/
int validate_date_time(const struct date_time time)
{
    /*test all the variable within time date to validate they are logical based
    on the real world representation of time*/
    if(time.month < MONTHS_LOWER ||
    time.month > MONTHS_UPPER ||
    time.day < DAYS_LOWER ||
    time.day >= DAYS_UPPER ||
    time.hour < HOURS_LOWER ||
    time.hour > HOURS_UPPER ||
    time.minute < MINUTES_LOWER ||
    time.minute >= MINUTES_UPPER)
    {
        return -1;
    }
    return 1;
}

/*******************************************************************************
 * Description
 * INPUTS:
 * what is required to input into this function
 * OUTPUTS:
 * what gets returned
 * POST:
 * what happens to pointers and data after the function
*******************************************************************************/
void validate_sq(const char user_ID[USER_MAX_NUM_LEN]) {
    char answer[ANSWER_MAX_LEN];
    int good_Answer = 0;
    printf("You have failed logging in three times.\n"
           "Please answer the 3 security questions to reset your password\n");
    while(good_Answer < 3) {
        printf("Security question\n"); /*security question should be stored in the txt file*/
        scanf("%s",answer);
        if(strcmp(answer,"answer") == 0) { 
            good_Answer++; 
            /*go to the next question in the text files*/
        }
        else { printf("Wrong answer\n"); }
    }
    change_password(user_ID);
}

/*******************************************************************************
 * Description
 * INPUTS:
 * what is required to input into this function
 * OUTPUTS:
 * what gets returned
 * POST:
 * what happens to pointers and data after the function
*******************************************************************************/
const char* encryption(int key, char string[])
{
    int i;
    if (key != 0)
    {
        for (i=0; (i<100 && string[i] != '\0'); i++)
        {
        /*j is the key, preferably a number.*/
        string[i] = string[i] + key;        
        }
        /*printf("Encryption Successful: %s\n", string);*/
    }
    else
    {
        key = 3;  
        for (i=0; (i<100 && string[i] != '\0'); i++)
        {
        /*j is the key, preferably a number.*/
        string[i] = string[i] + key;        
        }
        /*printf("Encryption Successful: %s\n", string);*/
    }
    /*Returns Key to be saved*/
    return string;
}
/*******************************************************************************
 * Description
 * INPUTS:
 * what is required to input into this function
 * OUTPUTS:
 * what gets returned
 * POST:
 * what happens to pointers and data after the function
*******************************************************************************/
const char* decryption(int key, char string[])
{
    int i;
    for (i=0; (i<100 && string[i] != '\0'); i++)
    {
        string[i] = string[i] - key;        
    }
    /*String is Decrypted*/
    /*printf("Decryption Successful: %s\n", string);*/
    return string;
}

/*******************************************************************************
 * This function inputs a transaction type and adds spaces at the end to make 
 * sure it is ready to print in printf format  
 * inputs:
 * - type[]
 * outputs:
 * none
 * post:
 * transaction type will be six chars longs with a null charater at the end
*******************************************************************************/
void format_trans_type(char type[])
{
    /*initlise incrementing variables*/
    int i, j = 0;
    /*interate through the flightcode untiil the end of the string is found*/
    for(i = 0; i < MAX_TYPE_LEN; i++)
    {
        if(type[i] == '\0')
        {
            /*fill the rest of the chars within the string as spaces to format
            the flight code to be printed the same no matter the size*/
            for(j = i; j < MAX_TYPE_LEN; j++)
            {
                type[j] = ' ';
            }
            type[MAX_TYPE_LEN] = '\0';
            return;
        }
    }
    type[MAX_TYPE_LEN] = '\0';
    return;
}
