/*
** EPITECH PROJECT, 2025
** Trade Barrier Impact Simulator
** File description:
** Main initialization functions implementation
*/

#include <stdio.h>
#include "main/main_init.h"
#include "csv/csv_loader.h"
#include "data/country_mgr.h"
#include "data/product_mgr.h"
#include "data/flow_mgr.h"
#include "data/barrier_mgr.h"
#include "scenario/scenario_mgr.h"

void init_sim_params(simulation_params_t *params)
{
    params->time_horizon_years = 10;
    params->enable_retaliation = true;
    params->enable_supply_chain_effects = true;
    params->retaliation_threshold = 0.15;
    params->currency_volatility = 0.08;
}

bool init_simulation_data(app_state_t *state)
{
    printf("Loading simulation data...\n");
    state->countries = load_countries("data/countries.csv");
    if (!state->countries) {
        printf("Failed to load countries\n");
        return false;
    }
    printf("Countries loaded successfully\n");
    state->products = load_products("data/products.csv");
    if (!state->products) {
        printf("Failed to load products\n");
        return false;
    }
    printf("Products loaded successfully\n");
    state->trade_flows = load_trade_flows("data/trade_flows.csv",
        state->countries, state->products);
    if (!state->trade_flows) {
        printf("Failed to load trade flows\n");
        return false;
    }
    printf("Trade flows loaded successfully\n");
    load_elasticities("data/elasticities.csv",
        state->products);
    printf("Elasticities loaded successfully\n");
    return true;
}

void cleanup_app_state(app_state_t *state)
{
    if (!state)
        return;
    free_countries(state->countries);
    free_products(state->products);
    free_trade_flows(state->trade_flows);
    free_trade_barriers(state->barriers);
    free_scenarios(state->scenarios);
}

void apply_scenario(app_state_t *state, int scenario_index)
{
    country_t *usa = NULL;
    country_t *china = NULL;
    country_t *eu_countries[] = {NULL, NULL, NULL, NULL, NULL, NULL};
    int i = 0;

    if (!state)
        return;
    free_trade_barriers(state->barriers);
    state->barriers = NULL;
    if (scenario_index == 0) {
        return;
    }
    usa = find_country(state->countries, "USA");
    china = find_country(state->countries, "CHN");
    eu_countries[0] = find_country(state->countries, "DEU");
    eu_countries[1] = find_country(state->countries, "FRA");
    eu_countries[2] = find_country(state->countries, "ITA");
    eu_countries[3] = find_country(state->countries, "ESP");
    eu_countries[4] = find_country(state->countries, "NLD");
    eu_countries[5] = find_country(state->countries, "BEL");
    if (scenario_index == 1 && usa && china) {
        trade_barrier_t *b1 = create_barrier(
            BARRIER_TARIFF_FIXED, 0.25, china, usa);
        trade_barrier_t *b2 = create_barrier(
            BARRIER_TARIFF_FIXED, 0.60, usa, china);
        trade_barrier_t *b3 = create_barrier(
            BARRIER_TARIFF_FIXED, 0.15, china, NULL);
        b1->is_active = true;
        b2->is_active = true;
        b3->is_active = true;
        add_barrier(&state->barriers, b1);
        add_barrier(&state->barriers, b2);
        add_barrier(&state->barriers, b3);
    } else if (scenario_index == 2) {
        while (i < 6 && eu_countries[i]) {
            trade_barrier_t *b = create_barrier(
                BARRIER_TARIFF_FIXED, 0.18, NULL, eu_countries[i]);
            b->is_active = true;
            add_barrier(&state->barriers, b);
            i++;
        }
    }
}
