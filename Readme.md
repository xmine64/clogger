# Logger Library for C
This is a small library that can be used for loggging errors in your applications.
It uses linked lists to save error messages, and can be used as static or dynamic library, or as part of your application.

# Usage
```
#include<clogger.h>

// log a message, warning or error
clog_info("a message, printf-style formatting is %s.",
	"supported");
clog_warn("a warning");
clog_err("an error");

// get count of messages
printf("total errors: %lu", clog_count());

// print messages to console
// errors will printed to stderr
clog_print();

// print messages to a file
clog_fprint(file_pointer);

// clear message log, and release used resources
clog_free();

```

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
or simply copy source files to your project.


# Copying
this is a free program provided to you through MIT License. you are free to use it in anyway.

