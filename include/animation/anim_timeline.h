/*
** EPITECH PROJECT, 2025
** Trade Barrier Impact Simulator
** File description:
** Animation timeline management
*/

#ifndef ANIM_TIMELINE_H
    #define ANIM_TIMELINE_H

    #include "animation/anim_core.h"
    #include "types.h"

struct timeline_event_s {
    float time;
    barrier_type_t event_type;
    trade_barrier_t *barrier;
    bool is_removal;
    struct timeline_event_s *next;
};

void build_simulation_timeline(animation_manager_t *manager,
    trade_barrier_t *barriers, int years);
void add_timeline_event(animation_manager_t *manager,
    float time, trade_barrier_t *barrier, bool is_removal);
void process_timeline_events(animation_manager_t *manager,
    float current_time);

#endif
