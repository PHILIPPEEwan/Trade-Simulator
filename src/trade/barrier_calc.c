/*
** EPITECH PROJECT, 2025
** Trade Barrier Impact Simulator
** File description:
** Trade barrier calculation implementation
*/

#include "trade/barrier_calc.h"
#include <math.h>

double calculate_tariff_impact(trade_barrier_t *barrier,
    double base_value, double volume)
{
    double tariff_amount = 0;
    double new_value = 0;

    if (!barrier || barrier->type != BARRIER_TARIFF_FIXED)
        return base_value;
    tariff_amount = base_value * barrier->rate;
    new_value = base_value + tariff_amount;
    if (barrier->type == BARRIER_TARIFF_PROGRESSIVE &&
        volume > barrier->threshold) {
        double excess = volume - barrier->threshold;
        double excess_val = (base_value / volume) * excess;
        new_value += excess_val * barrier->secondary_rate;
    }
    return new_value;
}

double calculate_quota_impact(trade_barrier_t *barrier,
    double current_volume)
{
    if (!barrier)
        return current_volume;
    if (barrier->type == BARRIER_QUOTA_ABSOLUTE)
        return fmin(current_volume, barrier->threshold);
    return current_volume;
}

double calculate_subsidy_effect(trade_barrier_t *barrier,
    double base_price)
{
    if (!barrier || barrier->type != BARRIER_SUBSIDY)
        return base_price;
    return base_price * (1.0 - barrier->rate);
}

static bool barrier_applies_to_flow(trade_barrier_t *barrier,
    trade_flow_t *flow)
{
    if (barrier->source_country &&
        flow->exporter != barrier->source_country)
        return false;
    if (barrier->target_country &&
        flow->importer != barrier->target_country)
        return false;
    if (barrier->product && flow->product != barrier->product)
        return false;
    return true;
}

static void apply_tariff(trade_flow_t *flow,
    trade_barrier_t *barrier)
{
    double price_increase = barrier->rate;

    flow->value = calculate_tariff_impact(barrier, flow->value,
        flow->volume);
    flow->volume *= (1.0 + flow->product->elasticity *
        price_increase);
}

static void apply_quota(trade_flow_t *flow,
    trade_barrier_t *barrier)
{
    flow->volume = calculate_quota_impact(barrier, flow->volume);
    if (flow->volume < 0.01)
        flow->value = 0;
    else
        flow->value = (flow->value / flow->volume) * flow->volume;
}

static void apply_embargo(trade_flow_t *flow)
{
    flow->volume = 0;
    flow->value = 0;
}

void apply_barrier_to_flow(trade_flow_t *flow,
    trade_barrier_t *barrier)
{
    if (!flow || !barrier || !barrier->is_active)
        return;
    if (!barrier_applies_to_flow(barrier, flow))
        return;
    if (barrier->type == BARRIER_TARIFF_FIXED ||
        barrier->type == BARRIER_TARIFF_PROGRESSIVE)
        apply_tariff(flow, barrier);
    else if (barrier->type == BARRIER_QUOTA_ABSOLUTE ||
        barrier->type == BARRIER_QUOTA_TARIFF_RATE)
        apply_quota(flow, barrier);
    else if (barrier->type == BARRIER_EMBARGO)
        apply_embargo(flow);
}
