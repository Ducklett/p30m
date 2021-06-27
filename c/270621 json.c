/*
Second JSON parser attempt
This time it parses objects and arrays!
It still doesn't output any values, instead just printing the parsed text to the console
*/
#include <assert.h>
#include <memory.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define TODO(x)              \
	printf("TODO: %s\n", x); \
	exit(1);
#define panic(x)       \
	printf("%s\n", x); \
	exit(1);

typedef struct {
	char *buf;
	int len;
} Str;
#define STR(x) ((Str){x, sizeof(x) - 1})

Str strSlice(Str source, int start, int end) { return (Str){source.buf + start, end - start}; }

bool isWhitespace(char c) { return c == ' ' || c == '\t' || c == '\n' || c == '\r'; }
bool isNumber(char c) { return c >= '0' && c <= '9'; }
char getCurrent(Str text, int i) { return text.buf[i]; }
int matchWhitespace(Str text, int i)
{
	while (isWhitespace(getCurrent(text, i)))
		i++;

	return i;
}

int matchString(Str text, int i)
{
	i++;
	int start = i;
	while (getCurrent(text, i) != '"' && i < text.len)
		i++;

	if (getCurrent(text, i) != '"') {
		panic("expected \"");
	}

	Str content = strSlice(text, start, i);
	printf("\"%.*s\"", content.len, content.buf);
	i++;
	return i;
}

int matchJson(Str text, int i)
{
	i = matchWhitespace(text, i);
	switch (text.buf[i]) {
	case '{': {
		i++;
		i = matchWhitespace(text, i);
		printf("{ ");
		while (getCurrent(text, i) != '}' && i < text.len) {
			i = matchString(text, i);
			i = matchWhitespace(text, i);
			if (getCurrent(text, i) != ':') break;
			i++;
			printf(" : ");

			i = matchJson(text, i);
			i = matchWhitespace(text, i);
			if (getCurrent(text, i) != ',') break;
			printf(", ");
			i++;
			i = matchWhitespace(text, i);
		}

		if (getCurrent(text, i) != '}') {
			panic("expected \"");
		}
		printf(" }");
		i++;
	} break;
	case '[':
		i++;
		i = matchWhitespace(text, i);
		printf("[ ");
		while (getCurrent(text, i) != ']' && i < text.len) {
			i = matchJson(text, i);
			i = matchWhitespace(text, i);
			if (getCurrent(text, i) != ',') break;
			printf(", ");
			i++;
			i = matchWhitespace(text, i);
		}

		if (getCurrent(text, i) != ']') {
			panic("expected \"");
		}
		printf(" ]");
		i++;

		break;
	case '"': {
		i = matchString(text, i);
	} break;
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9': {
		int start = i;
		while (isNumber(getCurrent(text, i))) {
			i++;
		}
		Str num = strSlice(text, start, i);
		printf("%.*s", num.len, num.buf);
	} break;
	default: {
		printf("%c\n", getCurrent(text, i));
		TODO("Handle unknown char");
	} break;
	}

	i = matchWhitespace(text, i);
	return i;
}

void main()
{
	Str json = STR("{\"Hello world\": [\"array test\", 10, 20], \"foo\":  \"bar\"}");
	matchJson(json, 0);
}
