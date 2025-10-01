/*
** EPITECH PROJECT, 2025
** Trade Barrier Impact Simulator
** File description:
** Economic impact animations implementation
*/

#include "animation/anim_impacts.h"
#include "utils/utils_memory.h"
#include <string.h>

void create_impact_animation(animation_manager_t *manager,
    const char *code, double current, double target,
    float duration)
{
    impact_animation_t *anim = NULL;

    if (!manager || !code)
        return;
    anim = safe_malloc(sizeof(impact_animation_t));
    safe_strncpy(anim->country_code, code, MAX_CODE_LEN);
    anim->start_impact = current;
    anim->target_impact = target;
    anim->current_impact = current;
    anim->progress = 0.0f;
    anim->duration = duration;
    anim->is_active = true;
    anim->next = manager->impact_animations;
    manager->impact_animations = anim;
}

static float ease_in_out(float t)
{
    return t < 0.5f ? 2 * t * t : -1 + (4 - 2 * t) * t;
}

static void update_single_impact(impact_animation_t *anim,
    float delta)
{
    float t = 0.0f;

    if (!anim->is_active)
        return;
    anim->progress += delta / anim->duration;
    if (anim->progress >= 1.0f) {
        anim->progress = 1.0f;
        anim->is_active = false;
        anim->current_impact = anim->target_impact;
    } else {
        t = ease_in_out(anim->progress);
        anim->current_impact = anim->start_impact +
            (anim->target_impact - anim->start_impact) * t;
    }
}

void update_impact_animations(animation_manager_t *manager,
    float delta, world_map_t *map, gui_state_t *gui)
{
    impact_animation_t *anim = NULL;

    if (!manager || !map || !gui)
        return;
    anim = manager->impact_animations;
    while (anim) {
        update_single_impact(anim, delta);
        if (anim->is_active) {
            country_region_t *region = find_country_region(map,
                anim->country_code);
            if (region) {
                update_country_color(region, anim->current_impact,
                    &gui->colors);
                map->needs_update = true;
            }
        }
        anim = anim->next;
    }
}
