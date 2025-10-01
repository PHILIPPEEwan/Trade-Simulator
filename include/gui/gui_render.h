/*
** EPITECH PROJECT, 2025
** Trade Barrier Impact Simulator
** File description:
** GUI rendering functions
*/

#ifndef GUI_RENDER_H
    #define GUI_RENDER_H

    #include "gui/gui_core.h"
    #include "types.h"

typedef struct render_context_s {
    gui_state_t *gui;
    country_t *countries;
    product_t *products;
    trade_flow_t *flows;
    trade_barrier_t *barriers;
} render_context_t;

void gui_render_frame(const render_context_t *ctx);
void gui_clear_screen(gui_state_t *gui);
void render_status_bar(gui_state_t *gui);
void render_status_text_public(gui_state_t *gui);

#endif
