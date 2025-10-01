/*
** EPITECH PROJECT, 2025
** Trade Barrier Impact Simulator
** File description:
** Economic impact calculation functions
*/

#ifndef IMPACT_CALC_H
    #define IMPACT_CALC_H

    #include "types.h"

economic_impact_t *calculate_economic_impact(
    trade_flow_t *base_flows, trade_flow_t *sim_flows,
    trade_barrier_t *barriers);
double calculate_consumer_surplus(double price_before,
    double price_after, double quantity, double elasticity);
double calculate_producer_surplus(double price_before,
    double price_after, double quantity, double elasticity);
double calculate_deadweight_loss(double tariff_rate,
    double quantity_change, double price);
double calculate_government_revenue(trade_barrier_t *barriers,
    trade_flow_t *flows);

#endif
