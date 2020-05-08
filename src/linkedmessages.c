// internal functions for managing the linked list

#include <clogger_internal.h>

// the list entry
_linked_messages _log = NULL;
// pointer to last node, used for caching and imporve performance
_linked_messages _last = NULL;

_linked_messages _clog_alloc(int message_size) {
	_linked_messages result =
		malloc(sizeof(struct _linked_message_entry));

	result->message = malloc(message_size);

#ifdef CLOGGER_DATETIME
	result->datetime = time(NULL);
#endif
	return result;
}

void _clog_append(_linked_messages message) {
	// first entry is null,
	// then there's no parent to append to it
	// so it's the first node
	if (_log == NULL) {
		_log = message;
		_last = _log;
		return;
	}
	// _last points to last node
	// so we don't need to seek through nodes
	// to find last node to append to it
	_last->next = message;
	// new node has been appended, so update _last pointer
	_last = _last->next;
}

// internal function to print log and its children recursively
void _clog_fprint(FILE *fp, _linked_messages messages) {
	if (messages == NULL)
		return;
	// format message to be printed
	// if date/time is enabled, format date/time
#ifdef CLOGGER_DATETIME
	// convert date/time to character string
	char *datetime = ctime(&messages->datetime);
	// datetime is a static character array with length of 26
	// [24] is '\n', and [25] is '\0'
	// by this, we remove the last new line character
	datetime[24] = '\0';
	// date/time: message
	fprintf(fp, "%s: %s\r\n",
			datetime,
			messages->message);
#else
	fprintf(fp, "%s\r\n", messages->message);
#endif
	// recursively, print children
	_clog_fprint(fp, messages->next);
}

// release resources of messages recursively
void _clog_free(_linked_messages messages) {
	if (messages == NULL)
		return;
	// free child before parent
	_clog_free(messages->next);

	free(messages->message);
	free(messages);
}

// these are public functions, but needed to declare them here
// because they need to access internals directly

bool clog_any() {
	return _log != NULL;
}

void clog_free() {
	if (_log == NULL)
		return;
	_clog_free(_log);
	// _log and _last are not available anymore
	_log = NULL;
	_last = NULL;
}

// print log from first node to last child
void clog_fprint(FILE *fp) {
	_clog_fprint(fp, _log);
}

