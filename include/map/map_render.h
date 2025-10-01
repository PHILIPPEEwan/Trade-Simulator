/*
** EPITECH PROJECT, 2025
** Trade Barrier Impact Simulator
** File description:
** World map rendering functions
*/

#ifndef MAP_RENDER_H
    #define MAP_RENDER_H

    #include <SFML/Graphics.h>
    #include "map/world_map.h"
    #include "gui/gui_core.h"

typedef struct render_params_s {
    sfRenderWindow *window;
    world_map_t *map;
    gui_state_t *gui;
} render_params_t;

void render_world_map(const render_params_t *params);
void render_country_labels(const render_params_t *params);
void render_ocean_background(sfRenderWindow *window);

#endif
