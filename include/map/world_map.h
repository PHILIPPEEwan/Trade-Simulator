/*
** EPITECH PROJECT, 2025
** Trade Barrier Impact Simulator
** File description:
** World map core structures and functions
*/

#ifndef WORLD_MAP_H
    #define WORLD_MAP_H

    #include <SFML/Graphics.h>
    #include "types.h"
    #include "gui/gui_core.h"

    #define MAP_CHAR_WIDTH 200
    #define MAP_CHAR_HEIGHT 120
    #define CHAR_SIZE 8
    #define MAP_OFFSET_X 160
    #define MAP_OFFSET_Y 40

typedef struct country_region_s {
    char country_code[MAX_CODE_LEN];
    int *char_positions;
    int position_count;
    sfColor base_color;
    sfColor current_color;
    sfVector2f label_pos;
    struct country_region_s *next;
} country_region_t;

typedef struct world_map_s {
    char map_data[MAP_CHAR_HEIGHT][MAP_CHAR_WIDTH + 1];
    country_region_t *regions;
    sfText ***char_sprites;
    sfFont *map_font;
    bool needs_update;
} world_map_t;

typedef struct country_def_s {
    const char *code;
    const char *name;
    sfVector2f position;
    sfVector2f size;
    sfColor color;
} country_def_t;

world_map_t *create_world_map(sfFont *font);
void free_world_map(world_map_t *map);
bool load_world_map_data(world_map_t *map);
void update_map_colors(world_map_t *map, country_t *countries,
    economic_impact_t *impacts);
country_region_t *find_country_region(world_map_t *map,
    const char *code);
void update_country_color(country_region_t *region,
    double impact, const color_scheme_t *colors);
const country_def_t *get_country_def(int index);
int get_country_count(void);

#endif
