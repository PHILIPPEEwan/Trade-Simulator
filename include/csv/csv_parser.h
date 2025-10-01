/*
** EPITECH PROJECT, 2025
** Trade Barrier Impact Simulator
** File description:
** CSV file parsing utilities
*/

#ifndef CSV_PARSER_H
    #define CSV_PARSER_H

    #include <stdio.h>

typedef struct csv_row_s {
    char **fields;
    int field_count;
    struct csv_row_s *next;
} csv_row_t;

typedef struct csv_data_s {
    csv_row_t *rows;
    int row_count;
    int column_count;
    char **headers;
} csv_data_t;

csv_data_t *parse_csv_file(const char *filename);
void free_csv_data(csv_data_t *data);
char *get_csv_field(csv_data_t *data, int row, int col);
char *get_csv_field_by_header(csv_data_t *data, int row,
    const char *header);

#endif
