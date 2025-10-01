/*
** EPITECH PROJECT, 2025
** Trade Barrier Impact Simulator
** File description:
** Trade arrow animations implementation
*/

#include "animation/anim_arrows.h"
#include "map/map_coords.h"
#include "utils/utils_memory.h"
#include <string.h>
#include <math.h>

char get_product_icon(product_t *product)
{
    if (!product || !product->category[0])
        return 'o';
    if (strstr(product->category, "Electronics"))
        return '@';
    if (strstr(product->category, "Automotive"))
        return '&';
    if (strstr(product->category, "Textiles"))
        return '#';
    if (strstr(product->category, "Food"))
        return '*';
    if (strstr(product->category, "Energy"))
        return '%';
    return 'o';
}

static sfColor get_arrow_color(product_t *product)
{
    char icon = get_product_icon(product);

    if (icon == '@')
        return (sfColor){255, 165, 0, 255};
    if (icon == '&')
        return (sfColor){128, 128, 128, 255};
    if (icon == '#')
        return (sfColor){255, 20, 147, 255};
    if (icon == '*')
        return (sfColor){34, 139, 34, 255};
    if (icon == '%')
        return (sfColor){255, 0, 0, 255};
    return (sfColor){70, 130, 180, 255};
}

trade_arrow_t *create_trade_arrow(trade_flow_t *flow)
{
    trade_arrow_t *arrow = NULL;
    double thickness_scale = 0;

    if (!flow || !flow->exporter || !flow->importer)
        return NULL;
    arrow = safe_malloc(sizeof(trade_arrow_t));
    arrow->start_pos = get_country_center(flow->exporter->code);
    arrow->end_pos = get_country_center(flow->importer->code);
    arrow->current_pos = arrow->start_pos;
    arrow->trade_value = flow->value;
    thickness_scale = log(flow->value / 1e9 + 1) / 3.0;
    arrow->thickness = fmax(1.0f, fmin(5.0f, thickness_scale));
    arrow->color = get_arrow_color(flow->product);
    arrow->progress = 0.0f;
    arrow->product = flow->product;
    arrow->is_visible = false;
    arrow->product_icon = get_product_icon(flow->product);
    arrow->next = NULL;
    return arrow;
}

static sfVector2f lerp_pos(sfVector2f start, sfVector2f end,
    float t)
{
    return (sfVector2f){
        start.x + (end.x - start.x) * t,
        start.y + (end.y - start.y) * t
    };
}

void update_trade_arrows(animation_manager_t *manager,
    float delta_time)
{
    trade_arrow_t *arrow = NULL;

    if (!manager)
        return;
    arrow = manager->trade_arrows;
    while (arrow) {
        if (arrow->is_visible) {
            arrow->progress += delta_time * 2.0f /
                TRADE_FLOW_DURATION;
            if (arrow->progress >= 1.0f) {
                arrow->progress = 0.0f;
                arrow->current_pos = arrow->start_pos;
            } else {
                arrow->current_pos = lerp_pos(arrow->start_pos,
                    arrow->end_pos, arrow->progress);
            }
        }
        arrow = arrow->next;
    }
}

void spawn_trade_flow_animation(animation_manager_t *manager,
    trade_flow_t *flow)
{
    trade_arrow_t *arrow = NULL;

    if (!manager || !flow)
        return;
    arrow = create_trade_arrow(flow);
    if (arrow) {
        arrow->is_visible = true;
        arrow->next = manager->trade_arrows;
        manager->trade_arrows = arrow;
    }
}
