# Logger Library for C
This is a small library that can be used for loggging errors in your applications.
It uses linked lists to save error messages, and can be used as static or dynamic library, or as part of your application.

# Usage
Include `clogger.h` file then link the library with your program.
Use `clog_logf()` to log a message. it supports printf-style formatting.
use `clog_print()` to print log to stdout.
and at the end, use `clog_free()` to clean up used resources and clear messages log.

# Compile
as a dynamic library:
```
$ make libclogger.so
```
or
```
$ gcc src/*.c -o libclogger.so -I include/ -DCLOGGER_DYN -shared
```


as a static library:
```
$ make libclogger.a
```
or simply copy source files to your program.


# Copying
this is a free program provided to you through MIT License. you are free to use it in anyway.

