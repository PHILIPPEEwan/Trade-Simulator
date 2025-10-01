/*
** EPITECH PROJECT, 2025
** Trade Barrier Impact Simulator
** File description:
** Trade flow arrow rendering
*/

#ifndef MAP_ARROWS_H
    #define MAP_ARROWS_H

    #include <SFML/Graphics.h>
    #include "types.h"
    #include "gui/gui_core.h"

void render_trade_arrows(sfRenderWindow *window,
    trade_flow_t *flows, trade_barrier_t *barriers,
    gui_state_t *gui);
void render_simple_arrow(sfRenderWindow *window,
    sfVector2f start, sfVector2f end, sfColor color,
    float thickness);

#endif
