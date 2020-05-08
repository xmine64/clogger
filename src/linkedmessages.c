#include <clogger_internal.h>

_linked_messages _log = NULL;
_linked_messages _last = NULL;

bool _clog_any() {
	return _log != NULL;
}

_linked_messages _clog_alloc(int size) {
	_linked_messages result = malloc(sizeof(struct _linked_message_entry));
	result->message = malloc(size);
#ifdef CLOGGER_DATETIME
	result->datetime = time(NULL);
#endif
	return result;
}

void _clog_append(_linked_messages message) {
	if (_log == NULL) {
		_log = message;
		_last = _log;
		return;
	}
	_last->next = message;
	_last = _last->next;
}

void __clog_fprint(FILE *fp, _linked_messages messages) {
	if (messages == NULL)
		return;
#ifdef CLOGGER_DATETIME
	char *datetime = ctime(&messages->datetime);
	datetime[24] = '\0';
	fprintf(fp, "%s: %s\r\n",
			datetime,
			messages->message);
#else
	fprintf(fp, "%s\r\n", messages->message);
#endif
	__clog_fprint(fp, messages->next);
}

void _clog_fprint(FILE *fp) {
	__clog_fprint(fp, _log);
}

void __clog_free(_linked_messages messages) {
	if (messages == NULL)
		return;
	__clog_free(messages->next);
	free(messages->message);
	free(messages);
}

void _clog_free() {
	if (_log == NULL)
		return;
	__clog_free(_log);
	_log = NULL;
	_last = NULL;
}

