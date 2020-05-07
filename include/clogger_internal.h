// clogger internals header file
// don't use it in your programs.

#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include<stdarg.h>

#include "clogger.h"

typedef struct _linked_message_entry* _linked_messages;

struct _linked_message_entry {
	char *message;
	_linked_messages next;
};

_linked_messages _clog_get();

_linked_messages _clog_alloc(int size);
void _clog_append(_linked_messages item);
void _clog_fprint(FILE *fp, _linked_messages messages);
void _clog_free(_linked_messages messages);

