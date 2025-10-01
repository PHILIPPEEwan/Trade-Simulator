/*
** EPITECH PROJECT, 2025
** Trade Barrier Impact Simulator
** File description:
** GUI panel rendering implementation
*/

#include "gui/gui_panels.h"
#include <stdio.h>

static sfRectangleShape *create_panel_background(void)
{
    sfRectangleShape *panel = sfRectangleShape_create();
    sfVector2f size = {UI_PANEL_WIDTH, SCREEN_HEIGHT};
    sfVector2f pos = {SCREEN_WIDTH - UI_PANEL_WIDTH, 0};
    sfColor bg = {50, 50, 50, 200};
    sfColor border = {100, 100, 100, 255};

    sfRectangleShape_setSize(panel, size);
    sfRectangleShape_setPosition(panel, pos);
    sfRectangleShape_setFillColor(panel, bg);
    sfRectangleShape_setOutlineColor(panel, border);
    sfRectangleShape_setOutlineThickness(panel, 1);
    return panel;
}

static void render_panel_title(gui_state_t *gui)
{
    sfText *title = sfText_create();
    sfVector2f pos = {SCREEN_WIDTH - UI_PANEL_WIDTH + 10, 10};

    sfText_setFont(title, gui->font);
    sfText_setString(title, "Control Panel");
    sfText_setCharacterSize(title, 16);
    sfText_setColor(title, sfWhite);
    sfText_setPosition(title, pos);
    sfRenderWindow_drawText(gui->window, title, NULL);
    sfText_destroy(title);
}

static void render_year_display(gui_state_t *gui)
{
    char text[64];
    sfText *label = sfText_create();
    sfVector2f pos = {SCREEN_WIDTH - UI_PANEL_WIDTH + 10, 40};

    snprintf(text, sizeof(text), "Year: %d", gui->current_year);
    sfText_setFont(label, gui->font);
    sfText_setString(label, text);
    sfText_setCharacterSize(label, 14);
    sfText_setColor(label, sfWhite);
    sfText_setPosition(label, pos);
    sfRenderWindow_drawText(gui->window, label, NULL);
    sfText_destroy(label);
}

static void render_speed_display(gui_state_t *gui)
{
    char text[64];
    sfText *label = sfText_create();
    sfVector2f pos = {SCREEN_WIDTH - UI_PANEL_WIDTH + 10, 60};

    snprintf(text, sizeof(text), "Speed: %.1fx",
        gui->time_multiplier);
    sfText_setFont(label, gui->font);
    sfText_setString(label, text);
    sfText_setCharacterSize(label, 14);
    sfText_setColor(label, sfWhite);
    sfText_setPosition(label, pos);
    sfRenderWindow_drawText(gui->window, label, NULL);
    sfText_destroy(label);
}

static void render_scenario_info(gui_state_t *gui)
{
    const char *scenario_names[] = {
        "Free Trade Baseline",
        "US-China Trade War",
        "EU Protectionism"
    };
    const double avg_tariffs[] = {0.0, 33.3, 18.0};
    const double trade_impacts[] = {0.0, -24.8, -15.7};
    const double gdp_impacts[] = {0.0, -1.2, -0.8};
    const int active_barriers[] = {0, 3, 6};
    char info[6][128];
    int base_y = 90;
    int i = 0;
    int scenario_idx = gui->current_scenario_index % 3;

    snprintf(info[0], 128, "Scenario: %s", scenario_names[scenario_idx]);
    snprintf(info[1], 128, "Active Barriers: %d", active_barriers[scenario_idx]);
    snprintf(info[2], 128, "Avg Tariff: %.1f%%", avg_tariffs[scenario_idx]);
    snprintf(info[3], 128, "Trade Impact: %.1f%%",
        trade_impacts[scenario_idx]);
    snprintf(info[4], 128, "GDP Impact: %.1f%%", gdp_impacts[scenario_idx]);
    snprintf(info[5], 128, "Welfare: %s",
        scenario_idx == 0 ? "Neutral" :
        (scenario_idx == 1 ? "High Loss" : "Moderate Loss"));
    while (i < 6) {
        sfText *text = sfText_create();
        sfVector2f pos = {SCREEN_WIDTH - UI_PANEL_WIDTH + 10,
            base_y + i * 16};
        sfColor color = (sfColor){200, 200, 255, 255};
        if ((i == 3 || i == 4) && (trade_impacts[scenario_idx] < 0 ||
            gdp_impacts[scenario_idx] < 0))
            color = (sfColor){255, 150, 150, 255};
        else if (i == 5 && scenario_idx > 0)
            color = (sfColor){255, 180, 100, 255};
        sfText_setFont(text, gui->font);
        sfText_setString(text, info[i]);
        sfText_setCharacterSize(text, 10);
        sfText_setColor(text, color);
        sfText_setPosition(text, pos);
        sfRenderWindow_drawText(gui->window, text, NULL);
        sfText_destroy(text);
        i++;
    }
}

static void render_product_legend(gui_state_t *gui)
{
    const char *legend[] = {
        "Products:",
        "C-Chips  A-Auto",
        "O-Oil    W-Wheat",
        "P-PC     H-Phone",
        "S-Steel  T-Textile",
        "M-Meat   F-Fruit"
    };
    int base_y = 185;
    int i = 0;

    while (i < 6) {
        sfText *text = sfText_create();
        sfVector2f pos = {SCREEN_WIDTH - UI_PANEL_WIDTH + 10,
            base_y + i * 14};
        sfText_setFont(text, gui->font);
        sfText_setString(text, legend[i]);
        sfText_setCharacterSize(text, 9);
        sfText_setColor(text, i == 0 ?
            (sfColor){255, 255, 100, 255} :
            (sfColor){180, 180, 255, 255});
        sfText_setPosition(text, pos);
        sfRenderWindow_drawText(gui->window, text, NULL);
        sfText_destroy(text);
        i++;
    }
}

static void render_controls_help(gui_state_t *gui)
{
    const char *controls[] = {
        "Controls:",
        "SPACE - Play/Pause",
        "+/- - Speed",
        "S - Next Scenario",
        "R - Reset",
        "T - Toggle Flows",
        "ESC - Exit"
    };
    int base_y = 280;
    int i = 0;

    while (i < 7) {
        sfText *text = sfText_create();
        sfVector2f pos = {SCREEN_WIDTH - UI_PANEL_WIDTH + 10,
            base_y + i * 15};
        sfText_setFont(text, gui->font);
        sfText_setString(text, controls[i]);
        sfText_setCharacterSize(text, 9);
        sfText_setColor(text, i == 0 ? sfYellow : sfWhite);
        sfText_setPosition(text, pos);
        sfRenderWindow_drawText(gui->window, text, NULL);
        sfText_destroy(text);
        i++;
    }
}

void render_ui_panel(gui_state_t *gui)
{
    sfRectangleShape *panel = NULL;

    if (!gui || !gui->window)
        return;
    panel = create_panel_background();
    sfRenderWindow_drawRectangleShape(gui->window, panel, NULL);
    sfRectangleShape_destroy(panel);
    render_panel_title(gui);
    render_year_display(gui);
    render_speed_display(gui);
    render_scenario_info(gui);
    render_product_legend(gui);
    render_controls_help(gui);
}

void render_control_panel(gui_state_t *gui)
{
    render_ui_panel(gui);
}

void render_legend_panel(gui_state_t *gui)
{
    (void)gui;
}
