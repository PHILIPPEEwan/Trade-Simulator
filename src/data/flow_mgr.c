/*
** EPITECH PROJECT, 2025
** Trade Barrier Impact Simulator
** File description:
** Trade flow management implementation
*/

#include <stdlib.h>
#include <string.h>
#include "data/flow_mgr.h"
#include "utils/utils_memory.h"

trade_flow_t *create_trade_flow(country_t *exp, country_t *imp,
    product_t *prod, double vol, double val)
{
    trade_flow_t *flow = NULL;

    if (!exp || !imp || !prod)
        return NULL;
    flow = safe_malloc(sizeof(trade_flow_t));
    flow->exporter = exp;
    flow->importer = imp;
    flow->product = prod;
    flow->volume = vol;
    flow->value = val;
    flow->year = 2024;
    flow->next = NULL;
    return flow;
}

static trade_flow_t *get_last_flow(trade_flow_t *list)
{
    trade_flow_t *current = list;

    while (current->next != NULL)
        current = current->next;
    return current;
}

void add_trade_flow(trade_flow_t **list, trade_flow_t *flow)
{
    trade_flow_t *last = NULL;

    if (!list || !flow)
        return;
    if (*list == NULL) {
        *list = flow;
        return;
    }
    last = get_last_flow(*list);
    last->next = flow;
}

trade_flow_t *find_trade_flow(trade_flow_t *list,
    const char *exp_code, const char *imp_code)
{
    while (list != NULL) {
        if (strcmp(list->exporter->code, exp_code) == 0 &&
            strcmp(list->importer->code, imp_code) == 0)
            return list;
        list = list->next;
    }
    return NULL;
}

void free_trade_flows(trade_flow_t *list)
{
    trade_flow_t *temp = NULL;

    while (list != NULL) {
        temp = list;
        list = list->next;
        free(temp);
    }
}

double get_total_trade_value(trade_flow_t *list)
{
    double total = 0.0;

    while (list != NULL) {
        total += list->value;
        list = list->next;
    }
    return total;
}
