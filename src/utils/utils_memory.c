/*
** EPITECH PROJECT, 2025
** Trade Barrier Impact Simulator
** File description:
** Memory management utilities implementation
*/

#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils/utils_memory.h"

void *safe_malloc(size_t size)
{
    void *ptr = malloc(size);

    if (!ptr && size > 0) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    return ptr;
}

void *safe_realloc(void *ptr, size_t size)
{
    void *new_ptr = realloc(ptr, size);

    if (!new_ptr && size > 0) {
        fprintf(stderr, "Error: Memory realloc failed\n");
        exit(EXIT_FAILURE);
    }
    return new_ptr;
}

char *safe_strdup(const char *str)
{
    char *copy = NULL;

    if (!str)
        return NULL;
    copy = strdup(str);
    if (!copy) {
        fprintf(stderr, "Error: String duplication failed\n");
        exit(EXIT_FAILURE);
    }
    return copy;
}

void safe_strncpy(char *dest, const char *src, size_t n)
{
    if (!dest || !src)
        return;
    strncpy(dest, src, n - 1);
    dest[n - 1] = '\0';
}
