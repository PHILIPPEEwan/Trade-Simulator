/*
** EPITECH PROJECT, 2025
** Trade Barrier Impact Simulator
** File description:
** Animation rendering implementation
*/

#include "animation/anim_render.h"
#include "animation/anim_arrows.h"
#include <math.h>

float ease_in_out(float t)
{
    return t < 0.5f ? 2 * t * t : -1 + (4 - 2 * t) * t;
}

sfVector2f interpolate_position(sfVector2f start, sfVector2f end,
    float progress)
{
    return (sfVector2f){
        start.x + (end.x - start.x) * progress,
        start.y + (end.y - start.y) * progress
    };
}

static void render_arrow_glow(sfRenderWindow *window,
    trade_arrow_t *arrow)
{
    sfCircleShape *glow = sfCircleShape_create();
    float radius = arrow->thickness + 2;
    sfColor glow_color = arrow->color;

    glow_color.a = 80;
    sfCircleShape_setRadius(glow, radius);
    sfCircleShape_setFillColor(glow, glow_color);
    sfCircleShape_setPosition(glow, (sfVector2f){
        arrow->current_pos.x - radius,
        arrow->current_pos.y - radius});
    sfRenderWindow_drawCircleShape(window, glow, NULL);
    sfCircleShape_destroy(glow);
}

static void render_arrow_head(sfRenderWindow *window,
    trade_arrow_t *arrow)
{
    sfCircleShape *head = sfCircleShape_create();
    float radius = arrow->thickness + 1;
    sfColor color = arrow->color;

    color.a = 255;
    sfCircleShape_setRadius(head, radius);
    sfCircleShape_setFillColor(head, color);
    sfCircleShape_setPosition(head, (sfVector2f){
        arrow->current_pos.x - radius,
        arrow->current_pos.y - radius});
    sfRenderWindow_drawCircleShape(window, head, NULL);
    sfCircleShape_destroy(head);
}

static void render_single_arrow(sfRenderWindow *window,
    trade_arrow_t *arrow)
{
    if (!arrow->is_visible || arrow->progress <= 0.0f)
        return;
    if (arrow->trade_value > 5e9)
        render_arrow_glow(window, arrow);
    render_arrow_head(window, arrow);
}

void render_animated_arrows(sfRenderWindow *window,
    animation_manager_t *manager)
{
    trade_arrow_t *arrow = NULL;

    if (!window || !manager)
        return;
    arrow = manager->trade_arrows;
    while (arrow) {
        render_single_arrow(window, arrow);
        arrow = arrow->next;
    }
}

static void render_timeline_bg(sfRenderWindow *window)
{
    sfRectangleShape *bg = sfRectangleShape_create();
    sfVector2f size = {SCREEN_WIDTH - UI_PANEL_WIDTH - 20, 40};
    sfVector2f pos = {10, SCREEN_HEIGHT - 80};
    sfColor fill = {50, 50, 50, 150};
    sfColor border = {100, 100, 100, 255};

    sfRectangleShape_setSize(bg, size);
    sfRectangleShape_setPosition(bg, pos);
    sfRectangleShape_setFillColor(bg, fill);
    sfRectangleShape_setOutlineColor(bg, border);
    sfRectangleShape_setOutlineThickness(bg, 1);
    sfRenderWindow_drawRectangleShape(window, bg, NULL);
    sfRectangleShape_destroy(bg);
}

void render_animation_timeline(sfRenderWindow *window,
    animation_manager_t *manager, gui_state_t *gui)
{
    (void)manager;
    (void)gui;
    if (!window)
        return;
    render_timeline_bg(window);
}
