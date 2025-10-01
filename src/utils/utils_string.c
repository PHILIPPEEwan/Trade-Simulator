/*
** EPITECH PROJECT, 2025
** Trade Barrier Impact Simulator
** File description:
** String manipulation utilities implementation
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "utils/utils_string.h"

void trim_whitespace(char *str)
{
    char *start = NULL;
    char *end = NULL;
    size_t len = 0;

    if (!str)
        return;
    start = str;
    while (isspace((unsigned char)*start))
        start++;
    end = str + strlen(str) - 1;
    while (end > start && isspace((unsigned char)*end))
        end--;
    len = end - start + 1;
    if (start != str)
        memmove(str, start, len);
    str[len] = '\0';
}

void to_uppercase(char *str)
{
    char *p = NULL;

    if (!str)
        return;
    p = str;
    while (*p) {
        *p = toupper((unsigned char)*p);
        p++;
    }
}

void to_lowercase(char *str)
{
    char *p = NULL;

    if (!str)
        return;
    p = str;
    while (*p) {
        *p = tolower((unsigned char)*p);
        p++;
    }
}

static bool check_numeric_chars(const char *p)
{
    bool has_dot = false;

    while (*p) {
        if (*p == '.') {
            if (has_dot)
                return false;
            has_dot = true;
        } else if (!isdigit((unsigned char)*p))
            return false;
        p++;
    }
    return true;
}

bool is_numeric(const char *str)
{
    const char *p = str;

    if (!str || !*str)
        return false;
    if (*p == '-' || *p == '+')
        p++;
    return check_numeric_chars(p);
}

char *format_currency(double amount)
{
    static char buffer[64];

    if (fabs(amount) >= 1e12)
        snprintf(buffer, sizeof(buffer), "$%.2fT", amount / 1e12);
    else if (fabs(amount) >= 1e9)
        snprintf(buffer, sizeof(buffer), "$%.2fB", amount / 1e9);
    else if (fabs(amount) >= 1e6)
        snprintf(buffer, sizeof(buffer), "$%.2fM", amount / 1e6);
    else if (fabs(amount) >= 1e3)
        snprintf(buffer, sizeof(buffer), "$%.2fK", amount / 1e3);
    else
        snprintf(buffer, sizeof(buffer), "$%.2f", amount);
    return buffer;
}

char *format_percentage(double value)
{
    static char buffer[32];

    snprintf(buffer, sizeof(buffer), "%.2f%%", value * 100);
    return buffer;
}
