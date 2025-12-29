#include "Question6.h"
#include "Question5.h"
#include "Question4.h"
#include "Question2.h"
#include "Question1.h"

// To take several arguments into account we have to split them into tokens and store them in the args array
void separation_args(char * command, char ** args) {
    char *token;
    char *token_read_head;
    // We are using the strtok_r function to split the command
    // The simpler strtok command was considered as a bad habit on stackoverflow because it doesn't store it's readhead in a chosen variable
    // This means it doesn't work for multithreading because the read position is in a global variable that will be changed by the other thread
    
    // The separator is the space character 
    token = strtok_r(command, " ", &token_read_head);
    int i = 0;

    while (token != NULL) {
        args[i++] = token;
        token = strtok_r(NULL, " ",&token_read_head);
    }
    args[i] = NULL; // Null-terminate the array of arguments
}

void eval_arg_fct(char * buffer, char ** args){

    int ctrlD = read_fct(buffer, BUFFSIZE);
            if (ctrlD==0){ // If the returned value of read_fct is 0 it means that no characters where inputed but somehow an instruction was sent i.e a ctrl + D
            write_fct("Ctrl D detecté, Fermeture...\n");
            exit(EXIT_SUCCESS);
        }

    // Cleaning the buffer : 
    buffer[strcspn(buffer, "\n")] = 0;

    // Checking for the custom exit command :
    if (strcmp(buffer, "exit") == 0) {  // "exit" command detection
        write_fct("Bye bye...\n");
        exit(EXIT_SUCCESS);
    }
    // Starting to separate the different arguments :
    separation_args(buffer,args);

    pid_t pid = fork();
            
    if(pid == -1) { // Fork failed
        perror("Fork fail");
        exit(EXIT_FAILURE);
    }
    else if(pid == 0) { // Child process identification and execution:
        // Now we have to use execvp to input an array of arguments 
        execvp(args[0],args);

        // The execution is supposed to kill the child if it fails, we kill it ourselves :
        perror("Execution failed");
        exit(EXIT_FAILURE);

    }
    else{ // Father instructions :
        start_timer();
        wait(&status);
        end_timer();
        write_return_code_timer_fct(status,get_time());// Once the child died and updated the status we are able to show it in the next line
    }
}
