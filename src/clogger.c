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

void _clog_vlogf(const char *format, va_list ap) {
	// allocate memory for storing message log in memory
	_linked_messages msgs = _clog_alloc(
			_clog_calc_min_msg_size(format, ap));
	// format and store message in log
	vsprintf(msgs->message, format, ap);
	_clog_append(msgs);
}

void clog_logf(const char *format, ...) {
	va_list ap;
	va_start(ap, format);
	_clog_vlogf(format, ap);
	va_end(ap);
}

void __clog_printer(_linked_messages entry,
		FILE **fp) {
#ifdef CLOGGER_DATETIME
	char *datetime_string = ctime(&entry->datetime);
	// removing \n from end of datetime_string
	datetime_string[24] = '\0';
	// date/time: message
	fprintf(*fp, "%s: %s\r\n",
			datetime_string,
			entry->message);
#else
	fprintf(*fp, "%s\r\n", entry->message);
#endif
}

void clog_fprint(FILE *fp) {
	_clog_foreach(__clog_printer, &fp);
}

void clog_print_console() {
	clog_fprint(stdout);
}

void _clog_counter(_linked_messages entry,
		int *count) {
	(*count)++;
}

unsigned long clog_count() {
	int count = 0;
	_clog_foreach(_clog_counter, &count);
	return count;
}

