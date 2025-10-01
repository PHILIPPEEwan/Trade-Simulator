/*
** EPITECH PROJECT, 2025
** Trade Barrier Impact Simulator
** File description:
** Dynamic economic events system
*/

#ifndef SCENARIO_EVENTS_H
    #define SCENARIO_EVENTS_H

    #include "types.h"
    #include "gui/gui_core.h"

typedef struct app_state_s app_state_t;

typedef enum event_type_e {
    EVENT_NONE,
    EVENT_RECESSION,
    EVENT_BOOM,
    EVENT_TRADE_AGREEMENT,
    EVENT_SANCTIONS,
    EVENT_CURRENCY_CRISIS
} event_type_t;

typedef struct economic_event_s {
    event_type_t type;
    char country_code[MAX_CODE_LEN];
    char description[256];
    float duration;
    float elapsed;
    bool is_active;
} economic_event_t;

void update_events(app_state_t *state, gui_state_t *gui, float delta_time);
void render_event_notifications(gui_state_t *gui, app_state_t *state);

#endif
