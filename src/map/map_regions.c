/*
** EPITECH PROJECT, 2025
** Trade Barrier Impact Simulator
** File description:
** Map region management implementation
*/

#include "map/map_regions.h"
#include "utils/utils_memory.h"
#include <string.h>

void add_country_region(world_map_t *map,
    const region_params_t *params)
{
    country_region_t *region = NULL;

    if (!map || !params)
        return;
    region = safe_malloc(sizeof(country_region_t));
    safe_strncpy(region->country_code, params->code,
        MAX_CODE_LEN);
    region->char_positions = params->positions;
    region->position_count = params->count;
    region->base_color = (sfColor){100, 100, 100, 255};
    region->current_color = region->base_color;
    region->label_pos = params->label_pos;
    region->next = map->regions;
    map->regions = region;
}

void highlight_country(world_map_t *map, const char *code)
{
    country_region_t *region = find_country_region(map, code);
    sfColor highlight;

    if (!region)
        return;
    highlight = region->current_color;
    highlight.r = (highlight.r + 255) / 2;
    highlight.g = (highlight.g + 255) / 2;
    highlight.b = (highlight.b + 255) / 2;
    region->current_color = highlight;
    map->needs_update = true;
}

void clear_highlights(world_map_t *map)
{
    country_region_t *region = NULL;

    if (!map)
        return;
    region = map->regions;
    while (region) {
        region->current_color = region->base_color;
        region = region->next;
    }
    map->needs_update = true;
}

static bool is_in_country_rect(sfVector2i pos,
    const country_def_t *def)
{
    if (pos.x < def->position.x)
        return false;
    if (pos.x > def->position.x + def->size.x)
        return false;
    if (pos.y < def->position.y)
        return false;
    if (pos.y > def->position.y + def->size.y)
        return false;
    return true;
}

country_t *get_country_at_position(world_map_t *map,
    sfVector2i pos, country_t *countries)
{
    int i = 0;
    int count = get_country_count();

    (void)map;
    while (i < count) {
        const country_def_t *def = get_country_def(i);
        if (is_in_country_rect(pos, def)) {
            country_t *c = countries;
            while (c) {
                if (strcmp(c->code, def->code) == 0)
                    return c;
                c = c->next;
            }
        }
        i++;
    }
    return NULL;
}
