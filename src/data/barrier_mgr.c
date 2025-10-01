/*
** EPITECH PROJECT, 2025
** Trade Barrier Impact Simulator
** File description:
** Trade barrier management implementation
*/

#include <stdlib.h>
#include "data/barrier_mgr.h"
#include "utils/utils_memory.h"

trade_barrier_t *create_barrier(barrier_type_t type, double rate,
    country_t *src, country_t *tgt)
{
    trade_barrier_t *barrier = safe_malloc(
        sizeof(trade_barrier_t));

    barrier->type = type;
    barrier->rate = rate;
    barrier->secondary_rate = 0.0;
    barrier->threshold = 0.0;
    barrier->source_country = src;
    barrier->target_country = tgt;
    barrier->product = NULL;
    barrier->is_active = true;
    barrier->next = NULL;
    return barrier;
}

static trade_barrier_t *get_last_barrier(trade_barrier_t *list)
{
    trade_barrier_t *current = list;

    while (current->next != NULL)
        current = current->next;
    return current;
}

void add_barrier(trade_barrier_t **list, trade_barrier_t *barrier)
{
    trade_barrier_t *last = NULL;

    if (!list || !barrier)
        return;
    if (*list == NULL) {
        *list = barrier;
        return;
    }
    last = get_last_barrier(*list);
    last->next = barrier;
}

void remove_barrier(trade_barrier_t **list,
    trade_barrier_t *barrier)
{
    trade_barrier_t *current = NULL;

    if (!list || !*list || !barrier)
        return;
    if (*list == barrier) {
        *list = barrier->next;
        free(barrier);
        return;
    }
    current = *list;
    while (current->next && current->next != barrier)
        current = current->next;
    if (current->next == barrier) {
        current->next = barrier->next;
        free(barrier);
    }
}

void free_trade_barriers(trade_barrier_t *list)
{
    trade_barrier_t *temp = NULL;

    while (list != NULL) {
        temp = list;
        list = list->next;
        free(temp);
    }
}
