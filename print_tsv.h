#include <stdarg.h>

void print_tsv(int count, ...) {
	va_list argp;
	va_start(argp, count);
	while (count-- > 0) {
		PrintInt(va_arg(argp, int));
		if (count) SerPrint("\t");
	}
	SerPrint("\n");
}

