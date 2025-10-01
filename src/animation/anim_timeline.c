/*
** EPITECH PROJECT, 2025
** Trade Barrier Impact Simulator
** File description:
** Animation timeline implementation
*/

#include "animation/anim_timeline.h"
#include "utils/utils_memory.h"
#include <stdio.h>

void add_timeline_event(animation_manager_t *manager,
    float time, trade_barrier_t *barrier, bool is_removal)
{
    timeline_event_t *event = NULL;

    if (!manager || !barrier)
        return;
    event = safe_malloc(sizeof(timeline_event_t));
    event->time = time;
    event->event_type = barrier->type;
    event->barrier = barrier;
    event->is_removal = is_removal;
    event->next = manager->timeline;
    manager->timeline = event;
}

void build_simulation_timeline(animation_manager_t *manager,
    trade_barrier_t *barriers, int years)
{
    trade_barrier_t *barrier = barriers;
    float time_step = 1.0f;

    if (!manager)
        return;
    manager->total_simulation_years = years;
    while (barrier) {
        add_timeline_event(manager, time_step, barrier, false);
        if (time_step + 3.0f < years)
            add_timeline_event(manager, time_step + 3.0f,
                barrier, true);
        time_step += 1.5f;
        barrier = barrier->next;
    }
}

static void process_event(timeline_event_t *event)
{
    if (event->is_removal) {
        event->barrier->is_active = false;
        printf("Barrier removed\n");
    } else {
        event->barrier->is_active = true;
        printf("Barrier activated\n");
    }
}

void process_timeline_events(animation_manager_t *manager,
    float current_time)
{
    timeline_event_t *event = NULL;

    if (!manager)
        return;
    event = manager->timeline;
    while (event) {
        if (event->time <= current_time &&
            event->time > current_time - 0.1f)
            process_event(event);
        event = event->next;
    }
}
