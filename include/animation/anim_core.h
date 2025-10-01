/*
** EPITECH PROJECT, 2025
** Trade Barrier Impact Simulator
** File description:
** Animation system core management
*/

#ifndef ANIM_CORE_H
    #define ANIM_CORE_H

    #include <stdbool.h>
    #include "types.h"

    #define YEAR_DURATION_SECONDS 3.0f
    #define TRADE_FLOW_DURATION 2.0f
    #define IMPACT_FADE_DURATION 1.0f
    #define MAX_CONCURRENT_ANIMATIONS 100

typedef struct trade_arrow_s trade_arrow_t;
typedef struct impact_animation_s impact_animation_t;
typedef struct barrier_animation_s barrier_animation_t;
typedef struct timeline_event_s timeline_event_t;

typedef struct animation_manager_s {
    trade_arrow_t *trade_arrows;
    impact_animation_t *impact_animations;
    barrier_animation_t *barrier_animations;
    timeline_event_t *timeline;
    float current_time;
    bool auto_play;
    float playback_speed;
    int current_year_display;
    int total_simulation_years;
} animation_manager_t;

animation_manager_t *create_animation_manager(void);
void free_animation_manager(animation_manager_t *manager);
void reset_animation(animation_manager_t *manager);
void set_animation_time(animation_manager_t *manager,
    float time);
void play_animation(animation_manager_t *manager);
void pause_animation(animation_manager_t *manager);

#endif
