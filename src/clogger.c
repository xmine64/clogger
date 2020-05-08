// public API functions

#include <clogger_internal.h>

// internal utility function for clog_logf()
// calculate the minimum needed memory to store formatted message
int _clog_measure_size(const char *format, va_list ap) {
	// backup va_list, we still need it later
	va_list ap_bak;
	va_copy(ap_bak, ap);
	// this won't print anything,
	// but returns length of the formatted string
	int size = vsnprintf(NULL, 0, format, ap_bak);
	va_end(ap_bak);
	return size;
}

// internal utility function for clog_logf()
// format and append message to log
void _clog_vlogf(const char *format, va_list ap) {
	// allocate memory for storing message log in memory
	_linked_messages msgs =
		_clog_alloc(_clog_measure_size(format, ap));
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

// moved to linkedmessages.c
//void clog_fprint(FILE *fp) {
//	_clog_fprint(fp);
//}

void clog_print_console() {
	clog_fprint(stdout);
}

// moved to linkedmessages.c
//void clog_free() {
//	_clog_free();
//}

// move to linkedmessages.c
//bool clog_any() {
//	return _clog_any();
//}

