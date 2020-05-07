// Small logger library for C
// API Header File
// By Mohammad Amin Mollazadeh (Madmanda)

#ifndef CLOGGER_API

#ifdef CLOGGER_DYN
#ifdef __WIN32
#define CLOGGER_API extern __declspec(dllexport)
#else
#define CLOGGER_API extern
#endif
#else
#define CLOGGER_API
#endif

#include <stdbool.h>

enum CLoggerMessageType {
	ERROR,
	WARNING,
	INFO
};

// Logs a message
CLOGGER_API void clog(const char *format, ...);

// Prints the log
CLOGGER_API void clog_print();

// Frees resources used by the logger
CLOGGER_API void clog_free();

// Returns true if log is not empty
CLOGGER_API bool clog_any();

#endif
