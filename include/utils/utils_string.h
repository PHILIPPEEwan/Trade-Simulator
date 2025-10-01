/*
** EPITECH PROJECT, 2025
** Trade Barrier Impact Simulator
** File description:
** String manipulation utilities
*/

#ifndef UTILS_STRING_H
    #define UTILS_STRING_H

    #include <stdbool.h>

void trim_whitespace(char *str);
void to_uppercase(char *str);
void to_lowercase(char *str);
bool is_numeric(const char *str);
char *format_currency(double amount);
char *format_percentage(double value);

#endif
