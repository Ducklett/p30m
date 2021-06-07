/*
Second attempt at file io
Managed to mostly memoryize fopen & friends this time
Spend the remaining time implementing a panic macro, reading bytes, and printing bytes
*/
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <assert.h>
#include <inttypes.h>

typedef uint8_t u8;

#define COLRED "\33[031m"
#define COLCLR "\33[0m"

typedef struct
{
    int len;
    u8 *data;
} Buf;

void panic_impl(const char *msg, const char *filename, const int line, ...)
{
    printf("%sPANIC %s:%d - %s", COLRED, filename, line, COLCLR);
    va_list args;
    va_start(args, line);
    vfprintf(stderr, msg, args);
    va_end(args);

    printf("\n");
    exit(1);
}

#define panic(msg, ...) panic_impl(msg, __FILE__, __LINE__, ##__VA_ARGS__)

char *fReadString(const char *filename)
{
    FILE *fp = fopen(filename, "rb");
    if (!fp)
        panic("Failed to open file %s", filename);
    fseek(fp, 0, SEEK_END);
    int len = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    if (len < 0)
        panic("Failed to read file length");
    char *buf = malloc((sizeof(char) * (len + 1)));
    if (!buf)
        panic("Allocation failed");
    buf[len] = '\0';
    fread(buf, 1, len, fp);
    fclose(fp);
    return buf;
}

void fWriteString(const char *filename, const char *buffer)
{
    FILE *fp = fopen(filename, "wb");
    fputs(buffer, fp);
    fclose(fp);
}

Buf fReadBytes(const char *filename)
{
    FILE *fp = fopen(filename, "rb");
    if (!fp)
        panic("Failed to open file %s", filename);
    fseek(fp, 0, SEEK_END);
    int len = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    if (len < 0)
        panic("Failed to read file length");
    char *buf = malloc(sizeof(char) * len);
    if (!buf)
        panic("Allocation failed");
    fread(buf, 1, len, fp);
    fclose(fp);
    return (Buf){len, buf};
}

void bufPrint(Buf b)
{
    for (int i = 0; i < b.len - 1; i++)
    {
        printf("%02X ", b.data[i]);
    }
    // no space on last printed byte
    printf("%02X\n", b.data[b.len - 1]);
}

void main()
{
    fWriteString("hello.txt", "Hi this is a test!\n");

    char *str = fReadString("hi.txt");
    printf("%s", str);

    Buf b = fReadBytes("hello.txt");
    bufPrint(b);
}
