#include <stdlib.h> // for exit()
#include <stdio.h> // for printf()
#include <unistd.h> // for read(), write(), close()
#include <sys/types.h> // for ssize_t
#include <sys/wait.h> // for wait()
#include <fcntl.h> // for open()
#include <string.h> // for strlen(), strcmp()

#define BUFFSIZE 128

ssize_t write_fct(const char *str);
ssize_t read_fct(char *buffer, size_t size);
void eval_fct(char *command);

int main(){
    char buffer[BUFFSIZE];

    // Check if the file descriptor 
    if(STDOUT_FILENO == -1){
        perror("Open");
        exit(EXIT_FAILURE);
    }

    write_fct("Bienvenue dans le shell ENSEA\n");
    write_fct("Pour quitter, tapez exit\n"); 
    write_fct("enseash %"); //Initial prompt

    while(1){
        read_fct(buffer, BUFFSIZE); //Read the prompt
        eval_fct(buffer); //Evaluate the prompt
        write_fct("enseash %"); //Write the prompt again
    }

    close(STDOUT_FILENO);
    exit(EXIT_SUCCESS);
}

ssize_t write_fct(const char * str){
    ssize_t wr;
    wr = write(STDOUT_FILENO, str, strlen(str)); 
    if( wr == -1 ){
        perror("write");
        exit(EXIT_FAILURE);
    }
    return wr;
}

ssize_t read_fct(char * buffer, size_t size){
    ssize_t rd;
    while ( (rd = read(STDOUT_FILENO, buffer, size)) < 0);
    if( rd == -1 ){
        perror("read");
        exit(EXIT_FAILURE);
    }
    return rd;
}

void eval_fct(char * command){
    if (strcmp(command, "exit\n") == 0) {
        write_fct("Bye bye...\n");
        exit(EXIT_SUCCESS);

    }
    if(strcmp(command, "date\n") == 0) {
        fork();
        execl("/bin/date", "date", NULL);  // Execute date command à reprendre ici
    }
    else {
        write_fct("Command not found\n");
    }
}

