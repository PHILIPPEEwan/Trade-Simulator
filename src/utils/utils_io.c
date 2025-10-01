/*
** EPITECH PROJECT, 2025
** Trade Barrier Impact Simulator
** File description:
** Input/output utility functions implementation
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "utils/utils_io.h"
#include "utils/utils_memory.h"

void clear_screen(void)
{
    #ifdef _WIN32
    system("cls");
    #else
    system("clear");
    #endif
}

void pause_screen(void)
{
    printf("Press Enter to continue...");
    getchar();
}

void print_separator(int width)
{
    int i = 0;

    while (i < width) {
        printf("-");
        i++;
    }
    printf("\n");
}

void print_centered(const char *text, int width)
{
    int text_len = strlen(text);
    int padding = (width - text_len) / 2;
    int i = 0;

    while (i < padding) {
        printf(" ");
        i++;
    }
    printf("%s\n", text);
}

bool file_exists(const char *filename)
{
    FILE *file = fopen(filename, "r");

    if (!file)
        return false;
    fclose(file);
    return true;
}

long file_size(const char *filename)
{
    FILE *file = fopen(filename, "rb");
    long size = 0;

    if (!file)
        return -1;
    fseek(file, 0, SEEK_END);
    size = ftell(file);
    fclose(file);
    return size;
}

char *read_file_contents(const char *filename)
{
    FILE *file = fopen(filename, "r");
    long size = 0;
    char *buffer = NULL;

    if (!file)
        return NULL;
    fseek(file, 0, SEEK_END);
    size = ftell(file);
    fseek(file, 0, SEEK_SET);
    buffer = safe_malloc(size + 1);
    fread(buffer, 1, size, file);
    buffer[size] = '\0';
    fclose(file);
    return buffer;
}

void print_error(const char *format, ...)
{
    va_list args;

    printf("ERROR: ");
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
    printf("\n");
}

void print_info(const char *format, ...)
{
    va_list args;

    printf("INFO: ");
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
    printf("\n");
}
