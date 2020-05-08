# C Compiler
CC = gcc
# Linker
LD = gcc
# Compiler Arguments
# For shared library
CFLAGS = -I include/ -DCLOGGER_DYN -fPIC
# Linker Arguments
LDFLAGS = -shared

SRC = $(wildcard src/*.c)
OBJ = $(patsubst src/%.c, obj/%.o, $(SRC))

all: libclogger.so

test: test.out
	sh -c "PATH=. LD_LIBRARY_PATH=. $<"

# link
libclogger.so: $(OBJ)
	$(LD) -o $@ $(OBJ) $(LDFLAGS)

# compile
obj/%.o: src/%.c
	$(CC) -c $< -o $@ $(CFLAGS)

test.out: test.c libclogger.so
	$(CC) $^ -o $@ $(CFLAGS)

clean:
	rm -rf $(OBJ) libclogger.so test.out

