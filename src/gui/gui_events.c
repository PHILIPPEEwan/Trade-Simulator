/*
** EPITECH PROJECT, 2025
** Trade Barrier Impact Simulator
** File description:
** GUI event handling implementation
*/

#include "gui/gui_events.h"
#include "gui/gui_tooltip.h"
#include "main/main_init.h"
#include <stdio.h>

static void handle_key_space(gui_state_t *gui)
{
    gui->is_paused = !gui->is_paused;
    printf("Simulation %s\n", gui->is_paused ? "paused" : "resumed");
}

static void handle_key_r(gui_state_t *gui)
{
    gui->simulation_time = 0.0f;
    gui->current_year = 0;
    printf("Simulation reset\n");
}

static void handle_key_t(gui_state_t *gui)
{
    gui->show_trade_flows = !gui->show_trade_flows;
    printf("Trade flows %s\n",
        gui->show_trade_flows ? "enabled" : "disabled");
}

static void handle_key_i(gui_state_t *gui)
{
    gui->show_impacts = !gui->show_impacts;
    printf("Impact colors %s\n",
        gui->show_impacts ? "enabled" : "disabled");
}

static void handle_key_n(gui_state_t *gui)
{
    gui->show_country_names = !gui->show_country_names;
    printf("Country names %s\n",
        gui->show_country_names ? "enabled" : "disabled");
}

static void handle_speed_keys(gui_state_t *gui, sfKeyCode code)
{
    if (code == sfKeySubtract && gui->time_multiplier > 0.1f) {
        gui->time_multiplier *= 0.5f;
        printf("Speed: %.1fx\n", gui->time_multiplier);
    }
    if (code == sfKeyAdd && gui->time_multiplier < 8.0f) {
        gui->time_multiplier *= 2.0f;
        printf("Speed: %.1fx\n", gui->time_multiplier);
    }
    if (code == sfKeyLeft && gui->time_multiplier > 0.1f) {
        gui->time_multiplier -= 0.25f;
        if (gui->time_multiplier < 0.1f)
            gui->time_multiplier = 0.1f;
        printf("Speed: %.1fx\n", gui->time_multiplier);
    }
    if (code == sfKeyRight && gui->time_multiplier < 8.0f) {
        gui->time_multiplier += 0.25f;
        printf("Speed: %.1fx\n", gui->time_multiplier);
    }
}

static void handle_key_s(gui_state_t *gui)
{
    app_state_t *state = NULL;

    if (!gui || !gui->app_state)
        return;
    gui->current_scenario_index = (gui->current_scenario_index + 1) % 3;
    gui->simulation_time = 0.0f;
    gui->current_year = 0;
    state = (app_state_t *)gui->app_state;
    apply_scenario(state, gui->current_scenario_index);
    printf("Switched to scenario %d\n", gui->current_scenario_index);
}

void gui_handle_keyboard(gui_state_t *gui, sfKeyEvent *key)
{
    if (!gui || !key)
        return;
    if (key->code == sfKeyEscape)
        gui->is_running = false;
    else if (key->code == sfKeySpace)
        handle_key_space(gui);
    else if (key->code == sfKeyR)
        handle_key_r(gui);
    else if (key->code == sfKeyT)
        handle_key_t(gui);
    else if (key->code == sfKeyI)
        handle_key_i(gui);
    else if (key->code == sfKeyN)
        handle_key_n(gui);
    else if (key->code == sfKeyS)
        handle_key_s(gui);
    else
        handle_speed_keys(gui, key->code);
}

void gui_handle_mouse_click(gui_state_t *gui, sfVector2i pos)
{
    if (!gui)
        return;
    printf("Mouse clicked at (%d, %d)\n", pos.x, pos.y);
}

void gui_handle_events(gui_state_t *gui, sfEvent *event)
{
    sfVector2i pos;

    if (!gui || !event)
        return;
    if (event->type == sfEvtClosed)
        gui->is_running = false;
    else if (event->type == sfEvtKeyPressed)
        gui_handle_keyboard(gui, &event->key);
    else if (event->type == sfEvtMouseButtonPressed) {
        pos.x = event->mouseButton.x;
        pos.y = event->mouseButton.y;
        gui_handle_mouse_click(gui, pos);
    } else if (event->type == sfEvtMouseMoved) {
        pos.x = event->mouseMove.x;
        pos.y = event->mouseMove.y;
        update_hovered_country(gui, pos);
    }
}
