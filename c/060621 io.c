/*
Attempt at learning C file io instead of just copy-pasting from stackoverflow
*/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <memory.h>

char *fReadText(const char *filename)
{
    FILE *fp = fopen(filename, "rb");
    assert(fp);
    fseek(fp, 0, SEEK_END);
    int len = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    assert(len > -1);
    char *str = malloc(sizeof(char) * (len + 1));
    fread(str, 1, len, fp);
    str[len] = '\0';
    fclose(fp);
    return str;
}

void fWriteText(const char *filename, const char *str)
{
    FILE *fp = fopen(filename, "wb");
    assert(fp);
    fputs(str, fp);
    fclose(fp);
}

void main()
{
    fWriteText("hello.txt", "Hello world");
    char *str = fReadText("hello.txt");
    remove("hello.txt");
    printf("%s\n", str);
}
