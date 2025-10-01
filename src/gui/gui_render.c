/*
** EPITECH PROJECT, 2025
** Trade Barrier Impact Simulator
** File description:
** GUI rendering implementation
*/

#include "gui/gui_render.h"
#include "gui/gui_panels.h"
#include <stdio.h>

void gui_clear_screen(gui_state_t *gui)
{
    if (!gui || !gui->window)
        return;
    sfRenderWindow_clear(gui->window, gui->colors.background);
}

void render_status_bar(gui_state_t *gui)
{
    sfRectangleShape *bar = NULL;
    sfVector2f size = {SCREEN_WIDTH, 30};
    sfVector2f pos = {0, SCREEN_HEIGHT - 30};
    sfColor bg = {30, 30, 30, 200};

    if (!gui || !gui->window)
        return;
    bar = sfRectangleShape_create();
    sfRectangleShape_setSize(bar, size);
    sfRectangleShape_setPosition(bar, pos);
    sfRectangleShape_setFillColor(bar, bg);
    sfRenderWindow_drawRectangleShape(gui->window, bar, NULL);
    sfRectangleShape_destroy(bar);
}

static void render_status_text(gui_state_t *gui)
{
    const char *scenario_names[] = {
        "Free Trade", "US-China Trade War", "EU Protectionism"
    };
    char text[256];
    sfText *status = NULL;
    sfVector2f pos = {10, SCREEN_HEIGHT - 25};
    sfColor color = gui->is_paused ?
        (sfColor){255, 200, 100, 255} : sfWhite;
    int scenario_idx = gui->current_scenario_index % 3;

    snprintf(text, sizeof(text),
        "Year %d | Speed: %.1fx | %s | Scenario: %s | Press S to switch",
        gui->current_year, gui->time_multiplier,
        gui->is_paused ? "[PAUSED]" : "[RUNNING]",
        scenario_names[scenario_idx]);
    status = sfText_create();
    sfText_setFont(status, gui->font);
    sfText_setString(status, text);
    sfText_setCharacterSize(status, 13);
    sfText_setColor(status, color);
    sfText_setPosition(status, pos);
    sfRenderWindow_drawText(gui->window, status, NULL);
    sfText_destroy(status);
}

void render_status_text_public(gui_state_t *gui)
{
    render_status_text(gui);
}

void gui_render_frame(const render_context_t *ctx)
{
    if (!ctx || !ctx->gui)
        return;
    gui_clear_screen(ctx->gui);
    render_ui_panel(ctx->gui);
    render_status_bar(ctx->gui);
    render_status_text(ctx->gui);
    sfRenderWindow_display(ctx->gui->window);
}
