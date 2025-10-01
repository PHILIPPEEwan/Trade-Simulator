/*
** EPITECH PROJECT, 2025
** Trade Barrier Impact Simulator
** File description:
** Product management implementation
*/

#include <stdlib.h>
#include <string.h>
#include "data/product_mgr.h"
#include "utils/utils_memory.h"

static void init_product_fields(product_t *product,
    const char *hs_code, const char *name, const char *category)
{
    safe_strncpy(product->hs_code, hs_code, MAX_CODE_LEN);
    safe_strncpy(product->name, name, MAX_NAME_LEN);
    safe_strncpy(product->category, category, MAX_NAME_LEN);
    product->elasticity = DEFAULT_ELASTICITY;
    product->next = NULL;
}

product_t *create_product(const char *hs_code, const char *name,
    const char *category, double price)
{
    product_t *product = safe_malloc(sizeof(product_t));

    init_product_fields(product, hs_code, name, category);
    product->base_price = price;
    return product;
}

static product_t *get_last_product(product_t *list)
{
    product_t *current = list;

    while (current->next != NULL)
        current = current->next;
    return current;
}

void add_product(product_t **list, product_t *product)
{
    product_t *last = NULL;

    if (!list || !product)
        return;
    if (*list == NULL) {
        *list = product;
        return;
    }
    last = get_last_product(*list);
    last->next = product;
}

product_t *find_product(product_t *list, const char *hs_code)
{
    while (list != NULL) {
        if (strcmp(list->hs_code, hs_code) == 0)
            return list;
        list = list->next;
    }
    return NULL;
}

void free_products(product_t *list)
{
    product_t *temp = NULL;

    while (list != NULL) {
        temp = list;
        list = list->next;
        free(temp);
    }
}

int count_products(product_t *list)
{
    int count = 0;

    while (list != NULL) {
        count++;
        list = list->next;
    }
    return count;
}
