/*
** EPITECH PROJECT, 2025
** Trade Barrier Impact Simulator
** File description:
** CSV data loading implementation
*/

#include <stdlib.h>
#include "csv/csv_loader.h"
#include "csv/csv_parser.h"
#include "data/country_mgr.h"
#include "data/product_mgr.h"
#include "data/flow_mgr.h"

country_t *load_countries(const char *filename)
{
    csv_data_t *data = parse_csv_file(filename);
    country_t *countries = NULL;
    csv_row_t *row = NULL;

    if (!data)
        return NULL;
    row = data->rows->next;
    while (row) {
        if (row->field_count >= 4) {
            country_t *country = create_country(
                row->fields[0], row->fields[1],
                atof(row->fields[2]), atof(row->fields[3]));
            add_country(&countries, country);
        }
        row = row->next;
    }
    free_csv_data(data);
    return countries;
}

product_t *load_products(const char *filename)
{
    csv_data_t *data = parse_csv_file(filename);
    product_t *products = NULL;
    csv_row_t *row = NULL;

    if (!data)
        return NULL;
    row = data->rows->next;
    while (row) {
        if (row->field_count >= 4) {
            product_t *product = create_product(
                row->fields[0], row->fields[1], row->fields[2],
                atof(row->fields[3]));
            add_product(&products, product);
        }
        row = row->next;
    }
    free_csv_data(data);
    return products;
}

trade_flow_t *load_trade_flows(const char *filename,
    country_t *countries, product_t *products)
{
    csv_data_t *data = parse_csv_file(filename);
    trade_flow_t *flows = NULL;
    csv_row_t *row = NULL;

    if (!data)
        return NULL;
    row = data->rows->next;
    while (row) {
        if (row->field_count >= 5) {
            country_t *exp = find_country(countries,
                row->fields[0]);
            country_t *imp = find_country(countries,
                row->fields[1]);
            product_t *prod = find_product(products,
                row->fields[2]);
            if (exp && imp && prod) {
                trade_flow_t *flow = create_trade_flow(exp, imp,
                    prod, atof(row->fields[3]),
                    atof(row->fields[4]));
                add_trade_flow(&flows, flow);
            }
        }
        row = row->next;
    }
    free_csv_data(data);
    return flows;
}

bool load_elasticities(const char *filename,
    product_t *products)
{
    csv_data_t *data = parse_csv_file(filename);
    csv_row_t *row = NULL;

    if (!data)
        return false;
    row = data->rows->next;
    while (row) {
        if (row->field_count >= 2) {
            product_t *prod = find_product(products,
                row->fields[0]);
            if (prod)
                prod->elasticity = atof(row->fields[1]);
        }
        row = row->next;
    }
    free_csv_data(data);
    return true;
}
