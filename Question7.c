#include "Question6.h"
#include "Question5.h"
#include "Question4.h"
#include "Question2.h"
#include "Question1.h"

#define PERMISSION 0644
#define ENDOFREDIRECT -1

//While we separate arguments we locate the greater than and smaller than symbols and store their postions
void separation_args_with_redirect_sort(char * command, char ** args,int * lesser_pos, int * greater_pos) {
    char *token;
    char *token_read_head;
    // We are using the strtok_r function to split the command
    // The simpler strtok command was considered as a bad habit on stackoverflow because it doesn't store it's readhead in a chosen variable
    // strtok doesn't work for multithreading because the read position is in a global variable that will be changed by the other thread
    
    // The separator is the space character 
    token = strtok_r(command, " ", &token_read_head);
    int i = 0;
    int lesser_count = 0;
    int greater_count = 0;

    while (token != NULL) {
        if(strcmp(token, "<") == 0){
            lesser_pos[lesser_count]=i+lesser_count+greater_count;
            lesser_count++;
        }
        else if(strcmp(token, ">") == 0){
            greater_pos[greater_count]=i+lesser_count+greater_count;
            greater_count++;
        }
        else{
            args[i++] = token;
        }
        token = strtok_r(NULL, " ",&token_read_head);

    }
    args[i] = NULL; // Null-terminate the array of arguments
    lesser_pos[lesser_count] = ENDOFREDIRECT; //-1-terminate the array of positions
    greater_pos[greater_count]=ENDOFREDIRECT;
}


//The goal of this function is to link outputs and input of files and then run the command
void eval_redirect_fct(char * buffer, char ** args){
    int lesser_pos[BUFFSIZE];
    int greater_pos[BUFFSIZE];
    int ctrlD = read_fct(buffer, BUFFSIZE);
            if (ctrlD==0){ // if the returned value of read_fct is 0 it means that no caracters where inputed but somehow an instruction was sent i.e a ctrl + D
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
    // Starting the decode process
    separation_args_with_redirect_sort(buffer,args,lesser_pos,greater_pos);

    pid_t pid = fork();
            
    if(pid == -1) { // Fork failed
        perror("Fork fail");
        exit(EXIT_FAILURE);
    }
    else if(pid == 0) { // Child process identification and execution:
            int current_token = 0; // the token index of the whole message (includes > and < )
            int current_arg = 0; // the token index of files and function arguments (excludes > and < )
            int current_sub_arg = 0; //the argument of the current function 
            int current_lesser_count = 0; // the index in the list of postitions of the lesser than symbols
            int current_greater_count = 0; // the index in the list of postitions of the greater than symbols
            
        while(args != NULL){
            char * sub_args[BUFFSIZE];
            do{
                if (current_token == lesser_pos[current_lesser_count]){
                    int fd = open(args[current_arg], O_RDONLY, PERMISSION); // Opens the file mentioned after "<" .
                    if (fd == -1) {
                        perror("open");
                        exit(EXIT_FAILURE);
                    }
                    dup2(fd, STDIN_FILENO); //Redirects stdin (the input) to the file, opened by descriptor fd
                    close(fd);
                    current_token++; //additionnal increase to compensate for the "<" (see line 108)
                    current_lesser_count++;
                }
                else if (current_token == greater_pos[current_greater_count]){
                    int fd = open(args[current_arg], O_CREAT | O_WRONLY | O_TRUNC, PERMISSION); // Opens or creates the file named after ">" 
                    if (fd == -1) {
                        perror("open");
                        exit(EXIT_FAILURE);
                    }
                    dup2(fd, STDOUT_FILENO); //Redirects stdout (the output) to the file, opened by descriptor fd
                    close(fd);

                    current_token++; //additionnal increase to compensate for the ">" (see line 108)
                    current_greater_count++;
                }
                else{
                    sub_args[current_sub_arg]=args[current_arg]; // Collects every arguments for the function
                    current_sub_arg++;

                }
                current_token++; // Increases twice in one cycle when < or > are found otherwise it only goes up once
                current_arg++; // In any case we move in the set of commands and files 

            }while((lesser_pos[current_lesser_count]!= ENDOFREDIRECT) | (greater_pos[current_greater_count] != ENDOFREDIRECT)|(args[current_arg] != NULL)); //We run it until all rederections have been mapped
                  sub_args[current_sub_arg]=NULL;          
            //Once the "routing" (all the inputs are leading to the correct outputs) is done we can run the command that was assembled previously
            execvp(sub_args[0],sub_args);
        }

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

