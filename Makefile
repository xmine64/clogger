# toolchain
CC = gcc
LD = gcc
AR = ar
DB = lldb

# options
CFLAGS = -I include/ -DCLOGGER_DATETIME
LDFLAGS =

# source files
SRC = $(wildcard src/*.c)

# object files
OBJ = $(patsubst src/%.c, obj/%.o, $(SRC))
OBJ_STATIC = $(patsubst src/%.c, obj/%-static.o, $(SRC))
OBJ_DEBUG = $(patsubst src/%.c, obj/%-debug.o, $(SRC))

# commands:
# all:   build dynamic and static profiles
# debug: build and run test program in static-debug profile
# test:  build and run test programs

all: libclogger.so libclogger.a

debug: test-debug
	$(DB) -f $< -d

test: test-dyn test-a test-s
	sh -c "PATH=. LD_LIBRARY_PATH=. test-dyn"
	sh -c "./test-a"
	sh -c "./test-s"

# link

# link test program with dynamic library
test-dyn: obj/test.o libclogger.so
	$(LD) -o $@ $^ $(LDFLAGS)

# link test program with static library
test-s: obj/test-static.o libclogger.a
	$(LD) -o $@ $^ $(LDFLAGS)

# link test program and library
test-a: obj/test-static.o $(OBJ_STATIC)
	$(LD) -o $@ $^ $(LDFLAGS)

# link test program in debug profile
test-debug: obj/test-debug.o $(OBJ_DEBUG)
	$(LD) -g -o $@ $^

libclogger.so: $(OBJ)
	$(LD) -o $@ $^ $(LDFLAGS) -shared
	
libclogger.a: $(OBJ_STATIC)
	$(AR) rcs $@ $^

# compile

# compile in debug profile
obj/%-debug.o: src/%.c
	$(CC) -g -c $< -o $@ $(CFLAGS)

obj/test-debug.o: test.c
	$(CC) -g -c $< -o $@ $(CFLAGS)

# compile in static profile
obj/%-static.o: src/%.c
	$(CC) -c $< -o $@ $(CFLAGS)

obj/test-static.o: test.c
	$(CC) -c $^ -o $@ $(CFLAGS)

# compile in dynamic profile
obj/%.o: src/%.c
	$(CC) -c $< -o $@ $(CFLAGS) -DCLOGGER_DYN -fPIC

obj/test.o: test.c
	$(CC) -c $^ -o $@ $(CFLAGS) -DCLOGGER_DYN -fPIC

# cleanup build and object files
clean:
	rm -rf $(OBJ) $(OBJ_STATIC) $(OBJ_DEBUG) libclogger.so libclogger.a test-a test-s test-dyn test-debug

