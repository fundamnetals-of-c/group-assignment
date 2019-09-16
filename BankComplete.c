/*******************************************************************************
 * 48430 Fundamentals of C Programming - Assignment 3
 * Name: James Walsh
 * Student ID: 99143152
 * Name: James Walsh
 * Student ID: 
 * Name: 
 * Student ID: 
 * Name: 
 * Student ID: 
 * Name: 
 * Student ID: 
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

#define DEIFNES "defined"

/*******************************************************************************
 * List structs - you may define struct date_time and struct flight only. Each
 * struct definition should have only the fields mentioned in the assignment
 * description.
*******************************************************************************/
typedef struct user
{
    /*fill with user data variables*/
} user_t;

/*******************************************************************************
 * Function prototypes - do NOT change the given prototypes. However you may
 * define your own functions if required.
*******************************************************************************/
int user_login(void); /*tam*/
void print_menu(const struct user_t user); /*tam*/

int add_user(void); /*james*/
int edit_user(struct user_t user); /*james*/
int deposit(double value); /*tam*/
int withdraw(double value); /*tam*/
int transfer(double value); /*tam*/
void print_statement(const struct user_t user); /*terry also compression*/
int delete_user(const struct user_t user); /*james*/
int store_users(const struct user_t user); /*james*/
int read_users(struct user_t users[]); /*james*/

int validate_user_ID(char user_ID[]); /*james*/
int validate_user_pw(char user_pw[]); /*walter*/
int validate_sq(char user_ans[]); /*seb*/
int validate_withdraw(/*fill*/); /*tam*/

int encription(char string[]); /*seb and walter*/
int decription(char string[]); /*seb and walter*/
/*to be extended*/

/*******************************************************************************
 * Main
*******************************************************************************/
int main(void)
{
    /*SETUP OF VARIABLES USED IN THE MAJORITY OF THE CODE*/
	
    
    return 0;
}

/*******************************************************************************
 * Description
 * INPUTS:
 * what is reuqired to input into this function
 * OUTPUTS:
 * what gets returned
 * POST:
 * what happens to pointers and data after the function
*******************************************************************************/
int user_login(void)
/*******************************************************************************
 * Description
 * INPUTS:
 * what is reuqired to input into this function
 * OUTPUTS:
 * what gets returned
 * POST:
 * what happens to pointers and data after the function
*******************************************************************************/
void print_menu(const struct user_t user)

/*******************************************************************************
 * Description
 * INPUTS:
 * what is reuqired to input into this function
 * OUTPUTS:
 * what gets returned
 * POST:
 * what happens to pointers and data after the function
*******************************************************************************/
int add_user(void)

/*******************************************************************************
 * Description
 * INPUTS:
 * what is reuqired to input into this function
 * OUTPUTS:
 * what gets returned
 * POST:
 * what happens to pointers and data after the function
*******************************************************************************/
int edit_user(struct user_t user)

/*******************************************************************************
 * Description
 * INPUTS:
 * what is reuqired to input into this function
 * OUTPUTS:
 * what gets returned
 * POST:
 * what happens to pointers and data after the function
*******************************************************************************/
int deposit(double value)

/*******************************************************************************
 * Description
 * INPUTS:
 * what is reuqired to input into this function
 * OUTPUTS:
 * what gets returned
 * POST:
 * what happens to pointers and data after the function
*******************************************************************************/
int withdraw(double value)

/*******************************************************************************
 * Description
 * INPUTS:
 * what is reuqired to input into this function
 * OUTPUTS:
 * what gets returned
 * POST:
 * what happens to pointers and data after the function
*******************************************************************************/
int transfer(double value)

/*******************************************************************************
 * Description
 * INPUTS:
 * what is reuqired to input into this function
 * OUTPUTS:
 * what gets returned
 * POST:
 * what happens to pointers and data after the function
*******************************************************************************/
void print_statement(const struct user_t user)

/*******************************************************************************
 * Description
 * INPUTS:
 * what is reuqired to input into this function
 * OUTPUTS:
 * what gets returned
 * POST:
 * what happens to pointers and data after the function
*******************************************************************************/
int delete_user(const struct user_t user)

/*******************************************************************************
 * Description
 * INPUTS:
 * what is reuqired to input into this function
 * OUTPUTS:
 * what gets returned
 * POST:
 * what happens to pointers and data after the function
*******************************************************************************/
int store_users(const struct user_t user)

/*******************************************************************************
 * Description
 * INPUTS:
 * what is reuqired to input into this function
 * OUTPUTS:
 * what gets returned
 * POST:
 * what happens to pointers and data after the function
*******************************************************************************/
int read_users(struct user_t users[])


/*******************************************************************************
 * Description
 * INPUTS:
 * what is reuqired to input into this function
 * OUTPUTS:
 * what gets returned
 * POST:
 * what happens to pointers and data after the function
*******************************************************************************/
int validate_user_ID(char user_ID[])

/*******************************************************************************
 * Description
 * INPUTS:
 * what is reuqired to input into this function
 * OUTPUTS:
 * what gets returned
 * POST:
 * what happens to pointers and data after the function
*******************************************************************************/
int validate_user_pw(char user_pw[])
/*******************************************************************************
 * Description
 * INPUTS:
 * what is reuqired to input into this function
 * OUTPUTS:
 * what gets returned
 * POST:
 * what happens to pointers and data after the function
*******************************************************************************/
int validate_sq(char user_ans[])

/*******************************************************************************
 * Description
 * INPUTS:
 * what is reuqired to input into this function
 * OUTPUTS:
 * what gets returned
 * POST:
 * what happens to pointers and data after the function
*******************************************************************************/
int validate_withdraw(/*fill*/)


/*******************************************************************************
 * Description
 * INPUTS:
 * what is reuqired to input into this function
 * OUTPUTS:
 * what gets returned
 * POST:
 * what happens to pointers and data after the function
*******************************************************************************/
int encription(char string[])

/*******************************************************************************
 * Description
 * INPUTS:
 * what is reuqired to input into this function
 * OUTPUTS:
 * what gets returned
 * POST:
 * what happens to pointers and data after the function
*******************************************************************************/
int decription(char string[])