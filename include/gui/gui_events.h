/*
** EPITECH PROJECT, 2025
** Trade Barrier Impact Simulator
** File description:
** GUI event handling
*/

#ifndef GUI_EVENTS_H
    #define GUI_EVENTS_H

    #include <SFML/Graphics.h>
    #include "gui/gui_core.h"

void gui_handle_events(gui_state_t *gui, sfEvent *event);
void gui_handle_keyboard(gui_state_t *gui, sfKeyEvent *key);
void gui_handle_mouse_click(gui_state_t *gui, sfVector2i pos);

#endif
