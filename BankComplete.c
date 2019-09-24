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


/*******************************************************************************
 * List structs - you may define struct date_time and struct flight only. Each
 * struct definition should have only the fields mentioned in the assignment
 * description.
*******************************************************************************/
typedef struct user
{
    /*fill with user data variables*/
    char user_num[USER_MAX_NUM_LEN + 1];
    char user_pw[USER_MAX_PW_LEN + 1];
    char user_lvl[USER_MAX_LVL_LEN + 1];
    double acc_balance;
    struct user * next;
} user_t;

/*******************************************************************************
 * Function prototypes - do NOT change the given prototypes. However you may
 * define your own functions if required.
*******************************************************************************/
int user_login(void); /*tam*/
void login_menu(user_t * user);
void print_menu(user_t * user); /*tam*/
void admin_menu(user_t * user);

void print_users(user_t * user);

int add_user(user_t * user); /*james*/
int edit_user(user_t * user); /*james*/
int deposit(double value); /*tam*/
int withdraw(double value); /*tam*/
int transfer(double value); /*tam*/
void print_statement(user_t * user); /*terry also compression*/
int delete_user(user_t * user); /*james*/
int store_users(user_t * user); /*james*/
int read_users(user_t * users); /*james*/

int validate_user_ID(char user_ID[]); /*james*/
int validate_user_pw(char user_pw[]); /*walter*/
void validate_sq(); /*seb*/
int validate_withdraw(/*fill*/); /*tam*/

int encryption(char string[]); /*seb and walter*/
int decryption(char string[]); /*seb and walter*/
/*to be extended*/

/*******************************************************************************
 * Main
*******************************************************************************/
int main(void)
{
    user_t * start = NULL;
    start = malloc(sizeof(user_t));

    if(start == NULL)
    {
        printf("mem error");
        return -1;
    }
    start->next = NULL;

    /*SETUP OF VARIABLES USED IN THE MAJORITY OF THE CODE*/
    
    
    login_menu(start);

printf("your user name is: %s\n", start->user_num);
printf("your password is: %s\n", start->user_pw);
printf("your user level is: %s\n", start->user_lvl);

    print_menu(start);
    
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
void login_menu(user_t * user)
{
    char userID[USER_MAX_NUM_LEN + 1];
    char userPW[USER_MAX_PW_LEN + 1];
    printf("please enter a user name: ");
    scanf("%s", userID);
    strcpy(user->user_num,userID);
    /*validate user ID*/
    printf("please enter your password: ");
    scanf("%s", userPW);
    strcpy(user->user_pw,userPW);
    strcpy(user->user_lvl,"admin");
    /*check against database*/
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
void print_menu(user_t * user)
{ 
    
    if(strcmp(user->user_lvl,"admin") == 0)
    {
        admin_menu(user);
    }

        
}

void admin_menu(user_t * user)
{
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
                    add_user(user);
print_users(user);
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
 * INPUTS:
 * what is required to input into this function
 * OUTPUTS:
 * what gets returned
 * POST:
 * what happens to pointers and data after the function
*******************************************************************************/
int add_user(user_t * user)
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

    user_t * it = user;
    
    if(strcmp(it->user_lvl, "first") == 0)
    {
    strcpy(it->user_num, user_num);
    strcpy(it->user_pw, user_pw);
    strcpy(it->user_lvl, user_lvl);
    it->acc_balance = acc_balance;
        }
    else
    {
        while(it->next != NULL)
    {
        it = it->next;
    }
    it->next = malloc(sizeof(user_t));
    /*entering user data into struct*/
    strcpy(it->next->user_num, user_num);
    strcpy(it->next->user_pw, user_pw);
    strcpy(it->next->user_lvl, user_lvl);
    it->next->acc_balance = acc_balance;
    it->next->next = NULL;
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
int edit_user(user_t * user)
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
void print_users(user_t * user)
{
    user_t * it = user;

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
void print_statement(user_t * user)
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
int delete_user(user_t * user)
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
int store_users(user_t * user)
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
int read_users(user_t * users)
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
int encryption(char string[])
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
int decryption(char string[])
{
return 1;
}