#ifndef GREP_H
#define GREP_H
#define  _GNU_SOURCE

#include <ctype.h>
#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ANSI_COLOR_RED "\033[1;31m"
#define ANSI_COLOR_GREEN "\033[1;32m"
#define ANSI_COLOR_PURPLE "\033[1;35m"
#define ANSI_COLOR_BLUE "\e[0;34m"
#define ANSI_COLOR_RESET "\x1b[0m"
#define colon ":"

void parse_args(int argc, char *argv[], int *e_flag, int *i_flag, int *v_flag,
                int *c_flag, int *l_flag, int *n_flag, int *h_flag, int *s_flag,
                int *f_flag, int *o_flag, char **e_arg, char **f_arg);
FILE *open_file(char *filename, char *argv[], int s_flag);
int o_flag_counter(char **buffer, char *required_data, int i_flag, int reti,
                   regex_t regex);
void string_counter(char **buffer, size_t *buffer_size, FILE *file, int f_flag,
                    int i_flag, char *required_data, int *max_str);
char *strcasestr(const char *haystack, const char *needle);
void finder(FILE *file, int argc, int *cycle, char *filename,
            char **f_flag_lines, int *f_cycle_counter, int *v_f_counter,
            int num_lines, char *required_data, int v_flag, int i_flag,
            int c_flag, int n_flag, int l_flag, int h_flag, int o_flag,
            int file_counter, int f_flag);
void define_f_flag(int f_flag, char ***f_flag_lines, char **f_arg,
                   int *num_lines, int s_flag, char *argv[], int argc,
                   int file_counter, int *f_cycle_counter, int *v_f_counter,
                   char *required_data, int v_flag, int i_flag, int c_flag,
                   int n_flag, int l_flag, int h_flag, int o_flag);
void process_without_flags(FILE *file, int v_flag, int o_flag, int f_flag,
                           int i_flag, int reti, regex_t regex,
                           char *required_data, int n_flag, char *buffer,
                           int offset, regmatch_t match, int *line_number,
                           int *smth_found, int h_flag, int c_flag, int l_flag,
                           char *filename, int found, int file_counter);
void define_f_c_flags(int f_flag, int c_flag, int l_flag, int *f_cycle_counter,
                      int argc, int num_lines, char *next_match, int i_flag,
                      char *match1, char **f_flag_lines, int match_found,
                      int *line_number);
void print_stdout(char **buffer, int *line_number, int *n_counter,
                  char *next_match, char *match1, int match_found, int argc,
                  char *filename, char **f_flag_lines, int *f_cycle_counter,
                  int num_lines, int v_flag, int i_flag, int c_flag, int n_flag,
                  int l_flag, int h_flag, int o_flag, int file_counter,
                  int f_flag, int *max_str, int *o_counter, int *cycle);
void print_c_l_flags(char *buffer, int num_lines, int *line_number,
                     int *smth_found, int argc, char *filename,
                     int *f_cycle_counter, int c_flag, int l_flag, int h_flag,
                     int file_counter, int v_flag, int f_flag);
void process_v_flag(char **buffer, size_t *buffer_size, char *required_data,
                    int v_flag, int i_flag, int *line_number, int n_flag,
                    int h_flag, int *smth_found, int file_counter,
                    char *filename, int f_flag, int *reti, regex_t regex);
void process_i_flag(char **buffer, size_t *buffer_size, char *required_data,
                    int i_flag, int *line_number, int n_flag, int v_flag,
                    int *smth_found, int f_flag, int reti, regex_t regex,
                    int c_flag);
void process_n_flag(char **buffer, size_t *buffer_size, char *required_data,
                    int n_flag, int *line_number, int i_flag, int c_flag,
                    int v_flag, int h_flag, int *smth_found, int file_counter,
                    char *filename, int f_flag, int reti, regex_t regex);
