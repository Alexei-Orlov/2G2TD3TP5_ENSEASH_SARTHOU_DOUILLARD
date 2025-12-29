#include "Question5.h"
#include "Question4.h"
#include "Question2.h"
#include "Question1.h"
struct timespec start_time;
struct timespec end_time;

// Outputs both the status code and time taken by the previous programm :
ssize_t write_return_code_timer_fct(int return_code, int time){
    ssize_t wr;
    char return_code_buffer[BUFFSIZE] = {'\0'};

    if( WIFEXITED(return_code) ){   
        snprintf(return_code_buffer, sizeof(return_code_buffer), "enseash [exit:%d | %d ms ] %%", WEXITSTATUS(return_code), time);
    }
    else if( WIFSIGNALED(return_code) ){ 
        snprintf(return_code_buffer, sizeof(return_code_buffer), "enseash [sign:%d | %d ms ] %%", WTERMSIG(return_code), time);
    }
    wr = write(STDOUT_FILENO, return_code_buffer, strlen(return_code_buffer)); 
    if( wr == -1 ){
        perror("write");
        exit(EXIT_FAILURE);
    }
    return wr;
}

// Time related functions :
void start_timer() {
    if (clock_gettime(CLOCK_MONOTONIC, &start_time) == -1) {
        perror("clock_gettime");
        exit(EXIT_FAILURE);
    }
}

void end_timer() {
    if (clock_gettime(CLOCK_MONOTONIC, &end_time) == -1) {
        perror("clock_gettime");
        exit(EXIT_FAILURE);
    }
}

int get_time() {
    return ((int) ((double)(end_time.tv_sec - start_time.tv_sec)*1000 + (double)(end_time.tv_nsec - start_time.tv_nsec) / 1e6)) ; //time is in ms
}

// The evaluation function with the added timer :
void eval_timer_fct(char * buffer){

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

        // The execution is supposed to kill the child if it fails, we kill it ourselves :
        perror("Execution failed");
        exit(EXIT_FAILURE);

    }
    else{ // Father instructions : The father is the only time keeper
        start_timer();
        wait(&status);
        end_timer();
        // Once the child died the father stops the timer and we are able to show time next to the status in the next line :
        write_return_code_timer_fct(status,get_time());
    }
}
