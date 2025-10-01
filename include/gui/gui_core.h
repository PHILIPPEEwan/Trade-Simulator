/*
** EPITECH PROJECT, 2025
** Trade Barrier Impact Simulator
** File description:
** GUI core engine management
*/

#ifndef GUI_CORE_H
    #define GUI_CORE_H

    #include <SFML/Graphics.h>
    #include <stdbool.h>

    #define SCREEN_WIDTH 1920
    #define SCREEN_HEIGHT 1080
    #define MAP_WIDTH 1600
    #define MAP_HEIGHT 1000
    #define UI_PANEL_WIDTH 300
    #define TARGET_FPS 60
    #define ANIMATION_SPEED 1.0f

typedef struct color_scheme_s {
    sfColor positive_high;
    sfColor positive_medium;
    sfColor neutral;
    sfColor negative_medium;
    sfColor negative_high;
    sfColor trade_flow;
    sfColor background;
    sfColor text;
} color_scheme_t;

typedef struct gui_state_s {
    sfRenderWindow *window;
    sfClock *clock;
    sfFont *font;
    color_scheme_t colors;
    bool is_running;
    bool is_paused;
    float simulation_time;
    float time_multiplier;
    int current_year;
    bool show_trade_flows;
    bool show_impacts;
    bool show_country_names;
    int current_scenario_index;
    void *app_state;
    sfVector2i mouse_pos;
    char hovered_country[8];
    bool show_tooltips;
    bool show_particles;
} gui_state_t;

bool gui_initialize(gui_state_t *gui);
void gui_cleanup(gui_state_t *gui);
sfColor gui_get_impact_color(const color_scheme_t *colors,
    double value);
void gui_update_time(gui_state_t *gui, float delta);

#endif
