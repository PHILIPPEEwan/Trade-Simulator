/*
** EPITECH PROJECT, 2025
** Trade Barrier Impact Simulator
** File description:
** Animation rendering functions
*/

#ifndef ANIM_RENDER_H
    #define ANIM_RENDER_H

    #include <SFML/Graphics.h>
    #include "animation/anim_core.h"
    #include "gui/gui_core.h"

void render_animated_arrows(sfRenderWindow *window,
    animation_manager_t *manager);
void render_animation_timeline(sfRenderWindow *window,
    animation_manager_t *manager, gui_state_t *gui);
sfVector2f interpolate_position(sfVector2f start, sfVector2f end,
    float progress);
float ease_in_out(float t);

#endif
