/*
Functions for converting text and binary assets into headers
so they can be baked into programs at compile time
*/

#include <inttypes.h>
#include <memory.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
	char *data;
	int len;
} Str;

typedef struct {
	uint8_t *data;
	int len;
} Buf;

Str freadString(const char *filename)
{
	FILE *fp = fopen(filename, "rb");
	fseek(fp, 0, SEEK_END);
	int len = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	char *buf = malloc(sizeof(char) * (len + 1));
	fread(buf, 1, len, fp);
	buf[len] = '\0';
	fclose(fp);
	return (Str){buf, len};
}

// generate header at {destination} from text at {filename} with variable {name}
// so it can be included into a program at compile time
void fIncludeString(const char *filename, const char *destination, const char *name)
{
	Str buf = freadString(filename);

	FILE *fp = fopen(destination, "wb");
	fprintf(fp, "const char* %s =\"", name);
	for (int i = 0; i < buf.len; i++) {
		char c = buf.data[i];
		if (c == '\n') {
			fputs("\\n", fp);
		} else if (c == '\r') {
			fputs("\\r", fp);
		} else if (c == '\t') {
			fputs("\\t", fp);
		} else {
			fputc(c, fp);
		}
	}

	fprintf(fp, "\"");
	fprintf(fp, "const int %s_len = %d;\n", name, buf.len);
	fclose(fp);
}

// generate header at {destination} from bytes {buf} with variable {name}
// so it can be included into a program at compile time
void bIncludeBytes(Buf buf, const char *destination, const char *name)
{
	FILE *fp = fopen(destination, "wb");

	fprintf(fp, "#include <inttypes.h>\nconst uint8_t %s[] = {", name);
	for (int i = 0; i < buf.len; i++) {
		uint8_t c = buf.data[i];
		fprintf(fp, "0x%.2X,", c);
	}

	fprintf(fp, "};\n");
	fprintf(fp, "const int %s_len = %d;\n", name, buf.len);
	fclose(fp);
}

// generate header at {destination} from bytes at {filename} with variable {name}
// so it can be included into a program at compile time
void fIncludeBytes(const char *filename, const char *destination, const char *name)
{
	Str buf = freadString(filename);
	bIncludeBytes((Buf){(uint8_t *)buf.data, buf.len}, destination, name);
}

int main()
{
	Str foo = freadString("hello.txt");
	bIncludeBytes((Buf){foo.data, foo.len}, "hello.h", "hello");
	// fIncludeBytes("./hello.txt", "./hello.h", "hello");
	return 0;
}
