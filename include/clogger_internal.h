// clogger internals header file
// don't use it in your programs.

#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include<stdarg.h>

// if CLOGGER_DATETIME is defined, then add timestamp to log
#ifdef CLOGGER_DATETIME
#include <time.h>
#endif

#include<clogger.h>

// messages are saved in linked list entries
typedef struct _linked_message_entry* _linked_messages;

struct _linked_message_entry {
	char *message;
#ifdef CLOGGER_DATETIME
	time_t datetime;
#endif
	_linked_messages next;
};

// internal functions used in clogger.c file

_linked_messages _clog_alloc(int message_size);

void _clog_append(_linked_messages entry);

