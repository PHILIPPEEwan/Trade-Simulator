/*
** EPITECH PROJECT, 2025
** Trade Barrier Impact Simulator
** File description:
** Trade barrier calculation functions
*/

#ifndef BARRIER_CALC_H
    #define BARRIER_CALC_H

    #include "types.h"

double calculate_tariff_impact(trade_barrier_t *barrier,
    double base_value, double volume);
double calculate_quota_impact(trade_barrier_t *barrier,
    double current_volume);
double calculate_subsidy_effect(trade_barrier_t *barrier,
    double base_price);
void apply_barrier_to_flow(trade_flow_t *flow,
    trade_barrier_t *barrier);

#endif
