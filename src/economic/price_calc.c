/*
** EPITECH PROJECT, 2025
** Trade Barrier Impact Simulator
** File description:
** Price calculation implementation
*/

#include "economic/price_calc.h"

double calculate_price_impact(double tariff_rate,
    double elasticity, double pass_through_rate)
{
    return tariff_rate * pass_through_rate *
        (1.0 / (1.0 - elasticity));
}

double calculate_consumer_price(double base_price,
    double tariff_rate, double market_power)
{
    double tariff_amount = base_price * tariff_rate;
    double markup = tariff_amount * market_power;

    return base_price + tariff_amount + markup;
}

double calculate_producer_price(double base_price,
    double tariff_rate, double subsidy_rate)
{
    double effective_price = base_price *
        (1.0 - tariff_rate * 0.3);

    if (subsidy_rate > 0)
        effective_price *= (1.0 + subsidy_rate);
    return effective_price;
}
