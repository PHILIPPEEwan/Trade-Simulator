/*
** EPITECH PROJECT, 2025
** Trade Barrier Impact Simulator
** File description:
** Scenario management
*/

#ifndef SCENARIO_MGR_H
    #define SCENARIO_MGR_H

    #include "types.h"
    #include <stdbool.h>

scenario_t *create_scenario(const char *name,
    trade_barrier_t *barriers, economic_impact_t *impacts);
void add_scenario(scenario_t **list, scenario_t *scenario);
scenario_t *find_scenario(scenario_t *list, const char *name);
void free_scenarios(scenario_t *list);
int count_scenarios(scenario_t *list);
void compare_scenarios(scenario_t *s1, scenario_t *s2);

#endif
