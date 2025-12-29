#include "Question1.h"
//A basic write function that outputs the inputed string
ssize_t write_fct(const char * str){
    ssize_t wr;
    wr = write(STDOUT_FILENO, str, strlen(str)); 
    if( wr == -1 ){
        perror("write");
        exit(EXIT_FAILURE);
    }
    return wr;
}