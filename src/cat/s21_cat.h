#ifndef CAT_H
#define CAT_H
#define  _GNU_SOURCE
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void parse_args(int argc, char *argv[], int *b_flag, int *e_flag, int *n_flag,
                int *s_flag, int *t_flag, int *a_flag);
FILE *open_file(const char *filename, char *argv[]);
void process_file(FILE *file, int b_flag, int e_flag, int n_flag, int s_flag,
                  int t_flag, int a_flag, int *line_number, int *first_pass,
                  int *counter, int *empty_string);
void string_counter(FILE *file, char **buffer, size_t *buffer_size, int s_flag,
                    int *last_str, int *last_empty_line);
int process_s_flag(char **buffer, int *last_empty_line, int s_flag);
void process_b_flag(char **buffer, size_t *buffer_size, int b_flag,
                    int *line_number, int *first_pass, int *counter,
                    int *empty_string);
void process_n_flag(char **buffer, size_t *buffer_size, int n_flag, int s_flag,
                    int b_flag, int *line_number, int is_squeezable,
                    int *first_pass, int *counter, int *empty_string);
void process_e_flag(char **buffer, size_t *buffer_size, int e_flag, int a_flag,
                    int *empty_string, int *counter, int last_str);
void process_t_flag(char **buffer, size_t *buffer_size, int t_flag, int a_flag);
void process_non_printable_chars(char **buffer, size_t *buffer_size, int e_flag,
                                 int t_flag);

#endif /*CAT_H*/