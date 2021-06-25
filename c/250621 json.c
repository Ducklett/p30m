/*
Json parser attempt
it detects integers, bools and basic strings (doesn't do floating point numbers of escape codes yet)
arrays are almost functional but I ran out of time during the implementation
*/
#include <assert.h>
#include <memory.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct {
	char *buf;
	int len;
} Str;

#define STR(s) ((Str){s, sizeof(s) - 1})
#define TODO(x)                \
	printf("TODO: %s\n", (x)); \
	exit(1);

bool isNum(char c) { return c >= '0' && c <= '9'; }
bool isWhitespace(char c) { return c == ' ' || c == '\t' || c == '\n' || c == '\r'; }

Str strSlice(Str str, int from, int len) { return (Str){str.buf + from, len}; }

int matchSequence(Str str, Str sequence, int i)
{
	for (int off = 0; off < sequence.len; off++) {
		char expected = sequence.buf[off];
		char got = str.buf[i + off];
		if (expected != got) {
			printf("Expected %c got %c\n", expected, got);
			exit(1);
		}
	}
	return sequence.len;
}

int matchJson(Str str, int i)
{
	while (i < str.len) {
		char cur = str.buf[i];

		if (isWhitespace(cur)) {
			i++;
			continue;
		}

		switch (cur) {
		case '{': TODO("Handle object"); break;
		case '[': {
			printf("[\n");
			i++; // skip [
			while (true) {
				if (str.buf[i] == '\0') {
					return i;
				} else if (str.buf[i] == ']') {
					printf("]\n");
					break;
				} else {
					i = matchJson(str, i);
					if (str.buf[i] == ',')
						i++;
					else
						return i;
				}
			}

		} break;
		case '"': {
			int start = i;
			while (str.buf[++i] != '"' && str.buf[i] != '\0') {
			}
			Str string = strSlice(str, start, i - start);
			printf("string %.*s", string.len, string.buf);
		} break;
		case 't': {
			i += matchSequence(str, STR("true"), i);
			printf("bool %s\n", "true");
		} break;
		case 'f': {
			i += matchSequence(str, STR("false"), i);
			printf("bool %s\n", "false");
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
			while (isNum(str.buf[++i])) {
			}
			Str num = strSlice(str, start, i - start);
			printf("num %.*s\n", num.len, num.buf);
		} break;
		default: {
			return i;
		} break;
		}
	}

	return i;
}

void main()
{
	Str json = STR("[10, 20, 30]");
	matchJson(json, 0);
}
