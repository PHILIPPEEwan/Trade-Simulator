/*
** EPITECH PROJECT, 2025
** Trade Barrier Impact Simulator
** File description:
** Map coordinate conversion implementation
*/

#include "map/map_coords.h"
#include "map/world_map.h"
#include "gui/gui_core.h"
#include <string.h>

sfVector2f map_coords_to_screen(int map_x, int map_y)
{
    sfVector2f screen_pos;

    screen_pos.x = map_x * CHAR_SIZE + MAP_OFFSET_X;
    screen_pos.y = map_y * CHAR_SIZE + MAP_OFFSET_Y;
    return screen_pos;
}

sfVector2i screen_to_map_coords(sfVector2f screen_pos)
{
    sfVector2i map_pos;

    map_pos.x = (int)((screen_pos.x - MAP_OFFSET_X) / CHAR_SIZE);
    map_pos.y = (int)((screen_pos.y - MAP_OFFSET_Y) / CHAR_SIZE);
    return map_pos;
}

static const char *convert_country_code(const char *code)
{
    if (!code)
        return NULL;
    if (strcmp(code, "USA") == 0) return "US";
    if (strcmp(code, "CHN") == 0) return "CN";
    if (strcmp(code, "DEU") == 0) return "DE";
    if (strcmp(code, "JPN") == 0) return "JP";
    if (strcmp(code, "GBR") == 0) return "GB";
    if (strcmp(code, "FRA") == 0) return "FR";
    if (strcmp(code, "BRA") == 0) return "BR";
    if (strcmp(code, "IND") == 0) return "IN";
    if (strcmp(code, "CAN") == 0) return "CA";
    if (strcmp(code, "MEX") == 0) return "MX";
    if (strcmp(code, "KOR") == 0) return "KR";
    if (strcmp(code, "ITA") == 0) return "IT";
    if (strcmp(code, "ESP") == 0) return "ES";
    if (strcmp(code, "AUS") == 0) return "AU";
    if (strcmp(code, "RUS") == 0) return "RU";
    if (strcmp(code, "NLD") == 0) return "NL";
    if (strcmp(code, "BEL") == 0) return "BE";
    if (strcmp(code, "CHE") == 0) return "CH";
    if (strcmp(code, "AUT") == 0) return "AT";
    if (strcmp(code, "POL") == 0) return "PL";
    if (strcmp(code, "SWE") == 0) return "SE";
    if (strcmp(code, "NOR") == 0) return "NO";
    if (strcmp(code, "DNK") == 0) return "DK";
    if (strcmp(code, "FIN") == 0) return "FI";
    if (strcmp(code, "PRT") == 0) return "PT";
    if (strcmp(code, "GRC") == 0) return "GR";
    if (strcmp(code, "TUR") == 0) return "TR";
    if (strcmp(code, "SAU") == 0) return "SA";
    if (strcmp(code, "ARE") == 0) return "AE";
    if (strcmp(code, "IRQ") == 0) return "IQ";
    if (strcmp(code, "EGY") == 0) return "EG";
    if (strcmp(code, "ZAF") == 0) return "ZA";
    if (strcmp(code, "NGA") == 0) return "NG";
    if (strcmp(code, "KEN") == 0) return "KE";
    if (strcmp(code, "ETH") == 0) return "ET";
    if (strcmp(code, "ARG") == 0) return "AR";
    if (strcmp(code, "CHL") == 0) return "CL";
    if (strcmp(code, "COL") == 0) return "CO";
    if (strcmp(code, "PER") == 0) return "PE";
    if (strcmp(code, "VNM") == 0) return "VN";
    if (strcmp(code, "THA") == 0) return "TH";
    if (strcmp(code, "MYS") == 0) return "MY";
    if (strcmp(code, "SGP") == 0) return "SG";
    if (strcmp(code, "IDN") == 0) return "ID";
    if (strcmp(code, "PHL") == 0) return "PH";
    if (strcmp(code, "NZL") == 0) return "NZ";
    if (strcmp(code, "PAK") == 0) return "PK";
    if (strcmp(code, "BGD") == 0) return "BD";
    if (strcmp(code, "ISR") == 0) return "IL";
    if (strcmp(code, "IRL") == 0) return "IE";
    if (strcmp(code, "CZE") == 0) return "CZ";
    if (strcmp(code, "ROU") == 0) return "RO";
    if (strcmp(code, "HUN") == 0) return "HU";
    if (strcmp(code, "UKR") == 0) return "UA";
    if (strcmp(code, "MAR") == 0) return "MA";
    if (strcmp(code, "ECU") == 0) return "EC";
    return code;
}

sfVector2f get_country_center(const char *country_code)
{
    const char *map_code = convert_country_code(country_code);
    int i = 0;
    int count = get_country_count();

    while (i < count) {
        const country_def_t *def = get_country_def(i);
        if (strcmp(def->code, map_code) == 0) {
            return (sfVector2f){
                def->position.x + def->size.x / 2,
                def->position.y + def->size.y / 2
            };
        }
        i++;
    }
    return (sfVector2f){MAP_OFFSET_X + MAP_WIDTH / 2,
        MAP_OFFSET_Y + MAP_HEIGHT / 2};
}

sfVector2f gui_country_to_screen_pos(country_t *country)
{
    if (!country)
        return (sfVector2f){0, 0};
    return get_country_center(country->code);
}
