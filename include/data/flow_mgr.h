/*
** EPITECH PROJECT, 2025
** Trade Barrier Impact Simulator
** File description:
** Trade flow management module
*/

#ifndef FLOW_MGR_H
    #define FLOW_MGR_H

    #include "types.h"

trade_flow_t *create_trade_flow(country_t *exp, country_t *imp,
    product_t *prod, double vol, double val);
void add_trade_flow(trade_flow_t **list, trade_flow_t *flow);
trade_flow_t *find_trade_flow(trade_flow_t *list,
    const char *exp_code, const char *imp_code);
void free_trade_flows(trade_flow_t *list);
double get_total_trade_value(trade_flow_t *list);

#endif
