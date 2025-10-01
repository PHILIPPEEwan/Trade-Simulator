/*
** EPITECH PROJECT, 2025
** Trade Barrier Impact Simulator
** File description:
** Welfare analysis implementation
*/

#include "economic/welfare_calc.h"

double calculate_total_welfare_change(economic_impact_t *impact)
{
    if (!impact)
        return 0;
    return impact->consumer_surplus_change +
        impact->producer_surplus_change +
        impact->government_revenue -
        impact->deadweight_loss;
}

double calculate_net_welfare(double consumer_surplus,
    double producer_surplus, double gov_revenue,
    double deadweight)
{
    return consumer_surplus + producer_surplus +
        gov_revenue - deadweight;
}

double estimate_employment_impact(double trade_change,
    double labor_intensity, double multiplier)
{
    double direct_jobs = (trade_change / 1e6) * labor_intensity;
    return direct_jobs * multiplier;
}

double estimate_gdp_impact(double trade_change,
    double trade_gdp_ratio, double multiplier)
{
    double direct_impact = trade_change / trade_gdp_ratio;
    return direct_impact * multiplier;
}
