/*
** EPITECH PROJECT, 2025
** Trade Barrier Impact Simulator
** File description:
** Particle effects for trade routes
*/

#ifndef ANIM_PARTICLES_H
    #define ANIM_PARTICLES_H

    #include <SFML/Graphics.h>
    #include "types.h"
    #include "gui/gui_core.h"

void update_particles(float delta_time);
void render_particles(sfRenderWindow *window, trade_flow_t *flows,
    gui_state_t *gui);
void cleanup_particles(void);

#endif
