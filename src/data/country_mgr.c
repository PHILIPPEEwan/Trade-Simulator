/*
** EPITECH PROJECT, 2025
** Trade Barrier Impact Simulator
** File description:
** Country management implementation
*/

#include <stdlib.h>
#include <string.h>
#include "data/country_mgr.h"
#include "utils/utils_memory.h"

static void init_country_fields(country_t *country,
    const char *code, const char *name)
{
    safe_strncpy(country->code, code, MAX_CODE_LEN);
    safe_strncpy(country->name, name, MAX_NAME_LEN);
    country->exchange_rate = 1.0;
    country->next = NULL;
}

country_t *create_country(const char *code, const char *name,
    double gdp, double pop)
{
    country_t *country = safe_malloc(sizeof(country_t));

    init_country_fields(country, code, name);
    country->gdp = gdp;
    country->population = pop;
    return country;
}

static country_t *get_last_country(country_t *list)
{
    country_t *current = list;

    while (current->next != NULL)
        current = current->next;
    return current;
}

void add_country(country_t **list, country_t *country)
{
    country_t *last = NULL;

    if (!list || !country)
        return;
    if (*list == NULL) {
        *list = country;
        return;
    }
    last = get_last_country(*list);
    last->next = country;
}

country_t *find_country(country_t *list, const char *code)
{
    while (list != NULL) {
        if (strcmp(list->code, code) == 0)
            return list;
        list = list->next;
    }
    return NULL;
}

void free_countries(country_t *list)
{
    country_t *temp = NULL;

    while (list != NULL) {
        temp = list;
        list = list->next;
        free(temp);
    }
}

int count_countries(country_t *list)
{
    int count = 0;

    while (list != NULL) {
        count++;
        list = list->next;
    }
    return count;
}
