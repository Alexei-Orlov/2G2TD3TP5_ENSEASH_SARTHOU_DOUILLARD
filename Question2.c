#include "Question2.h"
#include "Question1.h"

// A basic read function that fills a buffer with the inputed text and returns the number of bytes read
ssize_t read_fct(char * buffer, size_t size){
    ssize_t rd;
    rd = read(STDIN_FILENO, buffer, size);

    if( rd == -1 ){
        perror("read");
        exit(EXIT_FAILURE);
    }
    buffer[rd] = '\0';
    return rd;
}

// This evaluation function will run argument-less functions such as : date, ls or fortune if installed
void eval_fct(char * buffer){
        read_fct(buffer, BUFFSIZE);

        // Cleaning the buffer : 
        buffer[strcspn(buffer, "\n")] = 0;

        pid_t pid = fork();

        if(pid == -1) { // Fork failed
            perror("Fork");
            exit(EXIT_FAILURE);
        }
        else if(pid == 0) { // Child process identification and instructions :
            execlp(buffer, buffer, NULL);

            //The execution is supposed to kill the child if it fails we kill it ourselves :
            perror("Execution failed");
            exit(EXIT_FAILURE);
        }
        else{ // Father instructions :
            wait(&status);
            write_fct("enseash % "); //Write the prompt again
        }
}


// The folowing code was our first version where we tried to identify each command instead of running them directly

// void eval_fct(char * command){
//     command[strcspn(command, "\n")] = 0;
//     if(strcmp(command, "date") == 0) {      //date command  
//         pid_t pid = fork();
//         if(pid == -1) { // Fork failed
//             perror("Fork");
//             exit(EXIT_FAILURE);
//         }
//         else if(pid == 0) { // Child process
//             execlp("/bin/date", "date", NULL);
//         }
//         else{
//             wait(&status);
//         }
//     }
//     else if(strcmp(command, "ls") == 0) {        //ls command
//         pid_t pid = fork();
                
//         if(pid == -1) { // Fork failed
//             perror("Fork");
//             exit(EXIT_FAILURE);
//         }
//         else if(pid == 0) { // Child process
//             execlp("/bin/ls", "ls", NULL);
//         }
//         else{
//             wait(&status);
//         }
//     }
//     else {                                  // command not found            
//         write_fct("enseash % Command not found\n");
//     }
// }

