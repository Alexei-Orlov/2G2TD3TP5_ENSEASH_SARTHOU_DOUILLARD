
# This Makefile has been modified from the one downloaded ou ENSEA's moodle page 
# We found that separating questions in files was easier for us to work and go back and forth to previous questions than using git

TARGET = TP_main

SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
CFLAGS += -Wall -Wextra -g

all: $(TARGET)

# All .o files are linked to create an executable file
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

indent:
	indent -linux -i4 -nut -ts2 *.c

clean:
	rm -f $(TARGET)
	rm -f *.o

.PHONY: all clean indent

#Previous Makefile :

# SRC = $(wildcard *.c)

# BIN = $(SRC:.c=)

# CFLAGS += -Wall -Wextra -g


# all: $(BIN)


# indent:

# indent -linux -i4 -nut -ts2 *.c


# clean:

# rm -f $(BIN)

# rm -f *.o


# .PHONY: all clean indent 