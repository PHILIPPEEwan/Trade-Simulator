/*
** EPITECH PROJECT, 2025
** Trade Barrier Impact Simulator
** File description:
** Main initialization functions
*/

#ifndef MAIN_INIT_H
    #define MAIN_INIT_H

    #include "types.h"
    #include <stdbool.h>

typedef struct app_state_s {
    country_t *countries;
    product_t *products;
    trade_flow_t *trade_flows;
    trade_barrier_t *barriers;
    scenario_t *scenarios;
    simulation_params_t sim_params;
} app_state_t;

bool init_simulation_data(app_state_t *state);
void cleanup_app_state(app_state_t *state);
void init_sim_params(simulation_params_t *params);
void apply_scenario(app_state_t *state, int scenario_index);

#endif
