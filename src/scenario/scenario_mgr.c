/*
** EPITECH PROJECT, 2025
** Trade Barrier Impact Simulator
** File description:
** Scenario management implementation
*/

#include "scenario/scenario_mgr.h"
#include "utils/utils_memory.h"
#include "utils/utils_string.h"
#include "economic/welfare_calc.h"
#include <string.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

scenario_t *create_scenario(const char *name,
    trade_barrier_t *barriers, economic_impact_t *impacts)
{
    scenario_t *scenario = safe_malloc(sizeof(scenario_t));

    safe_strncpy(scenario->name, name, MAX_NAME_LEN);
    scenario->barriers = barriers;
    scenario->impacts = impacts;
    scenario->timestamp = (double)time(NULL);
    scenario->next = NULL;
    return scenario;
}

static scenario_t *get_last_scenario(scenario_t *list)
{
    scenario_t *current = list;

    while (current->next != NULL)
        current = current->next;
    return current;
}

void add_scenario(scenario_t **list, scenario_t *scenario)
{
    scenario_t *last = NULL;

    if (!list || !scenario)
        return;
    if (*list == NULL) {
        *list = scenario;
        return;
    }
    last = get_last_scenario(*list);
    last->next = scenario;
}

scenario_t *find_scenario(scenario_t *list, const char *name)
{
    while (list != NULL) {
        if (strcmp(list->name, name) == 0)
            return list;
        list = list->next;
    }
    return NULL;
}

void free_scenarios(scenario_t *list)
{
    scenario_t *temp = NULL;

    while (list != NULL) {
        temp = list;
        list = list->next;
        free(temp);
    }
}

int count_scenarios(scenario_t *list)
{
    int count = 0;

    while (list != NULL) {
        count++;
        list = list->next;
    }
    return count;
}

static void print_scenario_welfare(const char *name,
    economic_impact_t *impacts)
{
    double welfare = calculate_total_welfare_change(impacts);

    printf("  %s: %s\n", name, format_currency(welfare));
}

void compare_scenarios(scenario_t *s1, scenario_t *s2)
{
    double w1 = 0;
    double w2 = 0;

    if (!s1 || !s2)
        return;
    printf("\n=== SCENARIO COMPARISON ===\n\n");
    printf("Scenario 1: %s\n", s1->name);
    printf("Scenario 2: %s\n\n", s2->name);
    if (s1->impacts && s2->impacts) {
        printf("Welfare Impact:\n");
        print_scenario_welfare(s1->name, s1->impacts);
        print_scenario_welfare(s2->name, s2->impacts);
        w1 = calculate_total_welfare_change(s1->impacts);
        w2 = calculate_total_welfare_change(s2->impacts);
        printf("\nRecommendation: ");
        if (w1 > w2)
            printf("%s provides better outcomes\n", s1->name);
        else if (w2 > w1)
            printf("%s provides better outcomes\n", s2->name);
        else
            printf("Both scenarios are similar\n");
    }
}
