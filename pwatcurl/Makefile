CC				:= gcc
CFLAGS		:= -Wall -Wextra -Iinclude
LDFLAGS		:= -lcurl

SRCS			:= src/main.c src/request.c
OBJ				:= $(SRCS:.c=.o)
BIN				:= pwatcurl

$(BIN): $(OBJ)
	@echo "Compiling with sass..."
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	@echo "Cleaning up your digital crimes..."
	rm -f $(OBJ) $(BIN)
