// internal functions for managing the linked list

#include <clogger_internal.h>

// the list entry
_linked_messages _log = NULL;
// pointer to last node, used for caching and imporve performance
_linked_messages _last = NULL;
// keep track of messages count
unsigned long _log_size = 0;

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
	_log_size++;

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

// release resources of messages recursively
void _clog_free(_linked_messages messages) {
	if (messages == NULL)
		return;
	// free child before parent
	_clog_free(messages->next);

	free(messages->message);
	free(messages);
}

void _clog_foreach(_clog_foreach_handler handler, void *argument) {
	_linked_messages entry = _log;
	while (entry != NULL) {
		handler(entry, argument);
		entry = entry->next;
	}
}

// these are public functions, but needed to declare them here
// because they need to access internals directly

void clog_free() {
	if (_log == NULL)
		return;
	_clog_free(_log);
	// _log and _last are not available anymore
	_log = NULL;
	_last = NULL;

	_log_size = 0;
}

unsigned long clog_count() {
	return _log_size;
}

