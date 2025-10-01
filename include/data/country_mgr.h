/*
** EPITECH PROJECT, 2025
** Trade Barrier Impact Simulator
** File description:
** Country management module
*/

#ifndef COUNTRY_MGR_H
    #define COUNTRY_MGR_H

    #include "types.h"

country_t *create_country(const char *code, const char *name,
    double gdp, double pop);
void add_country(country_t **list, country_t *country);
country_t *find_country(country_t *list, const char *code);
void free_countries(country_t *list);
int count_countries(country_t *list);

#endif
