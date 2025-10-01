/*
** EPITECH PROJECT, 2025
** Trade Barrier Impact Simulator
** File description:
** Interactive tooltip implementation
*/

#include "gui/gui_tooltip.h"
#include "map/world_map.h"
#include "map/map_coords.h"
#include "main/main_init.h"
#include <stdio.h>
#include <string.h>

static const char *find_country_at_pos(sfVector2i pos)
{
    int i = 0;
    int count = get_country_count();

    while (i < count) {
        const country_def_t *def = get_country_def(i);
        if (pos.x >= def->position.x &&
            pos.x <= def->position.x + def->size.x &&
            pos.y >= def->position.y &&
            pos.y <= def->position.y + def->size.y) {
            return def->code;
        }
        i++;
    }
    return NULL;
}

void update_hovered_country(gui_state_t *gui, sfVector2i mouse_pos)
{
    const char *country_code = NULL;

    if (!gui)
        return;
    gui->mouse_pos = mouse_pos;
    country_code = find_country_at_pos(mouse_pos);
    if (country_code)
        snprintf(gui->hovered_country, sizeof(gui->hovered_country),
            "%s", country_code);
    else
        gui->hovered_country[0] = '\0';
}

static const char *convert_to_3letter(const char *code_2letter)
{
    if (strcmp(code_2letter, "US") == 0) return "USA";
    if (strcmp(code_2letter, "CN") == 0) return "CHN";
    if (strcmp(code_2letter, "DE") == 0) return "DEU";
    if (strcmp(code_2letter, "JP") == 0) return "JPN";
    if (strcmp(code_2letter, "GB") == 0) return "GBR";
    if (strcmp(code_2letter, "FR") == 0) return "FRA";
    if (strcmp(code_2letter, "BR") == 0) return "BRA";
    if (strcmp(code_2letter, "IN") == 0) return "IND";
    if (strcmp(code_2letter, "CA") == 0) return "CAN";
    if (strcmp(code_2letter, "MX") == 0) return "MEX";
    if (strcmp(code_2letter, "KR") == 0) return "KOR";
    if (strcmp(code_2letter, "IT") == 0) return "ITA";
    if (strcmp(code_2letter, "ES") == 0) return "ESP";
    if (strcmp(code_2letter, "AU") == 0) return "AUS";
    if (strcmp(code_2letter, "RU") == 0) return "RUS";
    if (strcmp(code_2letter, "ZA") == 0) return "ZAF";
    if (strcmp(code_2letter, "NZ") == 0) return "NZL";
    if (strcmp(code_2letter, "ID") == 0) return "IDN";
    if (strcmp(code_2letter, "SA") == 0) return "SAU";
    if (strcmp(code_2letter, "TR") == 0) return "TUR";
    if (strcmp(code_2letter, "TH") == 0) return "THA";
    if (strcmp(code_2letter, "PL") == 0) return "POL";
    if (strcmp(code_2letter, "NL") == 0) return "NLD";
    if (strcmp(code_2letter, "BE") == 0) return "BEL";
    if (strcmp(code_2letter, "CH") == 0) return "CHE";
    if (strcmp(code_2letter, "SE") == 0) return "SWE";
    if (strcmp(code_2letter, "NO") == 0) return "NOR";
    if (strcmp(code_2letter, "AT") == 0) return "AUT";
    if (strcmp(code_2letter, "AR") == 0) return "ARG";
    if (strcmp(code_2letter, "CL") == 0) return "CHL";
    if (strcmp(code_2letter, "SG") == 0) return "SGP";
    if (strcmp(code_2letter, "MY") == 0) return "MYS";
    if (strcmp(code_2letter, "PH") == 0) return "PHL";
    if (strcmp(code_2letter, "VN") == 0) return "VNM";
    if (strcmp(code_2letter, "AE") == 0) return "ARE";
    if (strcmp(code_2letter, "IL") == 0) return "ISR";
    if (strcmp(code_2letter, "IE") == 0) return "IRL";
    if (strcmp(code_2letter, "DK") == 0) return "DNK";
    if (strcmp(code_2letter, "FI") == 0) return "FIN";
    if (strcmp(code_2letter, "PT") == 0) return "PRT";
    if (strcmp(code_2letter, "GR") == 0) return "GRC";
    if (strcmp(code_2letter, "CZ") == 0) return "CZE";
    if (strcmp(code_2letter, "RO") == 0) return "ROU";
    if (strcmp(code_2letter, "HU") == 0) return "HUN";
    if (strcmp(code_2letter, "CO") == 0) return "COL";
    if (strcmp(code_2letter, "PE") == 0) return "PER";
    if (strcmp(code_2letter, "PK") == 0) return "PAK";
    if (strcmp(code_2letter, "BD") == 0) return "BGD";
    if (strcmp(code_2letter, "NG") == 0) return "NGA";
    if (strcmp(code_2letter, "EG") == 0) return "EGY";
    if (strcmp(code_2letter, "KE") == 0) return "KEN";
    if (strcmp(code_2letter, "ET") == 0) return "ETH";
    if (strcmp(code_2letter, "MA") == 0) return "MAR";
    if (strcmp(code_2letter, "EC") == 0) return "ECU";
    if (strcmp(code_2letter, "UA") == 0) return "UKR";
    if (strcmp(code_2letter, "IQ") == 0) return "IRQ";
    return code_2letter;
}

