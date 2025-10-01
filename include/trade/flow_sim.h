/*
** EPITECH PROJECT, 2025
** Trade Barrier Impact Simulator
** File description:
** Trade flow simulation
*/

#ifndef FLOW_SIM_H
    #define FLOW_SIM_H

    #include "types.h"

trade_flow_t *simulate_trade_flows(trade_flow_t *base_flows,
    trade_barrier_t *barriers, simulation_params_t *params);
void simulate_cascade_effects(trade_flow_t *flows,
    country_t *countries, product_t *products);

#endif
