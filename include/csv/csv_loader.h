/*
** EPITECH PROJECT, 2025
** Trade Barrier Impact Simulator
** File description:
** CSV data loading functions
*/

#ifndef CSV_LOADER_H
    #define CSV_LOADER_H

    #include "types.h"
    #include <stdbool.h>

country_t *load_countries(const char *filename);
product_t *load_products(const char *filename);
trade_flow_t *load_trade_flows(const char *filename,
    country_t *countries, product_t *products);
bool load_elasticities(const char *filename,
    product_t *products);

#endif
