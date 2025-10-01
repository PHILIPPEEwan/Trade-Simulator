/*
** EPITECH PROJECT, 2025
** Trade Barrier Impact Simulator
** File description:
** Mathematical utility functions implementation
*/

#include <stdlib.h>
#include "utils/utils_math.h"

double clamp(double value, double min, double max)
{
    if (value < min)
        return min;
    if (value > max)
        return max;
    return value;
}

double interpolate(double a, double b, double t)
{
    return a + (b - a) * t;
}

double random_double(double min, double max)
{
    double scale = rand() / (double)RAND_MAX;

    return min + scale * (max - min);
}

int random_int(int min, int max)
{
    return min + rand() % (max - min + 1);
}