static country_t *find_country_by_code(app_state_t *state, const char *code)
{
    country_t *country = state->countries;
    const char *code_3letter = convert_to_3letter(code);

    while (country) {
        if (strcmp(country->code, code_3letter) == 0)
            return country;
        country = country->next;
    }
    return NULL;
}

static void calc_trade_stats(app_state_t *state, const char *code,
    double *exports, double *imports, int *partners)
{
    trade_flow_t *flow = state->trade_flows;

    *exports = 0.0;
    *imports = 0.0;
    *partners = 0;
    while (flow) {
        if (flow->exporter && strcmp(flow->exporter->code, code) == 0) {
            *exports += flow->value;
            (*partners)++;
        }
        if (flow->importer && strcmp(flow->importer->code, code) == 0)
            *imports += flow->value;
        flow = flow->next;
    }
}

static void draw_tooltip_box(sfRenderWindow *window, sfVector2f pos)
{
    sfRectangleShape *box = sfRectangleShape_create();
    sfVector2f size = {240, 110};
    sfColor bg = {20, 20, 30, 230};
    sfColor border = {100, 150, 255, 255};

    sfRectangleShape_setSize(box, size);
    sfRectangleShape_setPosition(box, pos);
    sfRectangleShape_setFillColor(box, bg);
    sfRectangleShape_setOutlineColor(box, border);
    sfRectangleShape_setOutlineThickness(box, 2);
    sfRenderWindow_drawRectangleShape(window, box, NULL);
    sfRectangleShape_destroy(box);
}

static void draw_tooltip_text(sfRenderWindow *window, sfFont *font,
    sfVector2f pos, const char *text, int line)
{
    sfText *label = sfText_create();
    sfVector2f text_pos = {pos.x + 10, pos.y + 8 + line * 18};

    sfText_setFont(label, font);
    sfText_setString(label, text);
    sfText_setCharacterSize(label, 13);
    sfText_setColor(label, sfWhite);
    sfText_setPosition(label, text_pos);
    sfRenderWindow_drawText(window, label, NULL);
    sfText_destroy(label);
}

void render_tooltip(gui_state_t *gui, app_state_t *state)
{
    country_t *country = NULL;
    double exports = 0.0;
    double imports = 0.0;
    int partners = 0;
    char text[256];
    sfVector2f pos;

    if (!gui || !state || !gui->show_tooltips)
        return;
    if (gui->hovered_country[0] == '\0')
        return;
    country = find_country_by_code(state, gui->hovered_country);
    if (!country)
        return;
    calc_trade_stats(state, convert_to_3letter(gui->hovered_country), &exports,
        &imports, &partners);
    pos.x = gui->mouse_pos.x + 20;
    pos.y = gui->mouse_pos.y + 20;
    if (pos.x + 240 > SCREEN_WIDTH)
        pos.x = gui->mouse_pos.x - 260;
    if (pos.y + 110 > SCREEN_HEIGHT)
        pos.y = gui->mouse_pos.y - 130;
    draw_tooltip_box(gui->window, pos);
    snprintf(text, sizeof(text), "%s", country->name);
    draw_tooltip_text(gui->window, gui->font, pos, text, 0);
    snprintf(text, sizeof(text), "GDP: $%.1fT",
        country->gdp / 1000000000000.0);
    draw_tooltip_text(gui->window, gui->font, pos, text, 1);
    snprintf(text, sizeof(text), "Pop: %.1fM",
        country->population / 1000000.0);
    draw_tooltip_text(gui->window, gui->font, pos, text, 2);
    snprintf(text, sizeof(text), "Exports: $%.1fB", exports / 1000000000.0);
    draw_tooltip_text(gui->window, gui->font, pos, text, 3);
    snprintf(text, sizeof(text), "Imports: $%.1fB", imports / 1000000000.0);
    draw_tooltip_text(gui->window, gui->font, pos, text, 4);
    snprintf(text, sizeof(text), "Trade Partners: %d", partners);
    draw_tooltip_text(gui->window, gui->font, pos, text, 5);
}
