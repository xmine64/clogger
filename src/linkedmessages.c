#include <clogger_internal.h>

_linked_messages _log = NULL;

_linked_messages _clog_get() {
	return _log;
}

_linked_messages _clog_alloc(int size) {
	_linked_messages result = malloc(sizeof(struct _linked_message_entry));
	result->message = malloc(size);
	return result;
}

void _clog_append(_linked_messages message) {
	if (_log == NULL) {
		_log = message;
		return;
	}
	_linked_messages parent = _log;
	while (parent->next != NULL)
		parent = parent->next;
	parent->next = message;
}

void _clog_fprint(FILE *fp, _linked_messages messages) {
	if (messages == NULL)
		return;
	fprintf(fp, "%s\r\n", messages->message);
	_clog_fprint(fp, messages->next);
}

void _clog_free(_linked_messages messages) {
	if (messages == NULL)
		return;
	_clog_free(messages->next);
	free(messages->message);
	free(messages);
}

