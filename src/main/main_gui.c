/*
** EPITECH PROJECT, 2025
** Trade Barrier Impact Simulator
** File description:
** Main program entry point with GUI
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "main/main_init.h"
#include "gui/gui_core.h"
#include "gui/gui_events.h"
#include "gui/gui_render.h"
#include "gui/gui_panels.h"
#include "gui/gui_tooltip.h"
#include "map/world_map.h"
#include "map/map_render.h"
#include "map/map_arrows.h"
#include "animation/anim_core.h"
#include "animation/anim_particles.h"
#include "scenario/scenario_events.h"

static void display_welcome(void)
{
    printf("\n================================\n");
    printf("  Trade Barrier Simulator GUI\n");
    printf("================================\n\n");
}

static void run_main_loop(gui_state_t *gui, app_state_t *state)
{
    sfEvent event;
    world_map_t *map = create_world_map(gui->font);
    render_params_t map_params = {gui->window, map, gui};
    float delta_time = 0.0f;

    (void)state;

    while (sfRenderWindow_isOpen(gui->window) && gui->is_running) {
        delta_time = sfTime_asSeconds(sfClock_restart(gui->clock));
        while (sfRenderWindow_pollEvent(gui->window, &event))
            gui_handle_events(gui, &event);
        if (!gui->is_paused) {
            gui_update_time(gui, delta_time);
            update_particles(delta_time);
            update_events(state, gui, delta_time);
        }
        gui_clear_screen(gui);
        render_world_map(&map_params);
        render_country_labels(&map_params);
        render_trade_arrows(gui->window, state->trade_flows,
            state->barriers, gui);
        render_particles(gui->window, state->trade_flows, gui);
        render_event_notifications(gui, state);
        render_tooltip(gui, state);
        render_ui_panel(gui);
        render_status_bar(gui);
        render_status_text_public(gui);
        sfRenderWindow_display(gui->window);
    }
    cleanup_particles();
    free_world_map(map);
}

int main(void)
{
    app_state_t state = {0};
    gui_state_t gui = {0};

    srand(time(NULL));
    display_welcome();
    init_sim_params(&state.sim_params);
    if (!init_simulation_data(&state)) {
        fprintf(stderr, "Failed to load data\n");
        cleanup_app_state(&state);
        return 1;
    }
    if (!gui_initialize(&gui)) {
        fprintf(stderr, "Failed to init GUI\n");
        cleanup_app_state(&state);
        return 1;
    }
    gui.app_state = &state;
    gui.current_scenario_index = 0;
    apply_scenario(&state, 0);
    printf("GUI initialized successfully. Starting main loop...\n");
    run_main_loop(&gui, &state);
    gui_cleanup(&gui);
    cleanup_app_state(&state);
    return 0;
}
