/*
** EPITECH PROJECT, 2025
** Trade Barrier Impact Simulator
** File description:
** Trade flow simulation implementation
*/

#include "trade/flow_sim.h"
#include "trade/barrier_calc.h"
#include "data/flow_mgr.h"
#include <stddef.h>

static trade_flow_t *copy_flow(trade_flow_t *flow)
{
    return create_trade_flow(flow->exporter, flow->importer,
        flow->product, flow->volume, flow->value);
}

static void apply_all_barriers(trade_flow_t *flow,
    trade_barrier_t *barriers)
{
    trade_barrier_t *barrier = barriers;

    while (barrier) {
        if (barrier->is_active)
            apply_barrier_to_flow(flow, barrier);
        barrier = barrier->next;
    }
}

trade_flow_t *simulate_trade_flows(trade_flow_t *base_flows,
    trade_barrier_t *barriers, simulation_params_t *params)
{
    trade_flow_t *simulated = NULL;
    trade_flow_t *flow = base_flows;

    (void)params;
    if (!base_flows)
        return NULL;
    while (flow) {
        trade_flow_t *new_flow = copy_flow(flow);
        apply_all_barriers(new_flow, barriers);
        add_trade_flow(&simulated, new_flow);
        flow = flow->next;
    }
    return simulated;
}

void simulate_cascade_effects(trade_flow_t *flows,
    country_t *countries, product_t *products)
{
    (void)flows;
    (void)countries;
    (void)products;
}
