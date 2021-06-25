/*
A custom print funtion that supports printing of arbitrary types
like iostream in C++
The main print function accepts Printer structs as varargs
Printer structs hold a pointer to the data you want to print
and a pointer to the function to print it with

Benerfits of this approach:
- formatted printing of arbitrary structs
Downsides of this approach
- adding new printers is boilerplaty
- printing of literals is not supported, you must
  allocate them on the stack and pass in the address
*/
#include <assert.h>
#include <inttypes.h>
#include <memory.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct {
	void *data;
	void (*fn)(void *);
} Printer;

void print(const char *fmt, ...)
{
	va_list(args);
	va_start(args, fmt);

	for (int i = 0; fmt[i] != '\0'; i++) {
		char c = fmt[i];
		if (c == '{' && fmt[i + 1] == '}') {
			Printer p = va_arg(args, Printer);
			(*(p.fn))(p.data);
			i++;
		} else {
			fputc(c, stdout);
		}
	}
	va_end(args);
}

#define printLn(...)    \
	print(__VA_ARGS__); \
	fputs("\n", stdout);

void printChars(const char *chars) { fputs(chars, stdout); }
Printer charsP(const char *chars) { return (Printer){(void *)chars, &printChars}; }

void printInt(const int *v)
{
	int x = *v;
	char digits[16];
	int i = 0;
	while (x > 0) {
		digits[i++] = (x % 10) + '0';
		x /= 10;
	}
	while (i > 0) {
		fputc(digits[--i], stdout);
	}
}
Printer intP(const int *v) { return (Printer){(void *)v, &printInt}; }

typedef struct {
	int x;
	int y;
	int z;
} V3;

void printV3(const V3 *v) { print("{{},{},{}}", intP(&v->x), intP(&v->y), intP(&v->z)); }
Printer V3P(const V3 *v) { return (Printer){(void *)v, &printV3}; }

typedef struct {
	int x;
	int y;
} V2;

void printV2(const V2 *v) { print("{{},{}}", intP(&v->x), intP(&v->y)); }
Printer V2P(const V2 *v) { return (Printer){(void *)v, &printV2}; }

int main()
{
	printLn("Hello {}!", charsP("world"));

	V3 foo = {1, 2, 3};
	V2 bar = {4, 9};
	printLn("Vectors {}, {}", V3P(&foo), V2P(&bar));
	return 0;
}
