/*
** EPITECH PROJECT, 2025
** Trade Barrier Impact Simulator
** File description:
** Map region management
*/

#ifndef MAP_REGIONS_H
    #define MAP_REGIONS_H

    #include "map/world_map.h"
    #include "types.h"

typedef struct region_params_s {
    const char *code;
    int *positions;
    int count;
    sfVector2f label_pos;
} region_params_t;

void add_country_region(world_map_t *map,
    const region_params_t *params);
void highlight_country(world_map_t *map, const char *code);
void clear_highlights(world_map_t *map);
country_t *get_country_at_position(world_map_t *map,
    sfVector2i map_pos, country_t *countries);

#endif
