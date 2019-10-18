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
/*comment and uncomment these to change the program modes*/
#define DEBUG
#define DEV

#define DEFINES "defined"
#define USER_MAX_NUM_LEN 6
#define USER_NUM_LETTER_LEN 2
#define USER_MAX_PW_LEN 32
#define USER_MAX_LVL_LEN 5
#define SQ_MAX_LEN 100
#define ANSWER_MAX_LEN 15
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
int create_sq(const char user_ID[USER_MAX_NUM_LEN]); /*seb*/
int trans_cmp(const struct date_time trans_dt, const struct date_time date_dt);
int validate_sq(const char user_ID[USER_MAX_NUM_LEN]); /*seb*/
int validate_date_time(const struct date_time time); /*james*/

const char* encryption(char key[], char string[]); /*walter*/
const char* decryption(char key[], char string[]); /*walter*/
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

    /*if dev mode is not active*/
    #ifndef DEV
        #ifdef DEBUG
        printf("USER/ADMIN MENU\n");
        #endif
        while(login_menu(logged_user) != 1);
    #endif

     /*if dev mode is active*/
     #ifdef DEV
        #ifdef DEBUG
        printf("DEV MENU\n");
        #endif
        strcpy(logged_user->user_lvl,"test");
    #endif
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
    printf("please enter a user name: \n");
    scanf("%s", userID);

    /*validate user ID*/
    printf("please enter your password: \n");
    scanf("%s", userPW);

    /*place into struct*/
    #ifdef DEBUG
    printf("USER NUM: %s\n"
        "USER PASSWORD: %s\n",
        userID,
        userPW);
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
    while(fptr != NULL)
    {
        /*fill the logger struct with temp data*/
        if(fread(&logger, sizeof(logged_user_t), 1, fptr) == 0)
        {
            printf("incorrect ID or password\n");
	    validate_sq(userID);
        }
        /*check the logger information against user input*/
        #ifdef DEBUG
        printf("compare passwords>%s : %s\ncompare user ID>%s : %s\n",
            decryption("crypt",logger.user_pw), userPW, 
            decryption("crypt",logger.user_num), userID);
        #endif
        if(strcmp(logger.user_pw, userPW) == 0 && 
            strcmp(logger.user_num, userID) == 0)
        {
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
        #ifdef DEBUG
        printf("entering dev menu");
        #endif
        dev_menu(user);
    }
    else if(strcmp(user->user_lvl,"admin") == 0)
    {
        #ifdef DEBUG
        printf("entering admin menu");
        #endif
        admin_menu(user);
    }
    else if(strcmp(user->user_lvl,"user") == 0)
    {
        #ifdef DEBUG
        printf("entering user menu");
        #endif
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

    double val = 0;
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
                    #ifdef DEBUG
                    printf("add user\n");
                    #endif
                    add_user(start);
                    printf("\nPrinting total users\n");
                    print_users(start);
                    break;
            case 2 :
                    #ifdef DEBUG
                    printf("remove user\n");
                    #endif
                    delete_user(start);
                    break;
            case 3 :
                    #ifdef DEBUG
                    printf("view a users statement\n");
                    #endif
                    printf("enter target users account number");
                    scanf("%s", user_ID);
                    print_statement(user_ID);
                    break;
            case 4 :
                    #ifdef DEBUG
                    printf("view balance\n");
                    #endif
                    printf("your balance is: $%.2lf\n", get_balance(user));
                    break;
            case 5 :
                    #ifdef DEBUG
                    printf("withdraw funds\n");
                    #endif
                    printf("Please enter how much you wish to withdraw:>");
                    scanf("%lf", &val);
                    withdraw(user, val);
                    break;
            case 6 :
                    #ifdef DEBUG
                    printf("depoit funds\n");
                    #endif
                    printf("Please enter how much you wish to deposit:>");
                    scanf("%lf", &val);
                    deposit(user, val);
                    break;
            case 7 :
                    #ifdef DEBUG
                    printf("transfer funds\n");
                    #endif
                    printf("what account ID would you like to transfer to>");
                    scanf("%s", user_ID);
                    printf("how much funds would like to transfer>");
                    scanf("%lf", &val);
                    transfer(user, user_ID, val);
                    break;
            case 8 :
                    #ifdef DEBUG
                    printf("change user password\n");
                    #endif
                    printf("enter target users account number");
                    scanf("%s", user_ID);
                    change_password(user_ID);
                    break;
            case 9 :
                    #ifdef DEBUG
                    printf("view all account numbers\n");
                    #endif
                    print_users(start);
                    break;
            case 10:
                    printf("logging out\n");
                    return;
	    case 11: 
                    printf("Encrypt; Key, String:\n");
		    encryption("crypt", poop);
                    break;
	    case 12:
                    printf("Decrypt; Key, String:\n");
		    decryption("crypt", poop);
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
                    #ifdef DEBUG
                    printf("add user\n");
                    #endif
                    add_user(start);
                    print_users(start);
                    break;
            case 2 :
                    #ifdef DEBUG
                    printf("remove user\n");
                    #endif
                    break;
            case 3 :
                    #ifdef DEBUG
                    printf("view a users statement\n");
                    #endif
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
                    #ifdef DEBUG
                    printf("view balance\n");
                    #endif
                    printf("%.2lf",get_balance(user));
                    break;
            case 2 :
                    #ifdef DEBUG
                    printf("withdraw funds\n");
                    #endif
                    printf("how much funds would like to withdraw>");
                    scanf("%lf", &val);
                    withdraw(user, val);
                    break;
            case 3 :
                    #ifdef DEBUG
                    printf("deposit funds\n");
                    #endif
                    printf("how much funds would like to deposit>");
                    scanf("%lf", &val);
                    deposit(user, val);
                    break;
            case 4 :
                    #ifdef DEBUG
                    printf("transfer funds\n");
                    #endif
                    printf("what account ID would you like to transfer to>");
                    scanf("%s", user_ID);
                    printf("how much funds would like to transfer>");
                    scanf("%lf", &val);
                    transfer(user, user_ID, val);
                    break;
            case 5 :
                    #ifdef DEBUG
                    printf("view user statement");
                    #endif
                    print_statement(user->user_num);
                    break;
            case 6 :
                    #ifdef DEBUG
                    printf("change password");
                    #endif
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

    #ifdef DEBUG
    printf("users ID:%s\n"
        "users PW:%s\n"
        "users level:%s\n"
        "users balance:%.2lf\n",
        user_num, user_pw, user_lvl, acc_balance);
    #endif
	
    users_t * it = user;
    
    /*check if this is the first user*/
    if(strcmp(it->user_lvl, "test") == 0)
    {
        strcpy(it->user_num, user_num);
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
        strcpy(it->next->user_num, user_num);
        strcpy(it->next->user_pw, user_pw);
        strcpy(it->next->user_lvl, user_lvl);
        it->next->acc_balance = acc_balance;
        it->next->next = NULL;
        create_sq(it->next->user_num);
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
        printf("%s\n", decryption("crypt",it->user_num));
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
    dt.hour = timeinfo->tm_hour;
    dt.minute = timeinfo->tm_min;

    #ifdef DEBUG
    printf("the local time is> %d/%d/%d %d:%d\n",
        dt.day,dt.month,dt.year,dt.hour,dt.minute);
    #endif
	    
    /*fill transaction information*/
    transaction_details.trans_dt = dt;
    strcpy(transaction_details.type, "deposit");
    transaction_details.principal = user->acc_balance;
    transaction_details.trans_val = value;
    transaction_details.acc_balance = 
        transaction_details.principal + transaction_details.trans_val;

    /*update account balance*/
    user->acc_balance = transaction_details.acc_balance;

    #ifdef DEBUG
    printf("principal: %.2lf\n"
        "transaction value: %.2lf\n"
        "account balance: %.2lf\n",
        transaction_details.principal, 
        transaction_details.trans_val,
        transaction_details.acc_balance);
    #endif
	
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

    #ifdef DEBUG
    printf("the local time is> %d/%d/%d %d:%d\n",
        dt.day,dt.month,dt.year,dt.hour,dt.minute);
    #endif
	
    /*check if user has enough balance to withdraw*/
    if(user->acc_balance < value)
    {
        printf("error: not enough funds within account");
        transaction_details.trans_dt = dt;
        strcpy(transaction_details.type, "low fund");
        transaction_details.principal = user->acc_balance;
        transaction_details.trans_val = -1 * value;
        transaction_details.acc_balance = user->acc_balance;

        #ifdef DEBUG
        printf("not enough funds to withdraw");
        #endif
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

    #ifdef DEBUG
    printf("principal: %.2lf\n"
        "transaction value: %.2lf\n"
        "account balance: %.2lf\n",
        transaction_details.principal, 
        transaction_details.trans_val,
        transaction_details.acc_balance);
    #endif
	
    /*open the file to fill the data base*/
    FILE *fptr = NULL;
    char file_name[USER_MAX_NUM_LEN + 5];
    strcpy(file_name, user->user_num);
    strcat(file_name, ".txt");
	
    #ifdef DEBUG
    printf("the file name is>%s",file_name);
    #endif
	
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

    #ifdef DEBUG
    printf("the local time is> %d/%d/%d %d:%d\n",
        dt.day,dt.month,dt.year,dt.hour,dt.minute);
    #endif	
	
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
        transaction_details.trans_dt = dt;
        strcpy(transaction_details.type, "low funds");
        transaction_details.principal = user->acc_balance;
        transaction_details.trans_val = -1 * value;
        transaction_details.acc_balance = user->acc_balance;
        return user->acc_balance;
	    
        #ifdef DEBUG
        printf("not enough funds to transfer");
        #endif	    
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
    
    #ifdef DEBUG
    printf("account out account amounts>\n"
        "principal: %.2lf\n"
        "transaction value: %.2lf\n"
        "account balance: %.2lf\n",
        transaction_details.principal, 
        transaction_details.trans_val,
        transaction_details.acc_balance);
    #endif	
	
    /*write to user transaction database*/
    fptr = NULL;
    char file_name[USER_MAX_NUM_LEN + 5];
    strcpy(file_name, user->user_num);
    strcat(file_name, ".txt");\
	    
    #ifdef DEBUG
    printf("the file name is>%s",file_name);
    #endif	    
	    
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
        if(strcmp(decryption("crypt", it->user_num), target_acc) == 0)
        {
            break;
        }
        it = it->next;
    }
	
    transaction_details.trans_dt = dt;
    strcpy(transaction_details.type, "transaction in");
    transaction_details.principal = it->acc_balance;
    transaction_details.trans_val = 1 * value;
    transaction_details.acc_balance = 
        transaction_details.principal + transaction_details.trans_val;       

    /*update target user account balance*/
    it->acc_balance = transaction_details.acc_balance;

    #ifdef DEBUG
    printf("account in account amounts>\n"
        "principal: %.2lf\n"
        "transaction value: %.2lf\n"
        "account balance: %.2lf\n",
        transaction_details.principal, 
        transaction_details.trans_val,
        transaction_details.acc_balance);
    #endif	
	
    /*write transaction history on reciever*/
    fptr = NULL;
    strcpy(file_name, it->user_num);
    strcat(file_name, ".txt");
    fptr = fopen(file_name, "a");

    #ifdef DEBUG
    printf("the file name is>%s",file_name);
    #endif	
	
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

    #ifdef DEBUG
    printf("the file name is>%s",file_name);
    #endif	
	
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
	    
        #ifdef DEBUG
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
        #endif
	    
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
    char user_num[USER_MAX_NUM_LEN];
    printf("what is the user account number you would like to delete: ");
    scanf("%s", user_num);

    users_t * temp = NULL;
    users_t * it = user;

    #ifdef DEBUG	
    printf("%s : %s\n", it->user_num, user_num);
    #endif
	
    /*edge case*/
    /*check statement if first user*/
    if(strcmp(it->user_num, user_num) == 0)
    {
        user = it->next;
        user->next = NULL;
    }
    
    /*search through linked list*/
    while(it->next != NULL)
    {
        #ifdef DEBUG	
        printf("%s : %s\n", it->next->user_num, user_num);
        #endif
	    
        if(strcmp(it->next->user_num, user_num) == 0)
        {
            temp = it->next;
            /*second edge case testing for end of linked list*/
            if(temp->next != NULL)
            {
                it->next = temp->next;
            }
            /*if user is at end of list just delete the last entry by setting
            pointer being tested to NULL*/
            else
            {
                it->next = NULL;
                break;
            }
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
 * This function stores all users from users.txt into the users_t linked list
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
    /*test if userID is longer then the maximum determined size if it is 
    return an error*/
    if((int)strlen(user_ID) > USER_MAX_NUM_LEN)
    {
        return -1;
    }
    /*iterate through the letters of the userID checking they are capiital
	letters*/
    for(i = 0; i < USER_NUM_LETTER_LEN; i++)
    {
        /*test if the userID letters are between A - Z or 65 - 90*/
        if(user_ID[i] < 'A' || user_ID[i] > 'Z')
        {
            return -1;
        }
    }
    for(i = USER_NUM_LETTER_LEN; i < USER_MAX_NUM_LEN; i++)
    {
        /*test if the userID is at the end of the string as userID can 
        be less then 6 chars*/
        if(user_ID[i] == '\0' && i > USER_NUM_LETTER_LEN)
        {
            return 1;
        }
        /*test if the userID numbers are between '0' - '9' or 48 - 57*/
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
 * This function asks the user to create the security questions and the answers
 * corresponding with the questions, are stored in a file
 * INPUTS:
 * char user_ID
 * OUTPUTS:
 * returns -1 if wasn't able to open the file, returns 1 otherwise
 * POST:
 * const array no change
*******************************************************************************/
int create_sq(const char user_ID[USER_MAX_NUM_LEN]) { 
    user_security_questions_t userSq;

    char sq1[SQ_MAX_LEN];
    char ans1[ANSWER_MAX_LEN];
    char sq2[SQ_MAX_LEN];
    char ans2[ANSWER_MAX_LEN];
    char sq3[SQ_MAX_LEN];
    char ans3[ANSWER_MAX_LEN];
    char file_name[USER_MAX_NUM_LEN + 5];

    printf("Choose 3 security questions:\n");

    printf("Question 1 : ");
    fgets(sq1, SQ_MAX_LEN, stdin); 
    printf("Answer 1 : ");
    fgets(ans1, ANSWER_MAX_LEN, stdin); 

    printf("Question 2 : ");
    fgets(sq2, SQ_MAX_LEN, stdin); 
    printf("Answer 2 : ");
    fgets(ans2, ANSWER_MAX_LEN, stdin); 

    printf("Question 3 : ");
    fgets(sq3, SQ_MAX_LEN, stdin); 
    printf("Answer 3 : ");
    fgets(ans3, ANSWER_MAX_LEN, stdin); 

    strcpy(userSq.sq1, sq1);
    strcpy(userSq.ans1, ans1);
    strcpy(userSq.sq2, sq2);
    strcpy(userSq.ans2, ans2);
    strcpy(userSq.sq3, sq3);
    strcpy(userSq.ans3, ans3);

    FILE *fptr= NULL;
    strcpy(file_name, user_ID);
    strcat(file_name, "sq.txt");
    fptr=fopen(file_name,"wb");
    if(fptr == NULL) {
        printf("error when opening data base");
        return -1;
    }
    fwrite(&userSq, sizeof(user_security_questions_t), 1, fptr);
    fclose(fptr);
    return 1;
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
 * This function asks the security questions to the user and verify if it 
 * matches with the one from the files
 * INPUTS:
 * char user_ID
 * OUTPUTS:
 * returns -1 if wasn't able to open the file, returns 1 otherwise
 * POST:
 * const array no change
*******************************************************************************/
int validate_sq(const char user_ID[USER_MAX_NUM_LEN]) {
    user_security_questions_t userSq;
    char answer1[ANSWER_MAX_LEN];
    char answer2[ANSWER_MAX_LEN];
    char answer3[ANSWER_MAX_LEN];
    char file_name[USER_MAX_NUM_LEN + 5];

    printf("You have failed logging in\n"
           "Please answer the 3 security questions to reset your password\n");
    
    FILE *fptr= NULL;
    strcpy(file_name, user_ID);
    strcat(file_name, "sq.txt");
    fptr=fopen(file_name,"rb");

    if(fptr == NULL)
    {
        printf("mem error file location doesnt exist");
    }

    while(fptr != NULL){
        fread(&userSq, sizeof(user_security_questions_t), 1, fptr);
        printf("Question 1 : %s", userSq.sq1);
        fgets(answer1, ANSWER_MAX_LEN, stdin);;
        printf("Question 2 : %s", userSq.sq2);
        fgets(answer2, ANSWER_MAX_LEN, stdin);
        printf("Question 3 : %s", userSq.sq3);
        fgets(answer3, ANSWER_MAX_LEN, stdin);
        if( strcmp(userSq.ans1, answer1) == 0 &&
            strcmp(userSq.ans2, answer2) == 0 && 
            strcmp(userSq.ans3, answer3) == 0 ) 
        {
            fclose(fptr);
            return 1;
        }
        if(strcmp(userSq.ans1, answer1) != 0) {
            printf("Answer 1 is incorrect\n");
        }
        if(strcmp(userSq.ans2, answer2) != 0) {
            printf("Answer 2 is incorrect\n");
        }
        if(strcmp(userSq.ans3, answer3) != 0) {
            printf("Answer 3 is incorrect\n");
        }
        printf("Please try again\n");
        
    }
    change_password(user_ID);
    return -1;
}

/*******************************************************************************
 * Description
 * INPUTS:
 * char key[] (User ID), char string[]
 * OUTPUTS:
 * Returns the encrypted string.
 * POST:
 * Key does not change, string changes to encrypted string.
*******************************************************************************/
const char* encryption(char key[], char string[])
{
    int i, j;
    char strKey[strlen(key)], encString[strlen(string)];
    
    for (i = 0, j = 0; i < strlen(string); i++, j++)
    {
        /*strKey will become key repeated until the same length as string*/ 
        if (j == strlen(key))
        {
            j = 0;
        }
        strKey[i] = key[j];
    }
    strKey[i] = '\0';
    
    /*For each character until the end, add the ASCII value to string*/
    for (i = 0; (i < 100 && string[i] != '\0'); i++)
    {
        encString[i] = string[i] + (int)strKey[i];
    }
    encString[i] = '\0';
    /*Note to self: Can't return local pointers*/
    string = encString;
    /*Returns encrypted string to be saved*/
    return string;
}
/*******************************************************************************
 * Description
 * INPUTS:
 * char key[] (User ID), char string[]
 * OUTPUTS:
 * Returns the decrypted string.
 * POST:
 * Key does not change, string changes to decrypted string.
*******************************************************************************/
const char* decryption(char key[], char string[])
{
    int i, j;
    char strKey[strlen(key)], decString[strlen(string)];
    
    for (i = 0, j = 0; i < strlen(string); i++, j++)
    {
        /*strKey will become key repeated until the same length as string*/ 
        if (j == strlen(key))
        {
            j = 0;
        }
        strKey[i] = key[j];
    }
    strKey[i] = '\0';
    
    /*For each character until the end, remove the ASCII value from encString*/
    for (i = 0; (i < 100 && string[i] != '\0'); i++)
    {
        decString[i] = string[i] - (int)strKey[i];
    }
    decString[i] = '\0';
    /*Note to self: Can't return local pointers*/
    string = decString;
    /*Returns decrypted string to be saved*/
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
