/*
** EPITECH PROJECT, 2025
** Trade Barrier Impact Simulator
** File description:
** CSV file parsing implementation
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "csv/csv_parser.h"
#include "utils/utils_memory.h"
#include "utils/utils_string.h"

static int count_fields(char *line)
{
    int count = 1;
    bool in_quotes = false;
    char *p = line;

    while (*p) {
        if (*p == '"')
            in_quotes = !in_quotes;
        else if (*p == ',' && !in_quotes)
            count++;
        p++;
    }
    return count;
}

static void copy_field(char *dest, char *src, int len)
{
    int j = 0;
    bool skip_quotes = false;
    int i = 0;

    while (i < len) {
        if (src[i] == '"' && !skip_quotes) {
            skip_quotes = true;
            i++;
            continue;
        }
        if (src[i] == '"' && i == len - 1) {
            i++;
            continue;
        }
        dest[j++] = src[i];
        i++;
    }
    dest[j] = '\0';
    trim_whitespace(dest);
}

static csv_row_t *parse_csv_line(char *line)
{
    csv_row_t *row = safe_malloc(sizeof(csv_row_t));
    int field_idx = 0;
    char *field_start = line;
    bool in_quotes = false;
    char *p = line;

    row->field_count = count_fields(line);
    row->fields = safe_malloc(sizeof(char *) * row->field_count);
    row->next = NULL;
    while (1) {
        if (*p == '"')
            in_quotes = !in_quotes;
        else if ((*p == ',' && !in_quotes) || *p == '\0') {
            row->fields[field_idx] = safe_malloc(p - field_start + 1);
            copy_field(row->fields[field_idx], field_start,
                p - field_start);
            field_idx++;
            if (*p == '\0')
                break;
            field_start = p + 1;
        }
        p++;
    }
    return row;
}

csv_data_t *parse_csv_file(const char *filename)
{
    FILE *file = fopen(filename, "r");
    csv_data_t *data = NULL;
    char line[1024];
    csv_row_t *last_row = NULL;
    bool first = true;

    if (!file)
        return NULL;
    data = safe_malloc(sizeof(csv_data_t));
    data->rows = NULL;
    data->row_count = 0;
    data->column_count = 0;
    data->headers = NULL;
    while (fgets(line, sizeof(line), file)) {
        csv_row_t *row = NULL;

        line[strcspn(line, "\n\r")] = '\0';
        if (strlen(line) == 0)
            continue;
        row = parse_csv_line(line);
        if (first) {
            data->column_count = row->field_count;
            data->headers = safe_malloc(
                sizeof(char *) * data->column_count);
            for (int i = 0; i < data->column_count; i++)
                data->headers[i] = safe_strdup(row->fields[i]);
            first = false;
        }
        if (data->rows == NULL)
            data->rows = row;
        else
            last_row->next = row;
        last_row = row;
        data->row_count++;
    }
    fclose(file);
    return data;
}

void free_csv_data(csv_data_t *data)
{
    csv_row_t *row = NULL;
    csv_row_t *next = NULL;
    int i = 0;

    if (!data)
        return;
    row = data->rows;
    while (row) {
        next = row->next;
        i = 0;
        while (i < row->field_count) {
            free(row->fields[i]);
            i++;
        }
        free(row->fields);
        free(row);
        row = next;
    }
    if (data->headers) {
        i = 0;
        while (i < data->column_count) {
            free(data->headers[i]);
            i++;
        }
        free(data->headers);
    }
    free(data);
}

char *get_csv_field(csv_data_t *data, int row, int col)
{
    csv_row_t *current = NULL;
    int i = 0;

    if (!data || row >= data->row_count)
        return NULL;
    if (col >= data->column_count)
        return NULL;
    current = data->rows;
    while (i < row) {
        current = current->next;
        i++;
    }
    return current->fields[col];
}

char *get_csv_field_by_header(csv_data_t *data, int row,
    const char *header)
{
    int col = -1;
    int i = 0;

    if (!data || !header)
        return NULL;
    while (i < data->column_count) {
        if (strcmp(data->headers[i], header) == 0) {
            col = i;
            break;
        }
        i++;
    }
    if (col == -1)
        return NULL;
    return get_csv_field(data, row, col);
}
