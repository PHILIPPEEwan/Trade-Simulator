/*
** EPITECH PROJECT, 2025
** Trade Barrier Impact Simulator
** File description:
** Trade arrow animations
*/

#ifndef ANIM_ARROWS_H
    #define ANIM_ARROWS_H

    #include <SFML/Graphics.h>
    #include "animation/anim_core.h"
    #include "types.h"

struct trade_arrow_s {
    sfVector2f start_pos;
    sfVector2f end_pos;
    sfVector2f current_pos;
    sfColor color;
    float thickness;
    float progress;
    double trade_value;
    product_t *product;
    bool is_visible;
    char product_icon;
    struct trade_arrow_s *next;
};

trade_arrow_t *create_trade_arrow(trade_flow_t *flow);
void update_trade_arrows(animation_manager_t *manager,
    float delta_time);
void spawn_trade_flow_animation(animation_manager_t *manager,
    trade_flow_t *flow);
char get_product_icon(product_t *product);

#endif
