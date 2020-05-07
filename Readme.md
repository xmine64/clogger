# Logger Library for C
This is a small library that can be used for loggging errors in your applications.
It uses linked lists to save error messages, and can be used as static or dynamic library, or as part of your application.

# Usage
Include `clogger.h` file then link the library with your program.
Use `clog_add()` to log a message. it supports printf-style formatting.
use `clog_print()` to print log to stdout.
and at the end, `use clog_free() to clean up used resources and clear messages log.

Note: if you want to use clogger as a dynamic library, you should add `#define CLOGGER_DYN` at top of `clogger.h`

# Copying
this is a free program provided to you through MIT License. you are free to use it in anyway.

