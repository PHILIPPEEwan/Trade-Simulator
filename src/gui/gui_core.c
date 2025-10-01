/*
** EPITECH PROJECT, 2025
** Trade Barrier Impact Simulator
** File description:
** GUI core engine implementation
*/

#include <stdio.h>
#include "gui/gui_core.h"

static const color_scheme_t g_default_colors = {
    .positive_high = {50, 200, 50, 255},
    .positive_medium = {100, 255, 100, 255},
    .neutral = {150, 150, 150, 255},
    .negative_medium = {255, 100, 100, 255},
    .negative_high = {200, 50, 50, 255},
    .trade_flow = {70, 130, 180, 255},
    .background = {240, 248, 255, 255},
    .text = {25, 25, 25, 255}
};

static sfRenderWindow *create_window(void)
{
    sfVideoMode mode = {SCREEN_WIDTH, SCREEN_HEIGHT, 32};
    sfRenderWindow *window = NULL;

    window = sfRenderWindow_create(mode,
        "Trade Barrier Impact Simulator",
        sfResize | sfClose, NULL);
    if (!window)
        return NULL;
    sfRenderWindow_setFramerateLimit(window, TARGET_FPS);
    sfRenderWindow_setVerticalSyncEnabled(window, sfTrue);
    return window;
}

static sfFont *load_system_font(void)
{
    const char *fonts[] = {
        "/usr/share/fonts/liberation-mono-fonts/LiberationMono-Regular.ttf",
        "/usr/share/fonts/dejavu-sans-fonts/DejaVuSans.ttf",
        "/usr/share/fonts/liberation-sans-fonts/LiberationSans-Regular.ttf",
        NULL
    };
    sfFont *font = NULL;
    int i = 0;

    while (fonts[i] != NULL) {
        font = sfFont_createFromFile(fonts[i]);
        if (font) {
            printf("Loaded font: %s\n", fonts[i]);
            return font;
        }
        i++;
    }
    printf("Failed to load any system font\n");
    return NULL;
}

static void init_gui_state(gui_state_t *gui)
{
    gui->colors = g_default_colors;
    gui->is_running = true;
    gui->is_paused = false;
    gui->simulation_time = 0.0f;
    gui->time_multiplier = 1.0f;
    gui->current_year = 0;
    gui->show_trade_flows = true;
    gui->show_impacts = true;
    gui->show_country_names = true;
    gui->mouse_pos.x = 0;
    gui->mouse_pos.y = 0;
    gui->hovered_country[0] = '\0';
    gui->show_tooltips = true;
    gui->show_particles = true;
}

bool gui_initialize(gui_state_t *gui)
{
    if (!gui)
        return false;
    gui->window = create_window();
    if (!gui->window)
        return false;
    gui->font = load_system_font();
    if (!gui->font)
        return false;
    gui->clock = sfClock_create();
    if (!gui->clock)
        return false;
    init_gui_state(gui);
    return true;
}

void gui_cleanup(gui_state_t *gui)
{
    if (!gui)
        return;
    if (gui->clock)
        sfClock_destroy(gui->clock);
    if (gui->font)
        sfFont_destroy(gui->font);
    if (gui->window)
        sfRenderWindow_destroy(gui->window);
}

sfColor gui_get_impact_color(const color_scheme_t *colors,
    double value)
{
    if (!colors)
        return (sfColor){255, 255, 255, 255};
    if (value > 0.05)
        return colors->positive_high;
    if (value > 0.01)
        return colors->positive_medium;
    if (value < -0.05)
        return colors->negative_high;
    if (value < -0.01)
        return colors->negative_medium;
    return colors->neutral;
}

void gui_update_time(gui_state_t *gui, float delta)
{
    float increment = 0.0f;

    if (!gui)
        return;
    increment = delta * gui->time_multiplier * ANIMATION_SPEED;
    gui->simulation_time += increment;
    gui->current_year = (int)gui->simulation_time;
}
