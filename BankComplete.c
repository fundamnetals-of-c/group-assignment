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
#define USER_MAX_PW_LEN 32
#define USER_MAX_LVL_LEN 5
#define SQ_MAX_LEN 30
#define ANSWER_MAX_LEN 10

/*******************************************************************************
 * List structs - you may define struct date_time and struct flight only. Each
 * struct definition should have only the fields mentioned in the assignment
 * description.
*******************************************************************************/
typedef struct users
{
    /*fill with user data variables*/
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
    char type[11+1];
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
 * Function prototypes - do NOT change the given prototypes. However you may
 * define your own functions if required.
*******************************************************************************/
int login_menu(logged_user_t * logged_user); /*james*/
void print_menu(logged_user_t * user); /*james*/
void dev_menu(logged_user_t * user); /*james*/
void admin_menu(logged_user_t * user); /*james*/
void user_menu(logged_user_t * user); /*james*/


void print_users(users_t * user);

int add_user(users_t * user); /*james*/
int edit_user(users_t * user); /*james*/
double get_balance(logged_user_t * user); /*james*/
int deposit(logged_user_t * user, double value); /*tam*/
int withdraw(logged_user_t * user, double value); /*tam*/
int transfer(logged_user_t * user, 
                char target_acc[USER_MAX_NUM_LEN],
                double value); /*tam*/
void print_statement(users_t * user); /*terry also compression*/
int delete_user(users_t * user); /*james*/
int store_users(users_t * user); /*james*/
int read_users(users_t * users); /*james*/

int validate_user_ID(char user_ID[]); /*james*/
int validate_user_pw(char user_pw[]); /*walter*/
void create_sq(); /*seb*/
void validate_sq(); /*seb*/
int validate_withdraw(/*fill*/); /*tam*/

int encryption(int key, char string[]); /*seb and walter*/
void decryption(int key, char string[]); /*seb and walter*/
/*to be extended*/

/*******************************************************************************
 * Main
*******************************************************************************/
int main(void)
{
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

    /*SETUP OF VARIABLES USED IN THE MAJORITY OF THE CODE*/
    
    
    while(login_menu(logged_user) != 1)

printf("your user name is: %s\n", logged_user->user_num);
printf("your password is: %s\n", logged_user->user_pw);
printf("your user level is: %s\n", logged_user->user_lvl);

    print_menu(logged_user);
    
    return 0;
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
int login_menu(logged_user_t * logged_user)
{
    char userID[USER_MAX_NUM_LEN + 1];
    char userPW[USER_MAX_PW_LEN + 1];
    printf("please enter a user name: ");
    scanf("%s", userID);

    /*validate user ID*/
    printf("please enter your password: ");
    scanf("%s", userPW);

/*place into struct*/
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
        if(fread(&logger, sizeof(logged_user_t), 1, fptr) == 0)
        {
            printf("incorrect ID or password\n");
            return -1;
        }
        if(strcmp(logger.user_pw, userPW) == 0)
        {
            strcpy(logged_user->user_lvl,"test");
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
 * INPUTS:
 * what is required to input into this function
 * OUTPUTS:
 * what gets returned
 * POST:
 * what happens to pointers and data after the function
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

void dev_menu(logged_user_t * user)
{

    users_t * start = NULL;
    start = malloc(sizeof(users_t));
char poop[8] = "string";

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
                    break;
            case 4 :
                    printf("view balance\n");
                    printf("your balance is: $%.2lf\n", get_balance(user));
                    break;
            case 5 :
                    printf("withdraw funds\n");
printf("Please enter how much you wish to withdraw: ");
scanf("%lf", &val);
withdraw(user, val);
                    break;
            case 6 :
                    printf("deposit funds\n");
printf("Please enter how much you wish to deposit: ");
scanf("%lf", &val);
deposit(user, val);
                    break;
            case 7 :
                    printf("transfer funds\n");
                    break;
            case 8 :
                    printf("change password\n");
                    return;
            case 9 :
                    printf("view all account numbers\n");
print_users(start);
                    return;
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

void user_menu(logged_user_t * user)
{
    int user_input -1;
    while(1)
    {
        printf("\n"
        "1. view balance\n"
        "2. withdraw funds\n"
        "3. deposit funds\n"
        "4. transfer funds\n"
        "5. log out\n");
    
        scanf("%d", &user_input);
        switch(user_input)
        {
            case 1 :
                    printf("view balance\n");
                    break;
            case 2 :
                    printf("withdraw funds\n");
                    break;
            case 3 :
                    printf("deposit funds\n");
                    break;
            case 4 :
                    printf("transfer funds\n");
                    break;
            case 5 :
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
 * INPUTS:
 * what is required to input into this function
 * OUTPUTS:
 * what gets returned
 * POST:
 * what happens to pointers and data after the function
*******************************************************************************/
int add_user(users_t * user)
{
    char user_num[USER_MAX_NUM_LEN + 1];
    char user_pw[USER_MAX_PW_LEN + 1];
    char user_lvl[USER_MAX_LVL_LEN + 1];
    double acc_balance;


    /*entering user data*/
    printf("Enter user information\n");
    printf("Enter the new user number: \n");
    scanf("%s", user_num);
    /*validate*/
    printf("Enter the new user password: \n"); /*should this be done upon first sign in?*/
    scanf("%s", user_pw);
/*validate*/
    printf("Enter the user level");
/*validate*/
    scanf("%s", user_lvl);
    printf("Enter user initial account balance");
    scanf("%lf", &acc_balance);

    users_t * it = user;
    
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
        store_users(it->next);
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
int edit_user(users_t * user)
{
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
void print_users(users_t * user)
{
    users_t * it = user;

while(it != NULL){
printf("%s\n", it->user_num);
it = it->next;
}
}

double get_balance(logged_user_t * user)
{
    return user->acc_balance;
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

int deposit(logged_user_t * user, double value)
{
/*

double principal;
double deposit;
double new;
*/
/*need to initialise principal amount --> comes from admin*/
  /*  printf("Enter amount to be deposited");
    scanf("%lf", &deposit);

    new = principal + deposit;

    printf(" The total amount is: %lf", new);
*/
/*setting up the structs to fill date time and transaction information*/
    date_time_t dt;
    transaction_details_t transaction_details;    

    time_t rawtime;
    struct tm * timeinfo;

    time ( &rawtime );
    timeinfo = localtime ( &rawtime );

    dt.year = timeinfo->tm_year + 1900;
    dt.month = timeinfo->tm_mon + 1;
    dt.day = timeinfo->tm_mday;
    dt.minute = timeinfo->tm_min;

    transaction_details.trans_dt = dt;
    strcpy(transaction_details.type, "deposit");
    transaction_details.principal = user->acc_balance;
    transaction_details.trans_val = value;
    transaction_details.acc_balance = 
        transaction_details.principal + transaction_details.trans_val;

    user->acc_balance = transaction_details.acc_balance;

    FILE *fptr = NULL;
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
int withdraw(logged_user_t * user, double value)
{
    date_time_t dt;
    transaction_details_t transaction_details;    

    time_t rawtime;
    struct tm * timeinfo;

    time ( &rawtime );
    timeinfo = localtime ( &rawtime );

    dt.year = timeinfo->tm_year + 1900;
    dt.month = timeinfo->tm_mon + 1;
    dt.day = timeinfo->tm_mday;
    dt.minute = timeinfo->tm_min;

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
    user->acc_balance = transaction_details.acc_balance;
    
    FILE *fptr = NULL;
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
    return user->acc_balance;
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
int transfer(logged_user_t * user, char target_acc[], double value)
{
    date_time_t dt;
    transaction_details_t transaction_details; 
    logged_user_t logger;   

    time_t rawtime;
    struct tm * timeinfo;

    time ( &rawtime );
    timeinfo = localtime ( &rawtime );

    dt.year = timeinfo->tm_year + 1900;
    dt.month = timeinfo->tm_mon + 1;
    dt.day = timeinfo->tm_mday;
    dt.minute = timeinfo->tm_min;

    FILE *fptr = NULL;
    fptr = fopen("users.txt","r");

    if(fptr == NULL)
    {
        printf("mem error file location doesnt exsist");
    }

    while(fptr != NULL)
    {
        if(fread(&logger, sizeof(logged_user_t), 1, fptr) == 0)
        {
            printf("Invalid account ID\n");
            return -1;
        }
        if(strcmp(logger.user_num, target_acc) == 0)
        {
            fclose(fptr);
            break;
        }
    }
    /*fill payee transaction details*/
    /*dont fill and respond with low fund if there isnt enough funds*/
    if(user->acc_balance < value)
    {
        printf("error: not enough funds within account");
        transaction_details.trans_dt = dt;
        strcpy(transaction_details.type, "low funds");
        transaction_details.principal = user->acc_balance;
        transaction_details.trans_val = -1 * value;
        transaction_details.acc_balance = user->acc_balance;
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
    user->acc_balance = transaction_details.acc_balance;

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
void print_statement(users_t * user)
{
}
/*******************************************************************************
 * Description
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
 * INPUTS:
 * what is required to input into this function
 * OUTPUTS:
 * what gets returned
 * POST:
 * what happens to pointers and data after the function
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
            while(it->next != NULL)
            {
                it = it->next;
            }
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
 * INPUTS:
 * what is required to input into this function
 * OUTPUTS:
 * what gets returned
 * POST:
 * what happens to pointers and data after the function
*******************************************************************************/
int validate_user_ID(char user_ID[])
{
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
int validate_user_pw(char user_pw[])
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
    } else if ((lower < 1) || (upper < 1) || (digit < 1) || (special < 1)) {
        printf("Please use at least 1 of Lower & Upper Case, Number and special characters\n");
        return -1;
    }
    
    return (lower + upper + digit + special);
}

void create_sq() { 
 	user_security_questions_t userSq;
 	char sq[SQ_MAX_LEN];
	char ans[ANSWER_MAX_LEN];
	int NumberSq = 1;
	printf("Choose 3 security questions:\n");
	while(NumberSq < 4 ) {
		printf("Question %d : ", NumberSq);
		scanf("%s", sq);
		printf("Answer %d : ", NumberSq);
		scanf("%s",ans);
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
 * INPUTS:
 * what is required to input into this function
 * OUTPUTS:
 * what gets returned
 * POST:
 * what happens to pointers and data after the function
*******************************************************************************/
void validate_sq() {
	char answer[ANSWER_MAX_LEN];
	int good_Answer = 0;
	/*FILE* fp = fopen(filename,"r");*/
	while(good_Answer < 3) {
		printf("security question\n");
		scanf("%s",answer);
		if(strcmp(answer," security answer") == 0) { 
			good_Answer++; 
			/*go to the next question in the text files*/
		}
		else { printf("Wrong answer\n"); }
	}
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
int validate_withdraw(/*fill*/)
{
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
int encryption(int key, char string[])
{
    int i;
    if (key != 0)
    {
        for (i=0; (i<100 && string[i] != '\0'); i++)
        {
        /*j is the key, preferably a number.*/
        string[i] = string[i] + key;        
        }
        printf("Encryption Successful: %s\n", string);
    }
    else
    {
        key = 3;  
        for (i=0; (i<100 && string[i] != '\0'); i++)
        {
        /*j is the key, preferably a number.*/
        string[i] = string[i] + key;        
        }
        printf("Encryption Successful: %s\n", string);
    }
    /*Returns Key to be saved*/
    return key;
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
void decryption(int key, char string[])
{
    int i;
    for (i=0; (i<100 && string[i] != '\0'); i++)
    {
        string[i] = string[i] - key;        
    }
    /*String is Decrypted*/
    printf("Decryption Successful: %s\n", string);
}
