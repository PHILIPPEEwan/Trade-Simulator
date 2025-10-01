/*
** EPITECH PROJECT, 2025
** Trade Barrier Impact Simulator
** File description:
** Preset scenario creation implementation
*/

#include "scenario/scenario_presets.h"
#include "data/barrier_mgr.h"
#include "data/country_mgr.h"
#include <stddef.h>

trade_barrier_t *create_trade_war_scenario(country_t *countries,
    product_t *products)
{
    trade_barrier_t *barriers = NULL;
    country_t *usa = find_country(countries, "USA");
    country_t *china = find_country(countries, "CHN");

    (void)products;
    if (usa && china) {
        trade_barrier_t *t1 = create_barrier(
            BARRIER_TARIFF_FIXED, 0.25, china, usa);
        trade_barrier_t *t2 = create_barrier(
            BARRIER_TARIFF_FIXED, 0.20, usa, china);
        add_barrier(&barriers, t1);
        add_barrier(&barriers, t2);
    }
    return barriers;
}

trade_barrier_t *create_protectionist_scenario(
    country_t *country, product_t *products)
{
    trade_barrier_t *barriers = NULL;
    trade_barrier_t *tariff = NULL;

    (void)products;
    if (!country)
        return barriers;
    tariff = create_barrier(BARRIER_TARIFF_FIXED, 0.15,
        NULL, country);
    add_barrier(&barriers, tariff);
    return barriers;
}

trade_barrier_t *create_free_trade_scenario(void)
{
    return NULL;
}
