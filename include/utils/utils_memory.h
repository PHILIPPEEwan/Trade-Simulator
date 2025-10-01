/*
** EPITECH PROJECT, 2025
** Trade Barrier Impact Simulator
** File description:
** Memory management utilities
*/

#ifndef UTILS_MEMORY_H
    #define UTILS_MEMORY_H

    #include <stddef.h>

void *safe_malloc(size_t size);
void *safe_realloc(void *ptr, size_t size);
char *safe_strdup(const char *str);
void safe_strncpy(char *dest, const char *src, size_t n);

#endif
