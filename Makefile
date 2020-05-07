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

all: build/libclogger.so build/test

# link
build/libclogger.so: $(OBJ)
	$(LD) -o $@ $(OBJ) $(LDFLAGS)

# compile
obj/%.o: src/%.c
	$(CC) -c $< -o $@ $(CFLAGS)

build/test: test/test.c build/libclogger.so
	$(CC) $^ -o $@ $(CFLAGS)

clean:
	rm $(OBJ)

