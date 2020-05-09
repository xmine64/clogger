// public API functions

#include <clogger_internal.h>

int _clog_calc_min_msg_size(const char *format, va_list ap) {
	// backup va_list, we still need it later
	va_list ap_bak;
	va_copy(ap_bak, ap);
	// this won't print anything,
	// but returns length of the formatted string
	int size = vsnprintf(NULL, 0, format, ap_bak);
	va_end(ap_bak);
	return size;
}

void _clog_vlogf(enum _linked_message_entry_kind kind,
		const char *format, va_list ap) {
	// allocate memory for storing message log in memory
	_linked_messages entry = _clog_alloc(
			_clog_calc_min_msg_size(format, ap));
	entry->kind = kind;
	// format and store message in log
	vsprintf(entry->message, format, ap);
	_clog_append(entry);
}

void clog_err(const char *format, ...) {
	va_list ap;
	va_start(ap, format);
	_clog_vlogf(ERROR, format, ap);
	va_end(ap);
}

void clog_warn(const char *format, ...) {
	va_list ap;
	va_start(ap, format);
	_clog_vlogf(WARN, format, ap);
	va_end(ap);
}

void clog_info(const char *format, ...) {
	va_list ap;
	va_start(ap, format);
	_clog_vlogf(INFO, format, ap);
	va_end(ap);
}

const char *__clog_kind_to_string(
		enum _linked_message_entry_kind kind) {
	switch (kind) {
		case ERROR:
			return "ERROR";
		case INFO:
			return "Info";
		case WARN:
			return "Warning";
		default:
			return "Invalid";
	}
}

void __clog_fprinter(_linked_messages entry,
		FILE **fp) {
#ifdef CLOGGER_DATETIME
	char *datetime_string = ctime(&entry->datetime);
	// removing \n from end of datetime_string
	datetime_string[24] = '\0';
	// date/time: message
	fprintf(*fp, "%s: [%s]\t%s\r\n",
			datetime_string,
			__clog_kind_to_string(entry->kind),
			entry->message);
#else
	fprintf(*fp, "[%s]\t%s\r\n", 
			__clog_kind_to_string(entry->kind),
			entry->message);
#endif
}

void clog_fprint(FILE *fp) {
	_clog_foreach((_clog_foreach_handler*)__clog_fprinter, &fp);
}

void __clog_console_printer(_linked_messages entry, void *null) {
	FILE *fp = entry->kind == ERROR? stderr : stdout;
	__clog_fprinter(entry, &fp);
}

void clog_print() {
	_clog_foreach(__clog_console_printer, NULL);
}

