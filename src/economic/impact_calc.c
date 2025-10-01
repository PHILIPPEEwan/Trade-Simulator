/*
** EPITECH PROJECT, 2025
** Trade Barrier Impact Simulator
** File description:
** Economic impact calculation implementation
*/

#include "economic/impact_calc.h"
#include "utils/utils_memory.h"
#include <math.h>

static void calc_volumes(trade_flow_t *flows, double *volume,
    double *value)
{
    trade_flow_t *flow = flows;

    *volume = 0;
    *value = 0;
    while (flow) {
        *volume += flow->volume;
        *value += flow->value;
        flow = flow->next;
    }
}

economic_impact_t *calculate_economic_impact(
    trade_flow_t *base_flows, trade_flow_t *sim_flows,
    trade_barrier_t *barriers)
{
    economic_impact_t *impact = safe_malloc(
        sizeof(economic_impact_t));
    double base_vol = 0;
    double base_val = 0;
    double sim_vol = 0;
    double sim_val = 0;

    calc_volumes(base_flows, &base_vol, &base_val);
    calc_volumes(sim_flows, &sim_vol, &sim_val);
    impact->trade_volume_change = (sim_vol - base_vol) / base_vol;
    impact->price_change_consumer = (sim_val / sim_vol -
        base_val / base_vol) / (base_val / base_vol);
    impact->price_change_producer =
        impact->price_change_consumer * 0.6;
    impact->government_revenue = calculate_government_revenue(
        barriers, sim_flows);
    impact->consumer_surplus_change = -impact->government_revenue;
    impact->producer_surplus_change = impact->government_revenue * 0.5;
    impact->deadweight_loss = impact->government_revenue * 0.2;
    impact->employment_change = (sim_val - base_val) * 0.05;
    impact->gdp_impact = (sim_val - base_val) * 2.0;
    return impact;
}

double calculate_consumer_surplus(double price_before,
    double price_after, double quantity, double elasticity)
{
    double q_before = quantity * pow((price_after / price_before),
        elasticity);
    return -0.5 * (price_after - price_before) *
        (quantity + q_before);
}

double calculate_producer_surplus(double price_before,
    double price_after, double quantity, double elasticity)
{
    double q_before = quantity * pow((price_after / price_before),
        elasticity);
    return 0.5 * (price_after - price_before) *
        (quantity + q_before);
}

double calculate_deadweight_loss(double tariff_rate,
    double quantity_change, double price)
{
    return 0.5 * tariff_rate * tariff_rate *
        fabs(quantity_change) * price;
}

static bool barrier_applies(trade_barrier_t *barrier,
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

double calculate_government_revenue(trade_barrier_t *barriers,
    trade_flow_t *flows)
{
    double total = 0;
    trade_barrier_t *barrier = barriers;

    while (barrier) {
        if (barrier->type == BARRIER_TARIFF_FIXED) {
            trade_flow_t *flow = flows;
            while (flow) {
                if (barrier_applies(barrier, flow))
                    total += flow->value * barrier->rate;
                flow = flow->next;
            }
        }
        barrier = barrier->next;
    }
    return total;
}
