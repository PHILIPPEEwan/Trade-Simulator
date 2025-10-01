/*
** EPITECH PROJECT, 2025
** Trade Barrier Impact Simulator
** File description:
** World map rendering implementation
*/

#include "map/map_render.h"

static sfRectangleShape *create_ocean_shape(void)
{
    sfRectangleShape *ocean = sfRectangleShape_create();
    sfVector2f size = {MAP_WIDTH, MAP_HEIGHT};
    sfVector2f pos = {MAP_OFFSET_X, MAP_OFFSET_Y};

    sfRectangleShape_setSize(ocean, size);
    sfRectangleShape_setPosition(ocean, pos);
    return ocean;
}

void render_ocean_background(sfRenderWindow *window)
{
    sfRectangleShape *ocean = NULL;
    sfColor fill = {25, 100, 150, 255};
    sfColor border = {20, 80, 120, 255};

    if (!window)
        return;
    ocean = create_ocean_shape();
    sfRectangleShape_setFillColor(ocean, fill);
    sfRectangleShape_setOutlineColor(ocean, border);
    sfRectangleShape_setOutlineThickness(ocean, 2);
    sfRenderWindow_drawRectangleShape(window, ocean, NULL);
    sfRectangleShape_destroy(ocean);
}

static void render_country_rect(sfRenderWindow *window,
    const country_def_t *def)
{
    sfRectangleShape *rect = sfRectangleShape_create();
    sfColor border = {0, 0, 0, 255};

    sfRectangleShape_setSize(rect, def->size);
    sfRectangleShape_setPosition(rect, def->position);
    sfRectangleShape_setFillColor(rect, def->color);
    sfRectangleShape_setOutlineThickness(rect, 1.0f);
    sfRectangleShape_setOutlineColor(rect, border);
    sfRenderWindow_drawRectangleShape(window, rect, NULL);
    sfRectangleShape_destroy(rect);
}

static void render_all_countries(sfRenderWindow *window)
{
    int i = 0;
    int count = get_country_count();

    while (i < count) {
        render_country_rect(window, get_country_def(i));
        i++;
    }
}

void render_world_map(const render_params_t *params)
{
    if (!params || !params->window || !params->map)
        return;
    render_ocean_background(params->window);
    render_all_countries(params->window);
}

static sfText *create_label(const char *text, sfFont *font)
{
    sfText *label = sfText_create();
    sfColor white = {255, 255, 255, 255};

    sfText_setFont(label, font);
    sfText_setString(label, text);
    sfText_setCharacterSize(label, 11);
    sfText_setColor(label, white);
    return label;
}

static sfVector2f calc_label_pos(const country_def_t *def)
{
    sfVector2f pos;

    pos.x = def->position.x + def->size.x / 2 - 10;
    pos.y = def->position.y + def->size.y / 2 - 6;
    return pos;
}

static void render_single_label(sfRenderWindow *window,
    const country_def_t *def, sfFont *font)
{
    sfText *label = create_label(def->code, font);
    sfVector2f pos = calc_label_pos(def);
    sfRectangleShape *bg = sfRectangleShape_create();
    sfVector2f bg_size = {24, 14};
    sfVector2f bg_pos = {pos.x - 2, pos.y};
    sfColor bg_color = {0, 0, 0, 180};

    sfRectangleShape_setSize(bg, bg_size);
    sfRectangleShape_setPosition(bg, bg_pos);
    sfRectangleShape_setFillColor(bg, bg_color);
    sfRenderWindow_drawRectangleShape(window, bg, NULL);
    sfRectangleShape_destroy(bg);
    sfText_setPosition(label, pos);
    sfRenderWindow_drawText(window, label, NULL);
    sfText_destroy(label);
}

void render_country_labels(const render_params_t *params)
{
    int i = 0;
    int count = get_country_count();

    if (!params || !params->gui)
        return;
    if (!params->gui->show_country_names)
        return;
    while (i < count) {
        render_single_label(params->window,
            get_country_def(i), params->gui->font);
        i++;
    }
}
