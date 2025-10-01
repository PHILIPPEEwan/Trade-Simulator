/*
** EPITECH PROJECT, 2025
** Trade Barrier Impact Simulator
** File description:
** Dynamic economic events implementation
*/

#include "scenario/scenario_events.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static economic_event_t g_current_event = {EVENT_NONE, "", "", 0.0f, 0.0f,
    false};
static float g_event_timer = 0.0f;

static void trigger_random_event(app_state_t *state)
{
    const char *countries[] = {"USA", "CHN", "DEU", "JPN", "GBR", "FRA"};
    int event_roll = rand() % 5;
    int country_idx = rand() % 6;

    g_current_event.type = event_roll + 1;
    strncpy(g_current_event.country_code, countries[country_idx],
        MAX_CODE_LEN - 1);
    g_current_event.country_code[MAX_CODE_LEN - 1] = '\0';
    g_current_event.elapsed = 0.0f;
    g_current_event.duration = 15.0f + (rand() % 20);
    g_current_event.is_active = true;
    (void)state;
    switch (g_current_event.type) {
        case EVENT_RECESSION:
            snprintf(g_current_event.description, 256,
                "%s enters recession (-2%% GDP)",
                g_current_event.country_code);
            break;
        case EVENT_BOOM:
            snprintf(g_current_event.description, 256,
                "%s economic boom (+3%% GDP)", g_current_event.country_code);
            break;
        case EVENT_TRADE_AGREEMENT:
            snprintf(g_current_event.description, 256,
                "%s signs new trade agreement", g_current_event.country_code);
            break;
        case EVENT_SANCTIONS:
            snprintf(g_current_event.description, 256,
                "International sanctions on %s", g_current_event.country_code);
            break;
        case EVENT_CURRENCY_CRISIS:
            snprintf(g_current_event.description, 256,
                "%s currency crisis (-15%% value)",
                g_current_event.country_code);
            break;
        default:
            break;
    }
}

void update_events(app_state_t *state, gui_state_t *gui, float delta_time)
{
    if (!state || !gui)
        return;
    g_event_timer += delta_time;
    if (g_current_event.is_active) {
        g_current_event.elapsed += delta_time;
        if (g_current_event.elapsed >= g_current_event.duration) {
            g_current_event.is_active = false;
            g_event_timer = 0.0f;
        }
    } else if (g_event_timer >= 30.0f && (rand() % 100) < 20) {
        trigger_random_event(state);
        g_event_timer = 0.0f;
    }
}

static void draw_notification_box(sfRenderWindow *window)
{
    sfRectangleShape *box = sfRectangleShape_create();
    sfVector2f size = {400, 60};
    sfVector2f pos = {(SCREEN_WIDTH - 400) / 2, 100};
    sfColor bg = {255, 100, 50, 220};
    sfColor border = {255, 200, 100, 255};

    if (g_current_event.type == EVENT_BOOM)
        bg = (sfColor){50, 200, 100, 220};
    else if (g_current_event.type == EVENT_TRADE_AGREEMENT)
        bg = (sfColor){100, 150, 255, 220};
    sfRectangleShape_setSize(box, size);
    sfRectangleShape_setPosition(box, pos);
    sfRectangleShape_setFillColor(box, bg);
    sfRectangleShape_setOutlineColor(box, border);
    sfRectangleShape_setOutlineThickness(box, 3);
    sfRenderWindow_drawRectangleShape(window, box, NULL);
    sfRectangleShape_destroy(box);
}

static void draw_event_text(sfRenderWindow *window, sfFont *font)
{
    sfText *title = sfText_create();
    sfText *desc = sfText_create();
    sfVector2f title_pos = {(SCREEN_WIDTH - 400) / 2 + 10, 105};
    sfVector2f desc_pos = {(SCREEN_WIDTH - 400) / 2 + 10, 128};

    sfText_setFont(title, font);
    sfText_setString(title, "ECONOMIC EVENT");
    sfText_setCharacterSize(title, 16);
    sfText_setColor(title, sfWhite);
    sfText_setPosition(title, title_pos);
    sfRenderWindow_drawText(window, title, NULL);
    sfText_setFont(desc, font);
    sfText_setString(desc, g_current_event.description);
    sfText_setCharacterSize(desc, 14);
    sfText_setColor(desc, sfWhite);
    sfText_setPosition(desc, desc_pos);
    sfRenderWindow_drawText(window, desc, NULL);
    sfText_destroy(title);
    sfText_destroy(desc);
}

void render_event_notifications(gui_state_t *gui, app_state_t *state)
{
    if (!gui || !state || !g_current_event.is_active)
        return;
    if (g_current_event.elapsed < 8.0f) {
        draw_notification_box(gui->window);
        draw_event_text(gui->window, gui->font);
    }
}
