// switched everything into a file called libc which is simulating the C library in modern OSes
#ifndef STRING_H
#define STRING_H
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include "mem.h"
void int_to_ascii(int n, char str[]);
void hex_to_ascii(int n, char str[]);
void reverse(char s[]);
void backspace(char s[]);
void append(char s[], char n);
int strlen(char s[]);
int strcmp(char s1[], char s2[]);
char* strtok(char* str, const char* delimeters); // string tokenizer, basically allows for inputs and filenames to be handled properly
char* strdup(char* org); // String duplication, useful for copying strings
static bool is_delimiter(char c, const char* delimeters); // Helper functions
#endif