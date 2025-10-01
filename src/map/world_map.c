/*
** EPITECH PROJECT, 2025
** Trade Barrier Impact Simulator
** File description:
** World map core implementation
*/

#include "map/world_map.h"
#include "utils/utils_memory.h"
#include <string.h>
#include <stdlib.h>

static const country_def_t g_countries[] = {
    {"US", "United States", {280, 200}, {220, 130},
        {34, 139, 34, 255}},
    {"CN", "China", {1040, 200}, {160, 130},
        {220, 20, 60, 255}},
    {"DE", "Germany", {720, 170}, {80, 80},
        {255, 215, 0, 255}},
    {"JP", "Japan", {1250, 230}, {50, 100},
        {255, 69, 0, 255}},
    {"GB", "United Kingdom", {640, 140}, {60, 80},
        {255, 0, 0, 255}},
    {"FR", "France", {670, 200}, {80, 100},
        {0, 0, 255, 255}},
    {"BR", "Brazil", {480, 520}, {160, 190},
        {255, 255, 0, 255}},
    {"IN", "India", {930, 300}, {110, 130},
        {255, 165, 0, 255}},
    {"CA", "Canada", {300, 120}, {200, 90},
        {255, 0, 0, 255}},
    {"MX", "Mexico", {320, 310}, {140, 120},
        {0, 128, 0, 255}},
    {"KR", "South Korea", {1180, 250}, {50, 60},
        {0, 128, 255, 255}},
    {"IT", "Italy", {740, 240}, {60, 80},
        {0, 146, 70, 255}},
    {"ES", "Spain", {600, 260}, {80, 80},
        {255, 196, 0, 255}},
    {"AU", "Australia", {1300, 600}, {120, 100},
        {0, 0, 128, 255}},
    {"RU", "Russia", {850, 100}, {350, 120},
        {255, 255, 255, 255}},
    {"ZA", "South Africa", {780, 630}, {80, 90},
        {0, 128, 0, 255}},
    {"NZ", "New Zealand", {1420, 680}, {60, 80},
        {0, 100, 200, 255}},
    {"ID", "Indonesia", {1150, 480}, {100, 60},
        {255, 100, 100, 255}},
    {"SA", "Saudi Arabia", {840, 310}, {90, 80},
        {0, 128, 0, 255}},
    {"TR", "Turkey", {800, 240}, {70, 60},
        {255, 0, 0, 255}},
    {"TH", "Thailand", {1090, 360}, {50, 80},
        {255, 100, 150, 255}},
    {"PL", "Poland", {760, 160}, {60, 60},
        {255, 255, 255, 255}},
    {"NL", "Netherlands", {700, 160}, {40, 40},
        {255, 150, 0, 255}},
    {"BE", "Belgium", {695, 180}, {35, 35},
        {255, 200, 0, 255}},
    {"CH", "Switzerland", {710, 210}, {40, 40},
        {255, 0, 0, 255}},
    {"SE", "Sweden", {745, 120}, {50, 80},
        {0, 100, 200, 255}},
    {"NO", "Norway", {720, 100}, {50, 90},
        {255, 100, 100, 255}},
    {"AT", "Austria", {745, 205}, {45, 40},
        {255, 0, 0, 255}},
    {"AR", "Argentina", {460, 670}, {100, 140},
        {100, 200, 255, 255}},
    {"CL", "Chile", {400, 650}, {40, 160},
        {255, 100, 100, 255}},
    {"SG", "Singapore", {1100, 430},  {20, 20},
        {255, 0, 0, 255}},
    {"MY", "Malaysia", {1090, 420}, {70, 50},
        {255, 200, 0, 255}},
    {"PH", "Philippines", {1200, 360}, {60, 90},
        {0, 100, 200, 255}},
    {"VN", "Vietnam", {1070, 350}, {50, 90},
        {255, 0, 0, 255}},
    {"AE", "UAE", {860, 320}, {40, 30},
        {0, 128, 0, 255}},
    {"IL", "Israel", {810, 280}, {30, 40},
        {0, 100, 255, 255}},
    {"IE", "Ireland", {615, 155}, {40, 50},
        {0, 150, 0, 255}},
    {"DK", "Denmark", {730, 145}, {40, 35},
        {255, 0, 0, 255}},
    {"FI", "Finland", {780, 110}, {60, 80},
        {255, 255, 255, 255}},
    {"PT", "Portugal", {575, 270}, {40, 60},
        {0, 128, 0, 255}},
    {"GR", "Greece", {770, 265}, {50, 50},
        {0, 100, 200, 255}},
    {"CZ", "Czech Republic", {745, 180}, {50, 40},
        {255, 255, 255, 255}},
    {"RO", "Romania", {795, 215}, {60, 50},
        {255, 200, 0, 255}},
    {"HU", "Hungary", {765, 205}, {50, 40},
        {255, 100, 100, 255}},
    {"CO", "Colombia", {420, 450}, {70, 80},
        {255, 200, 0, 255}},
    {"PE", "Peru", {410, 560}, {70, 100},
        {255, 0, 0, 255}},
    {"PK", "Pakistan", {900, 290}, {70, 80},
        {0, 128, 0, 255}},
    {"BD", "Bangladesh", {980, 320}, {50, 50},
        {0, 128, 0, 255}},
    {"NG", "Nigeria", {700, 460}, {60, 50},
        {0, 128, 0, 255}},
    {"EG", "Egypt", {800, 310}, {60, 70},
        {255, 200, 100, 255}},
    {"KE", "Kenya", {820, 480}, {50, 60},
        {255, 0, 0, 255}},
    {"ET", "Ethiopia", {825, 455}, {50, 60},
        {0, 128, 0, 255}},
    {"MA", "Morocco", {620, 290}, {60, 60},
        {255, 0, 0, 255}},
    {"EC", "Ecuador", {390, 480}, {50, 60},
        {255, 200, 0, 255}},
    {"UA", "Ukraine", {805, 180}, {70, 50},
        {0, 100, 255, 255}},
    {"IQ", "Iraq", {850, 285}, {60, 60},
        {255, 0, 0, 255}},
};

