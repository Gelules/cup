CFLAGS = -std=c99 -pedantic -Wall -Wextra -Werror
OBJ = src/file.o
LIB = libfile_mapper.a

all: $(LIB)

$(LIB): $(OBJ)
	$(AR) csr $@ $^

clean:
	$(RM) $(OBJ) $(LIB)
