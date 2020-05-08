CC = gcc
LD = gcc
AR = ar

CFLAGS = -I include/ -DCLOGGER_DYN -fPIC
CFLAGS_STATIC = -I include/
LDFLAGS = -shared

SRC = $(wildcard src/*.c)
OBJ = $(patsubst src/%.c, obj/%.o, $(SRC))
OBJ_STATIC = $(patsubst src/%.c, obj/%-static.o, $(SRC))

all: libclogger.so libclogger.a

test: test.out
	sh -c "PATH=. LD_LIBRARY_PATH=. $<"

# link
libclogger.so: $(OBJ)
	$(LD) -o $@ $(OBJ) $(LDFLAGS)

libclogger.a: $(OBJ_STATIC)
	$(AR) rcs $@ $^

# compile
obj/%-static.o: src/%.c
	$(CC) -c $< -o $@ $(CFLAGS_STATIC)

obj/%.o: src/%.c
	$(CC) -c $< -o $@ $(CFLAGS)

test.out: test.c libclogger.so
	$(CC) $^ -o $@ $(CFLAGS)

clean:
	rm -rf $(OBJ) $(OBJ_STATIC) libclogger.so libclogger.a test.out

