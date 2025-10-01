/*
** EPITECH PROJECT, 2025
** Trade Barrier Impact Simulator
** File description:
** Map coordinate conversion utilities
*/

#ifndef MAP_COORDS_H
    #define MAP_COORDS_H

    #include <SFML/Graphics.h>
    #include "types.h"

sfVector2f map_coords_to_screen(int map_x, int map_y);
sfVector2i screen_to_map_coords(sfVector2f screen_pos);
sfVector2f get_country_center(const char *country_code);
sfVector2f gui_country_to_screen_pos(country_t *country);

#endif
