#include "TP_main.h"
#include "Question1.h"
#include "Question2.h"
#include "Question3.h"
#include "Question4.h"
#include "Question5.h"
#include "Question6.h"

// Global status for Q4 however this means that this program is not ready for multithreading
int status = 0;

int main(){
    char buffer[BUFFSIZE];
    char* argv[BUFFSIZE]; // For Q6 and later

    if(STDOUT_FILENO == -1){
        perror("Open");
        exit(EXIT_FAILURE);
    }
    //Initial prompt : Q1
    write_fct("Bienvenue dans le shell ENSEA\n");
    write_fct("Pour quitter, tapez exit\n"); 
    write_fct("enseash % "); 

    while(1){
        //eval_fct(buffer); //Q2
        //eval_exit_fct(buffer); //Q3
        //eval_return_code_fct(buffer); //Q4
        //eval_timer_fct(buffer); //Q5
        //eval_arg_fct(buffer, argv); //Q6
        eval_redirect_fct(buffer, argv); //Q7
    }

    close(STDOUT_FILENO);
    exit(EXIT_SUCCESS);
}




