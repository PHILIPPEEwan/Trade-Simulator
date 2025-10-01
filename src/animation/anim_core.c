/*
** EPITECH PROJECT, 2025
** Trade Barrier Impact Simulator
** File description:
** Animation system core implementation
*/

#include "animation/anim_core.h"
#include "animation/anim_arrows.h"
#include "utils/utils_memory.h"
#include <stdlib.h>

animation_manager_t *create_animation_manager(void)
{
    animation_manager_t *mgr = safe_malloc(
        sizeof(animation_manager_t));

    mgr->trade_arrows = NULL;
    mgr->impact_animations = NULL;
    mgr->barrier_animations = NULL;
    mgr->timeline = NULL;
    mgr->current_time = 0.0f;
    mgr->auto_play = true;
    mgr->playback_speed = 1.0f;
    mgr->current_year_display = 0;
    mgr->total_simulation_years = 10;
    return mgr;
}

static void free_arrows(trade_arrow_t *arrows)
{
    trade_arrow_t *arrow = arrows;

    while (arrow) {
        trade_arrow_t *next = arrow->next;
        free(arrow);
        arrow = next;
    }
}

void free_animation_manager(animation_manager_t *manager)
{
    if (!manager)
        return;
    free_arrows(manager->trade_arrows);
    free(manager);
}

void reset_animation(animation_manager_t *manager)
{
    trade_arrow_t *arrow = NULL;

    if (!manager)
        return;
    manager->current_time = 0.0f;
    manager->current_year_display = 0;
    arrow = manager->trade_arrows;
    while (arrow) {
        arrow->progress = 0.0f;
        arrow->current_pos = arrow->start_pos;
        arrow->is_visible = false;
        arrow = arrow->next;
    }
}

void set_animation_time(animation_manager_t *manager,
    float time)
{
    if (!manager)
        return;
    manager->current_time = time;
    manager->current_year_display = (int)time;
}

void play_animation(animation_manager_t *manager)
{
    if (!manager)
        return;
    manager->auto_play = true;
}

void pause_animation(animation_manager_t *manager)
{
    if (!manager)
        return;
    manager->auto_play = false;
}
