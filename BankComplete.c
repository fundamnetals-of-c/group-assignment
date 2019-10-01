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
#include <string.h> /*strlen strcmp strcpy*/
#include <stdlib.h> 

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
}user_security_question_t;
/*******************************************************************************
 * Function prototypes - do NOT change the given prototypes. However you may
 * define your own functions if required.
*******************************************************************************/
int user_login(void); /*tam*/
int login_menu(logged_user_t * logged_user); /*james*/
void print_menu(logged_user_t * user); /*tam*/
void dev_menu(logged_user_t * user); /*james*/
void admin_menu(logged_user_t * user); /*james*/
void user_menu(logged_user_t * user); /*james*/

void print_users(users_t * user);

int add_user(users_t * user); /*james*/
int edit_user(users_t * user); /*james*/
int deposit(double value); /*tam*/
int withdraw(double value); /*tam*/
int transfer(double value); /*tam*/
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
int user_login(void)
{
return 1;
/*
	int i;
	char user[30], pass[30], perm[30];
	FILE *ftpr = NULL;
	ftpr = fopen("login.txt", "r");
	
	printf("Username: ");
	scanf("%s", user);
	printf("Password: ");
	scanf("%s", pass);

	
	for (i = 0; fptr == NULL; i++) {
		fscan(fptr, "%s", user_ID);
		validate_user_ID(user_ID);
		strcomp with username in file
		Do the same for pass
	}

	fscan(fptr, "%s", perm);
	return user.perm;
*/
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
    strcpy(logged_user->user_lvl,"test");
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
/*debugging*/
/*printf("%s : %s\n", logger.user_num, userID);*/

if(strcmp(logger.user_pw, userPW) == 0)
{
printf("Welcome\n");
return 1;
}
    }
    /*check against database*/
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

    int user_input = NULL;
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
	"12. Decrypt\n");
    
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
                    delete_user(start);
                    break;
            case 3 :
                    printf("view a users statement\n");
                    break;
            case 4 :
                    printf("view balance\n");
                    break;
            case 5 :
                    printf("withdraw funds\n");
                    break;
            case 6 :
                    printf("deposit funds\n");
                    break;
            case 7 :
                    printf("transfer funds\n");
                    break;
            case 8 :
                    printf("change password\n");
                    return;
            case 9 :
                    printf("view all account numbers\n");
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

    int user_input = NULL;
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
    int user_input;
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
/*******************************************************************************
 * Description
 * INPUTS:
 * what is required to input into this function
 * OUTPUTS:
 * what gets returned
 * POST:
 * what happens to pointers and data after the function
*******************************************************************************/

int deposit(double value)
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
int withdraw(double value)
{
/*
double principal;
double withdraw;
double new;
*/
/*need to initialise principal amount --> comes from admin*/
  /*  printf("Enter amount to be withdrawn\n");
    scanf("%lf",&withdraw);

    new = principal - withdraw;

    if (withdraw > principal);
        printf("Cannot withdraw that amount of money, Enter a lower amount");
    printf("The total amount is: %lf", new);
*/
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
int transfer(double value)
{
/*
double transfer
double principal

printf("Enter the account number you want to transfer to");
printf("Enter the amoount you want to transfer");
scanf("%lf", &transfer);*/



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
 * what is required to input into this function
 * OUTPUTS:
 * what gets returned
 * POST:
 * what happens to pointers and data after the function
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
/*logged_user_t logged_user_test = {user->user_num, user->user_pw, user->user_lvl, user->acc_balance};*/
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
 * what is required to input into this function
 * OUTPUTS:
 * what gets returned
 * POST:
 * what happens to pointers and data after the function
*******************************************************************************/
int validate_user_pw(char user_pw[])
{
return 1;
}

void create_sq() { /*still need to find a proper way to code the function*/
 	/*user_security_questions_t user;
	printf("Choose 3 security questions:\n");
	printf("Question 1 : ");
	scanf("%s", userSq.sq1);
	printf("Answer 1 : ");
	scanf("%s", userSq.ans1);
	printf("Question 2 : ");
	scanf("%s", userSq.sq2);
	printf("Answer 2 : ");
	scanf("%s", userSq.ans2);
	printf("Question 3 : ");
	scanf("%s", userSq.sq3);
	printf("Answer 3 : ");
	scanf("%s", userSq.ans3);*/
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
	char answer[124];
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
