/*
** EPITECH PROJECT, 2025
** Trade Barrier Impact Simulator
** File description:
** Input/output utility functions
*/

#ifndef UTILS_IO_H
    #define UTILS_IO_H

    #include <stdbool.h>
    #include <stddef.h>

void clear_screen(void);
void pause_screen(void);
void print_separator(int width);
void print_centered(const char *text, int width);
bool file_exists(const char *filename);
long file_size(const char *filename);
char *read_file_contents(const char *filename);
void print_error(const char *format, ...);
void print_info(const char *format, ...);

#endif
