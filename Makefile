CFLAGS = -std=c99 -pedantic -Wall -Wextra -Werror
OBJ = src/cup.o
BIN = packer

all: $(BIN)

$(BIN): $(OBJ)
	$(CC) $^ -o $@

clean:
	$(RM) $(OBJ) $(BIN) unpacker
