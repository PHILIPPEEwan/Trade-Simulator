/*
** EPITECH PROJECT, 2025
** Trade Barrier Impact Simulator
** File description:
** Product management module
*/

#ifndef PRODUCT_MGR_H
    #define PRODUCT_MGR_H

    #include "types.h"

product_t *create_product(const char *hs_code, const char *name,
    const char *category, double price);
void add_product(product_t **list, product_t *product);
product_t *find_product(product_t *list, const char *hs_code);
void free_products(product_t *list);
int count_products(product_t *list);

#endif
