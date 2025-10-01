/*
** EPITECH PROJECT, 2025
** Trade Barrier Impact Simulator
** File description:
** Price calculation functions
*/

#ifndef PRICE_CALC_H
    #define PRICE_CALC_H

double calculate_price_impact(double tariff_rate,
    double elasticity, double pass_through_rate);
double calculate_consumer_price(double base_price,
    double tariff_rate, double market_power);
double calculate_producer_price(double base_price,
    double tariff_rate, double subsidy_rate);

#endif
