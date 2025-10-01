/*
** EPITECH PROJECT, 2025
** Trade Barrier Impact Simulator
** File description:
** Preset scenario creation
*/

#ifndef SCENARIO_PRESETS_H
    #define SCENARIO_PRESETS_H

    #include "types.h"

trade_barrier_t *create_trade_war_scenario(country_t *countries,
    product_t *products);
trade_barrier_t *create_protectionist_scenario(
    country_t *country, product_t *products);
trade_barrier_t *create_free_trade_scenario(void);

#endif
