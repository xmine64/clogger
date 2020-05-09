// Small logger library for C
// API Header File
// By Mohammad Amin Mollazadeh (Madmanda)

#ifndef CLOGGER_API

// add extern keyword for dynamic library
#ifdef CLOGGER_DYN
#ifdef __WIN32
#define CLOGGER_API extern __declspec(dllexport)
#else
#define CLOGGER_API extern
#endif
#else
#define CLOGGER_API
#endif

CLOGGER_API void clog_err(const char *format, ...);
CLOGGER_API void clog_warn(const char *format, ...);
CLOGGER_API void clog_info(const char *format, ...);

// print all logged messages to console
CLOGGER_API void clog_print();

// print all logged messages to file fp
CLOGGER_API void clog_fprint(FILE *fp);

// release resources used by the linked list
// will clear all message log
// you will be able to log message again
CLOGGER_API void clog_free();

// get count of messages in log (fast version)
CLOGGER_API unsigned long clog_count();

#endif
