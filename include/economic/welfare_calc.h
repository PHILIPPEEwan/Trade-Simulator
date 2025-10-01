/*
** EPITECH PROJECT, 2025
** Trade Barrier Impact Simulator
** File description:
** Welfare analysis calculations
*/

#ifndef WELFARE_CALC_H
    #define WELFARE_CALC_H

    #include "types.h"

double calculate_total_welfare_change(economic_impact_t *impact);
double calculate_net_welfare(double consumer_surplus,
    double producer_surplus, double gov_revenue,
    double deadweight);
double estimate_employment_impact(double trade_change,
    double labor_intensity, double multiplier);
double estimate_gdp_impact(double trade_change,
    double trade_gdp_ratio, double multiplier);

#endif