void process_ni_flag(int i_flag, int v_flag, int c_flag, char *required_data,
                     int reti, regex_t regex, char *tmp, char **buffer,
                     size_t *buffer_size, int *smth_found, int *line_number);
void process_nv_flag(int i_flag, int v_flag, int c_flag, char *required_data,
                     int reti, regex_t regex, char *tmp, char **buffer,
                     size_t *buffer_size, int *smth_found, int *line_number,
                     int h_flag, char *filename, int file_counter);
void process_nvi_flag(int i_flag, int v_flag, int c_flag, char *required_data,
                      int reti, regex_t regex, char *tmp, char **buffer,
                      size_t *buffer_size, int *smth_found, int *line_number,
                      int h_flag, char *filename, int file_counter);
void process_o_flag(char **buffer, size_t *buffer_size, char *required_data,
                    int o_flag, int i_flag, int *line_number, int n_flag,
                    int h_flag, int *smth_found, int file_counter,
                    char *filename, int f_flag, int v_flag, int reti,
                    regex_t regex, int c_flag, int *o_counter);
void process_f_flag(char **buffer, size_t *buffer_size, int num_lines,
                    char **f_flag_lines, int f_flag, int *line_number,
                    int *n_counter, int *v_f_counter, int file_counter,
                    int h_flag, char *filename, int *smth_found, int i_flag,
                    int c_flag, int n_flag, int v_flag, int o_flag);
void process_fi_flag(int i_flag, int o_flag, int v_flag, int num_lines,
                     char *tmp, char **f_flag_lines, char **buffer,
                     int *smth_found);
void process_fn_flag(int n_flag, int i_flag, int v_flag, int num_lines,
                     char *tmp, char **f_flag_lines, char **buffer,
                     int *smth_found);
void process_fni_flag(int n_flag, int i_flag, int v_flag, int num_lines,
                      char *tmp, char **f_flag_lines, char **buffer,
                      int *smth_found);
void process_fvn_flag(int n_flag, int i_flag, int v_flag, int c_flag,
                      int num_lines, char *tmp, char **f_flag_lines,
                      char **buffer, int *smth_found, int *n_counter,
                      int *v_f_counter, int *line_number);
void process_fvni_flag(int n_flag, int i_flag, int v_flag, int c_flag,
                       int num_lines, char *tmp, char **f_flag_lines,
                       char **buffer, int *smth_found, int *n_counter,
                       int *v_f_counter, int *line_number);
void process_fv_flag(int n_flag, int i_flag, int v_flag, int c_flag, int o_flag,
                     int num_lines, char *tmp, char **f_flag_lines,
                     char **buffer, int *smth_found, int *v_f_counter,
                     int *line_number);
void process_fvi_flag(int n_flag, int i_flag, int v_flag, int c_flag,
                      int o_flag, int num_lines, char *tmp, char **f_flag_lines,
                      char **buffer, int *smth_found, int *v_f_counter,
                      int *line_number);
void process_fo_flag(int n_flag, int i_flag, int v_flag, int h_flag, int o_flag,
                     int num_lines, char *tmp, char **f_flag_lines,
                     char **buffer, size_t *buffer_size, int *smth_found,
                     int *line_number, char *filename, int file_counter);
void process_fvo_flag(int v_flag, int o_flag, char *tmp, char **f_flag_lines,
                      int *smth_found, int num_lines, int *line_number);
void process_fvc_flag(int v_flag, int c_flag, char *tmp, char **f_flag_lines,
                      int *smth_found, int num_lines);
void process_foi_flag(int n_flag, int i_flag, int h_flag, int num_lines,
                      char *tmp, char **f_flag_lines, char **buffer,
                      size_t *buffer_size, int *smth_found, int *line_number,
                      char *filename, int file_counter);
char **get_data_f_flag(char *filename, int *num_lines, int s_flag,
                       char *argv[]);
int fo_flag_counter(char *tmp, int num_lines, char **f_flag_lines, int i_flag);

#endif /*GREP_H*/