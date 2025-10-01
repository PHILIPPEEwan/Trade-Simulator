/*
** EPITECH PROJECT, 2025
** Trade Barrier Impact Simulator
** File description:
** Trade flow arrow rendering with animated boxes
*/

#include "map/map_arrows.h"
#include "map/map_coords.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct trade_box_s {
    sfVector2f start_pos;
    sfVector2f end_pos;
    sfVector2f current_pos;
    float progress;
    sfColor color;
    char icon[8];
    double value;
    struct trade_box_s *next;
} trade_box_t;

static trade_box_t *g_boxes = NULL;
static float g_spawn_timer = 0.0f;

static void draw_arrow_line(sfRenderWindow *window,
    sfVector2f start, sfVector2f end, sfColor color)
{
    sfVertex line[2];

    line[0].position = start;
    line[0].color = color;
    line[1].position = end;
    line[1].color = color;
    sfRenderWindow_drawPrimitives(window, line, 2, sfLines, NULL);
}

static sfColor get_product_color(const char *icon)
{
    if (icon[0] == 'C' || icon[0] == 'P' || icon[0] == 'H' ||
        icon[0] == 'E')
        return (sfColor){100, 150, 255, 220};
    if (icon[0] == 'A')
        return (sfColor){255, 200, 100, 220};
    if (icon[0] == 'O')
        return (sfColor){80, 80, 80, 220};
    if (icon[0] == 'W' || icon[0] == 'F' || icon[0] == 'M')
        return (sfColor){100, 200, 100, 220};
    if (icon[0] == 'S')
        return (sfColor){150, 150, 150, 220};
    if (icon[0] == 'T')
        return (sfColor){200, 100, 200, 220};
    if (icon[0] == '+')
        return (sfColor){255, 100, 100, 220};
    return (sfColor){150, 150, 150, 220};
}

static void draw_box(sfRenderWindow *window, trade_box_t *box,
    sfFont *font)
{
    sfRectangleShape *rect = sfRectangleShape_create();
    sfVector2f size = {20, 20};
    sfVector2f pos = {box->current_pos.x - 10,
        box->current_pos.y - 10};
    sfColor bg_color = get_product_color(box->icon);

    sfRectangleShape_setSize(rect, size);
    sfRectangleShape_setPosition(rect, pos);
    sfRectangleShape_setFillColor(rect, bg_color);
    sfRectangleShape_setOutlineColor(rect,
        (sfColor){255, 255, 255, 255});
    sfRectangleShape_setOutlineThickness(rect, 1);
    sfRenderWindow_drawRectangleShape(window, rect, NULL);
    sfRectangleShape_destroy(rect);
    if (font) {
        sfText *text = sfText_create();
        sfText_setFont(text, font);
        sfText_setString(text, box->icon);
        sfText_setCharacterSize(text, 14);
        sfText_setColor(text, (sfColor){255, 255, 255, 255});
        sfText_setPosition(text, (sfVector2f){pos.x + 5, pos.y + 1});
        sfRenderWindow_drawText(window, text, NULL);
        sfText_destroy(text);
    }
}

static const char *get_product_icon(const char *hs_code,
    const char *category)
{
    if (!hs_code)
        return "?";
    if (strncmp(hs_code, "8541", 4) == 0)
        return "C";
    if (strncmp(hs_code, "8703", 4) == 0)
        return "A";
    if (strncmp(hs_code, "5201", 4) == 0)
        return "T";
    if (strncmp(hs_code, "1001", 4) == 0)
        return "W";
    if (strncmp(hs_code, "2709", 4) == 0 ||
        strncmp(hs_code, "2710", 4) == 0)
        return "O";
    if (strncmp(hs_code, "0201", 4) == 0)
        return "M";
    if (strncmp(hs_code, "0803", 4) == 0)
        return "F";
    if (strncmp(hs_code, "8471", 4) == 0)
        return "P";
    if (strncmp(hs_code, "7208", 4) == 0)
        return "S";
    if (strncmp(hs_code, "8517", 4) == 0)
        return "H";
    if (strncmp(hs_code, "9018", 4) == 0)
        return "+";
    if (category && strstr(category, "Electronics"))
        return "E";
    if (category && strstr(category, "Automotive"))
        return "A";
    if (category && strstr(category, "Food"))
        return "F";
    if (category && strstr(category, "Energy"))
        return "O";
    if (category && strstr(category, "Metals"))
        return "S";
    if (category && strstr(category, "Textiles"))
        return "T";
    return "?";
}

