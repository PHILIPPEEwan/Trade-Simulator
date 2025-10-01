/*
** EPITECH PROJECT, 2025
** Trade Barrier Impact Simulator
** File description:
** Economic impact animations
*/

#ifndef ANIM_IMPACTS_H
    #define ANIM_IMPACTS_H

    #include "animation/anim_core.h"
    #include "map/world_map.h"
    #include "gui/gui_core.h"

struct impact_animation_s {
    char country_code[MAX_CODE_LEN];
    double start_impact;
    double target_impact;
    double current_impact;
    float progress;
    float duration;
    bool is_active;
    struct impact_animation_s *next;
};

void create_impact_animation(animation_manager_t *manager,
    const char *code, double current, double target,
    float duration);
void update_impact_animations(animation_manager_t *manager,
    float delta, world_map_t *map, gui_state_t *gui);

#endif
