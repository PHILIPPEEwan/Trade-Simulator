/*
** EPITECH PROJECT, 2025
** Trade Barrier Impact Simulator
** File description:
** Interactive tooltip system
*/

#ifndef GUI_TOOLTIP_H
    #define GUI_TOOLTIP_H

    #include <SFML/Graphics.h>
    #include "types.h"
    #include "gui/gui_core.h"

typedef struct app_state_s app_state_t;

void update_hovered_country(gui_state_t *gui, sfVector2i mouse_pos);
void render_tooltip(gui_state_t *gui, app_state_t *state);

#endif
