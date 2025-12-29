#ifndef QUESTION_5_H 
#define QUESTION_5_H 
#include "TP_main.h"

extern int status;
void start_timer();
void end_timer();
int get_time();
void eval_timer_fct(char * command);
ssize_t write_return_code_timer_fct(int return_code, int time);
#endif