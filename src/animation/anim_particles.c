/*
** EPITECH PROJECT, 2025
** Trade Barrier Impact Simulator
** File description:
** Particle effects implementation
*/

#include "animation/anim_particles.h"
#include "map/map_coords.h"
#include <stdlib.h>
#include <math.h>

typedef struct particle_s {
    sfVector2f position;
    sfVector2f velocity;
    sfColor color;
    float life;
    float size;
    struct particle_s *next;
} particle_t;

static particle_t *g_particles = NULL;
static float g_spawn_timer = 0.0f;

static void spawn_particle(sfVector2f start, sfVector2f end, sfColor color)
{
    particle_t *p = malloc(sizeof(particle_t));
    float angle = atan2(end.y - start.y, end.x - start.x);
    float speed = 150.0f + (rand() % 100);

    if (!p)
        return;
    p->position = start;
    p->velocity.x = cos(angle) * speed;
    p->velocity.y = sin(angle) * speed;
    p->color = color;
    p->color.a = 200;
    p->life = 1.0f + (rand() % 100) / 100.0f;
    p->size = 2.0f + (rand() % 3);
    p->next = g_particles;
    g_particles = p;
}

void update_particles(float delta_time)
{
    particle_t *p = g_particles;
    particle_t *prev = NULL;
    particle_t *next = NULL;

    while (p) {
        next = p->next;
        p->position.x += p->velocity.x * delta_time;
        p->position.y += p->velocity.y * delta_time;
        p->life -= delta_time;
        p->color.a = (unsigned char)(200 * (p->life / 2.0f));
        if (p->life <= 0.0f) {
            if (prev)
                prev->next = next;
            else
                g_particles = next;
            free(p);
        } else {
            prev = p;
        }
        p = next;
    }
}

static void render_single_particle(sfRenderWindow *window, particle_t *p)
{
    sfCircleShape *circle = sfCircleShape_create();

    sfCircleShape_setRadius(circle, p->size);
    sfCircleShape_setPosition(circle,
        (sfVector2f){p->position.x - p->size, p->position.y - p->size});
    sfCircleShape_setFillColor(circle, p->color);
    sfRenderWindow_drawCircleShape(window, circle, NULL);
    sfCircleShape_destroy(circle);
}

void render_particles(sfRenderWindow *window, trade_flow_t *flows,
    gui_state_t *gui)
{
    particle_t *p = g_particles;
    trade_flow_t *flow = flows;

    if (!window || !gui || !gui->show_particles)
        return;
    g_spawn_timer += 0.016f;
    if (g_spawn_timer >= 0.3f) {
        g_spawn_timer = 0.0f;
        while (flow) {
            if (flow->exporter && flow->importer &&
                flow->value > 5000000000.0) {
                sfVector2f start = gui_country_to_screen_pos(flow->exporter);
                sfVector2f end = gui_country_to_screen_pos(flow->importer);
                sfColor color = {100, 200, 255, 200};
                spawn_particle(start, end, color);
            }
            flow = flow->next;
        }
    }
    while (p) {
        render_single_particle(window, p);
        p = p->next;
    }
}

void cleanup_particles(void)
{
    particle_t *p = g_particles;
    particle_t *next = NULL;

    while (p) {
        next = p->next;
        free(p);
        p = next;
    }
    g_particles = NULL;
}