const country_def_t *get_country_def(int index)
{
    if (index < 0 || index >= 56)
        return NULL;
    return &g_countries[index];
}

int get_country_count(void)
{
    return 56;
}

static void init_map_data(world_map_t *map)
{
    int y = 0;

    while (y < MAP_CHAR_HEIGHT) {
        memset(map->map_data[y], ' ', MAP_CHAR_WIDTH);
        map->map_data[y][MAP_CHAR_WIDTH] = '\0';
        y++;
    }
}

world_map_t *create_world_map(sfFont *font)
{
    world_map_t *map = safe_malloc(sizeof(world_map_t));

    map->regions = NULL;
    map->map_font = font;
    map->needs_update = true;
    map->char_sprites = NULL;
    init_map_data(map);
    return map;
}

void free_world_map(world_map_t *map)
{
    country_region_t *region = NULL;
    country_region_t *next = NULL;

    if (!map)
        return;
    region = map->regions;
    while (region) {
        next = region->next;
        if (region->char_positions)
            free(region->char_positions);
        free(region);
        region = next;
    }
    free(map);
}

bool load_world_map_data(world_map_t *map)
{
    if (!map)
        return false;
    init_map_data(map);
    return true;
}

void update_map_colors(world_map_t *map, country_t *countries,
    economic_impact_t *impacts)
{
    country_t *country = countries;
    int index = 0;

    if (!map || !countries)
        return;
    while (country) {
        country_region_t *region = find_country_region(map,
            country->code);
        if (region && impacts) {
            double impact = impacts[index].gdp_impact;
            if (impact > 0.05)
                region->current_color = (sfColor){50, 200, 50, 255};
            else if (impact < -0.05)
                region->current_color = (sfColor){200, 50, 50, 255};
            else
                region->current_color = (sfColor){150, 150, 150, 255};
            index++;
        }
        country = country->next;
    }
    map->needs_update = true;
}

country_region_t *find_country_region(world_map_t *map,
    const char *code)
{
    country_region_t *region = NULL;

    if (!map || !code)
        return NULL;
    region = map->regions;
    while (region) {
        if (strcmp(region->country_code, code) == 0)
            return region;
        region = region->next;
    }
    return NULL;
}

void update_country_color(country_region_t *region,
    double impact, const color_scheme_t *colors)
{
    if (!region || !colors)
        return;
    if (impact > 0.05)
        region->current_color = colors->positive_high;
    else if (impact > 0.01)
        region->current_color = colors->positive_medium;
    else if (impact < -0.05)
        region->current_color = colors->negative_high;
    else if (impact < -0.01)
        region->current_color = colors->negative_medium;
    else
        region->current_color = colors->neutral;
}
