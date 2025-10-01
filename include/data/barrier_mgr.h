/*
** EPITECH PROJECT, 2025
** Trade Barrier Impact Simulator
** File description:
** Trade barrier management module
*/

#ifndef BARRIER_MGR_H
    #define BARRIER_MGR_H

    #include "types.h"

trade_barrier_t *create_barrier(barrier_type_t type, double rate,
    country_t *src, country_t *tgt);
void add_barrier(trade_barrier_t **list, trade_barrier_t *barrier);
void remove_barrier(trade_barrier_t **list,
    trade_barrier_t *barrier);
void free_trade_barriers(trade_barrier_t *list);

#endif