static void spawn_box(trade_flow_t *flow, sfColor color)
{
    trade_box_t *box = malloc(sizeof(trade_box_t));
    const char *icon = NULL;

    if (!box || !flow)
        return;
    box->start_pos = get_country_center(flow->exporter->code);
    box->end_pos = get_country_center(flow->importer->code);
    box->current_pos = box->start_pos;
    box->progress = 0.0f;
    box->color = color;
    box->value = flow->value;
    icon = get_product_icon(
        flow->product ? flow->product->hs_code : NULL,
        flow->product ? flow->product->category : NULL);
    snprintf(box->icon, sizeof(box->icon), "%s", icon);
    box->next = g_boxes;
    g_boxes = box;
}

static void update_boxes(float delta_time)
{
    trade_box_t *box = g_boxes;
    trade_box_t *prev = NULL;

    while (box) {
        box->progress += delta_time * 0.3f;
        if (box->progress >= 1.0f) {
            trade_box_t *to_remove = box;
            if (prev)
                prev->next = box->next;
            else
                g_boxes = box->next;
            box = box->next;
            free(to_remove);
            continue;
        }
        box->current_pos.x = box->start_pos.x +
            (box->end_pos.x - box->start_pos.x) * box->progress;
        box->current_pos.y = box->start_pos.y +
            (box->end_pos.y - box->start_pos.y) * box->progress;
        prev = box;
        box = box->next;
    }
}

void render_simple_arrow(sfRenderWindow *window,
    sfVector2f start, sfVector2f end, sfColor color,
    float thickness)
{
    (void)thickness;
    if (!window)
        return;
    draw_arrow_line(window, start, end, color);
}

static bool is_eu_country(const char *code)
{
    const char *eu_codes[] = {
        "DEU", "FRA", "ITA", "ESP", "NLD", "BEL",
        "AUT", "POL", "PRT", "GRC", "CZE", "HUN",
        "SWE", "DNK", "FIN", "IRL", "LUX", NULL
    };
    int i = 0;

    if (!code)
        return false;
    while (eu_codes[i]) {
        if (strcmp(code, eu_codes[i]) == 0)
            return true;
        i++;
    }
    return false;
}

static bool is_blocked(trade_flow_t *flow,
    trade_barrier_t *barriers)
{
    trade_barrier_t *barrier = barriers;

    while (barrier) {
        if (barrier->is_active) {
            if (barrier->source_country == NULL &&
                barrier->target_country == flow->importer) {
                if (is_eu_country(barrier->target_country->code) &&
                    is_eu_country(flow->exporter->code))
                    goto next_barrier;
                return true;
            }
            if (barrier->target_country == NULL &&
                barrier->source_country == flow->exporter)
                return true;
            if ((barrier->source_country == flow->exporter &&
                barrier->target_country == flow->importer) ||
                (barrier->source_country == flow->importer &&
                barrier->target_country == flow->exporter))
                return true;
        }
next_barrier:
        barrier = barrier->next;
    }
    return false;
}

static sfColor get_arrow_color(trade_flow_t *flow,
    trade_barrier_t *barriers)
{
    if (is_blocked(flow, barriers))
        return (sfColor){255, 80, 80, 180};
    return (sfColor){100, 200, 100, 180};
}

static int get_spawn_count(double trade_value)
{
    if (trade_value > 10000000000.0)
        return 5;
    if (trade_value > 5000000000.0)
        return 3;
    if (trade_value > 1000000000.0)
        return 2;
    return 1;
}

void render_trade_arrows(sfRenderWindow *window,
    trade_flow_t *flows, trade_barrier_t *barriers,
    gui_state_t *gui)
{
    trade_flow_t *flow = flows;
    int count = 0;
    trade_box_t *box = NULL;
    int spawn_count = 0;
    int i = 0;

    if (!window || !flows || !gui)
        return;
    if (!gui->show_trade_flows)
        return;
    g_spawn_timer += 0.016f;
    if (g_spawn_timer >= 1.2f) {
        g_spawn_timer = 0.0f;
        flow = flows;
        while (flow) {
            if (flow->exporter && flow->importer) {
                sfColor color = get_arrow_color(flow, barriers);
                spawn_count = get_spawn_count(flow->value);
                i = 0;
                while (i < spawn_count) {
                    spawn_box(flow, color);
                    i++;
                }
            }
            flow = flow->next;
        }
    }
    update_boxes(0.016f * gui->time_multiplier);
    flow = flows;
    count = 0;
    while (flow) {
        if (flow->exporter && flow->importer) {
            sfVector2f start = get_country_center(
                flow->exporter->code);
            sfVector2f end = get_country_center(
                flow->importer->code);
            sfColor color = get_arrow_color(flow, barriers);
            render_simple_arrow(window, start, end, color, 2.0f);
        }
        flow = flow->next;
        count++;
    }
    box = g_boxes;
    while (box) {
        draw_box(window, box, gui->font);
        box = box->next;
    }
}
