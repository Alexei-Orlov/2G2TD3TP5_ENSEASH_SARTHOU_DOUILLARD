#include "TP_main.h" // Includes all libraries and BUFFSIZE
#include "Question3.h"
#include "Question2.h" //We need read_fct
#include "Question1.h" //We need write_fct

// Updated evaluation function from Q2 with the addition of an exit command killing the main process
// We also implemented a ctrl + D detection that also exits the shell

void eval_exit_fct(char * buffer){

    int ctrlD = read_fct(buffer, BUFFSIZE);
            if (ctrlD==0){ // if the returned value is 0 it means that no caracters where inputed but somehow an instruction was sent i.e a ctrl + D
            write_fct("Ctrl D detecté, Fermeture...\n");
            exit(EXIT_SUCCESS);
        }

    // Cleaning the buffer : 
    buffer[strcspn(buffer, "\n")] = 0;

    if (strcmp(buffer, "exit") == 0) {     // "exit" command detection
        write_fct("Bye bye...\n");
        exit(EXIT_SUCCESS);
    }
    pid_t pid = fork();
            
    if(pid == -1) { // Fork failed
        perror("Fork fail");
        exit(EXIT_FAILURE);
    }
    else if(pid == 0) { // Child process identification and execution:
        execlp(buffer,buffer, NULL);

        // The execution is supposed to kill the child if it fails we kill it ourselves :
        perror("Execution failed");
        exit(EXIT_FAILURE);

    }
    else{ // Father instructions :
        wait(&status);
        write_fct("enseash % "); //Write the prompt again
    }

}