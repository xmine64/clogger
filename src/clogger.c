#include <clogger_internal.h>

int _clog_measure_size(const char *format, va_list ap) {
	va_list ap_bak;
	va_copy(ap_bak, ap);
	int size = vsnprintf(NULL, 0, format, ap_bak);
	va_end(ap_bak);
	return size;
}

void clog_logf(const char *format, ...) {
	va_list ap;
	va_start(ap, format);
	_linked_messages msgs = _clog_alloc(_clog_measure_size(format, ap));
	vsprintf(msgs->message, format, ap);
	va_end(ap);
	_clog_append(msgs);
}

void clog_print() {
	_clog_fprint(stdout);
}

void clog_free() {
	_clog_free();
}

bool clog_any() {
	return _clog_any();
}

