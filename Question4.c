#include "Question4.h"
#include "Question3.h"
#include "Question2.h"
#include "Question1.h"

// Write the exit code of the previous command return_code corresponds to the previous status
ssize_t write_return_code_fct(int return_code){
    ssize_t wr;
    char return_code_buffer[BUFFSIZE] = {'\0'};

    // If the previous process ends by itself :
    if( WIFEXITED(return_code) ){   
        snprintf(return_code_buffer, sizeof(return_code_buffer), "enseash [exit:%d] %%", WEXITSTATUS(return_code));
    }

    //If it got interrupted :
    else if( WIFSIGNALED(return_code) ){ 
        snprintf(return_code_buffer, sizeof(return_code_buffer), "enseash [sign:%d] %%", WTERMSIG(return_code));
    }
    wr = write(STDOUT_FILENO, return_code_buffer, strlen(return_code_buffer)); 
    if( wr == -1 ){
        perror("write");
        exit(EXIT_FAILURE);
    }
    return wr;
}

void eval_return_code_fct(char * buffer){

    int ctrlD = read_fct(buffer, BUFFSIZE);
            if (ctrlD==0){ // if the returned value is 0 it means that no caracters where inputed but somehow an instruction was sent i.e a ctrl + D
            write_fct("Ctrl D detecté, Fermeture...\n");
            exit(EXIT_SUCCESS);
        }

    // Cleaning the buffer : 
    buffer[strcspn(buffer, "\n")] = 0;

    if (strcmp(buffer, "exit") == 0) {  // "exit" command detection
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
        write_return_code_fct(status); // Once the child died ans updated the status we are able to show it in the next line
    }
}