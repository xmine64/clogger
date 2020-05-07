#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

#include <clogger.h>

int main() {
	clog("Hello World!");

	for (int i = 1000; i < 1010; i++)
		clog("%s, i=%i", "Testing Messages", i);

	clog("The End!");

	assert(clog_any());

	clog_print();

	clog_free();

	assert(!clog_any());
}
