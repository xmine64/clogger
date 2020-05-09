#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

#include <clogger.h>

int main() {
	clog_logf("Hello World!");

	for (int i = 1000; i < 1010; i++)
		clog_logf("%s, i=%i", "Testing Messages", i);

	clog_logf("The End!");

	assert(clog_count() == 12);

	clog_fprint(stderr);

	clog_free();

	assert(clog_count() == 0);
}
