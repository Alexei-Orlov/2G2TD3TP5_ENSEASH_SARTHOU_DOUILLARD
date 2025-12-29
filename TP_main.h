#define _POSIX_C_SOURCE 199309L

#include <stdlib.h> // for exit()
#include <stdio.h> // for printf()
#include <unistd.h> // for read(), write(), close()
#include <sys/types.h> // for ssize_t
#include <sys/wait.h> // for wait()
#include <fcntl.h> // for open()
#include <string.h> // for strlen(), strcmp() and snprintf()
#include <time.h> // for time()

#define BUFFSIZE 128


