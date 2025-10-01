/*
** EPITECH PROJECT, 2025
** Trade Barrier Impact Simulator
** File description:
** Mathematical utility functions
*/

#ifndef UTILS_MATH_H
    #define UTILS_MATH_H

double clamp(double value, double min, double max);
double interpolate(double a, double b, double t);
double random_double(double min, double max);
int random_int(int min, int max);

#endif
