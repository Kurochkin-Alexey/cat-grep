#include "s21_cat.h"

void parse_args(int argc, char *argv[], int *b_flag, int *e_flag, int *n_flag,
                int *s_flag, int *t_flag, int *a_flag) {
  int flags;
  const char *short_options = "beEnstTA";
  const struct option long_options[] = {
      {"number-nonblank", no_argument, b_flag, 1},
      {"show-all", no_argument, a_flag, 1},
      {"show-ends", no_argument, e_flag, 1},
      {"number", no_argument, n_flag, 1},
      {"squeeze-blank", no_argument, s_flag, 1},
      {"show-tabs", no_argument, t_flag, 1},
      {0, 0, 0, 0}};
  while ((flags = getopt_long(argc, argv, short_options, long_options, NULL)) !=
         -1) {
    switch (flags) {
      case 0:
        break;
      case 'b':
        (*b_flag)++;
        break;
      case 'e':
      case 'E':
        (*e_flag)++;
        break;
      case 'n':
        (*n_flag)++;
        break;
      case 't':
      case 'T':
        (*t_flag)++;
        break;
      case 's':
        (*s_flag)++;
        break;
      case 'A':
        (*a_flag)++;
        break;
      default:
        fprintf(stderr, "Usage: %s [OPTIONS] [FILE]...\n", argv[0]);
        exit(EXIT_FAILURE);
    }
  }
  if (argc == optind) {
    fprintf(stderr, "Usage: %s [OPTIONS] [FILE]...\n", argv[0]);
    exit(EXIT_FAILURE);
  }
}

FILE *open_file(const char *filename, char *argv[]) {
  FILE *file = fopen(filename, "r");
  if (file == NULL) {
    fprintf(stderr, "%s: %s: No such file or directory\n", argv[0], filename);
    exit(EXIT_FAILURE);
  }
  return file;
}

void process_file(FILE *file, int b_flag, int e_flag, int n_flag, int s_flag,
                  int t_flag, int a_flag, int *line_number, int *first_pass,
                  int *counter, int *empty_string) {
  char *buffer = NULL;
  size_t buffer_size = 0;
  int last_empty_line = 0;
  int last_str = 0;
  string_counter(file, &buffer, &buffer_size, s_flag, &last_str,
                 &last_empty_line);
  while ((getline(&buffer, &buffer_size, file)) != -1) {
    int is_squeezable = process_s_flag(&buffer, &last_empty_line, s_flag);
    if (*counter + 1 == last_str) {
      (buffer[strlen(buffer) - 1] == '\n') ? ((*empty_string) = 1)
                                           : ((*empty_string) = 0);
    }
    if (!s_flag) {
      (*counter)++;
    }
    if (s_flag && !is_squeezable) {
      (*counter)++;
    }
    if (!is_squeezable || !s_flag) {
      process_t_flag(&buffer, &buffer_size, t_flag, a_flag);
      process_b_flag(&buffer, &buffer_size, b_flag, line_number, first_pass,
                     counter, empty_string);
      process_n_flag(&buffer, &buffer_size, n_flag, s_flag, b_flag, line_number,
                     is_squeezable, first_pass, counter, empty_string);
      process_e_flag(&buffer, &buffer_size, e_flag, a_flag, empty_string,
                     counter, last_str);
      process_non_printable_chars(&buffer, &buffer_size, e_flag, t_flag);
      if (*counter != last_str) {
        if (buffer[0] != '\0') {
          fprintf(stdout, "%s", buffer);
        }
      }
      if (*counter == last_str) {
        if (buffer[0] == '\0') {
          fprintf(stdout, "%.*s", (int)strlen(buffer) - 1, buffer);
        } else {
          fprintf(stdout, "%s", buffer);
        }
      }
    }
  }
  free(buffer);
}

void string_counter(FILE *file, char **buffer, size_t *buffer_size, int s_flag,
                    int *last_str, int *last_empty_line) {
  while ((getline(buffer, buffer_size, file)) != -1) {
    if (!s_flag) {
      (*last_str)++;
    }
    if (s_flag) {
      int is_squeezable = process_s_flag(buffer, last_empty_line, s_flag);
      if (!is_squeezable) {
        (*last_str)++;
      }
    }
  }
  rewind(file);
}

int process_s_flag(char **buffer, int *last_empty_line, int s_flag) {
  int length = strlen(*buffer);
  int is_empty_line = (length <= 1);
  int marker = 0;

  if (s_flag && is_empty_line) {
    if (*last_empty_line) {
      marker = 1;
    }
    *last_empty_line = 1;
  } else {
    *last_empty_line = 0;
  }
  return marker;
}

void process_b_flag(char **buffer, size_t *buffer_size, int b_flag,
                    int *line_number, int *first_pass, int *counter,
                    int *empty_string) {
  int length = strlen(*buffer);
  if (b_flag && length > 1) {
    char *tmp = strdup(*buffer);
    *buffer[0] = '\0';
    char *new_buffer = realloc(*buffer, *buffer_size + 100);
    if (new_buffer != NULL) {
      if (*first_pass) {
        sprintf(new_buffer, "%6d\t", (*line_number)++);
      }
      if (!(*empty_string)) {
        if (!*first_pass && *counter != 1) {
          sprintf(new_buffer, "%6d\t", (*line_number)++);
        }
      }
      if (*empty_string && !*first_pass) {
        sprintf(new_buffer, "%6d\t", (*line_number)++);
      }
      strcat(new_buffer, tmp);
      *buffer = new_buffer;
    }
    free(tmp);
  }
}

void process_n_flag(char **buffer, size_t *buffer_size, int n_flag, int s_flag,
                    int b_flag, int *line_number, int is_squeezable,
                    int *first_pass, int *counter, int *empty_string) {
  if (n_flag) {
    if ((!s_flag && !b_flag) || (!is_squeezable && !b_flag)) {
      char *tmp = strdup(*buffer);
      *buffer[0] = '\0';
      char *new_buffer = realloc(*buffer, *buffer_size + 100);
      if (new_buffer != NULL) {
        if (*first_pass) {
          sprintf(new_buffer, "%6d\t", (*line_number)++);
        }
        if (!(*empty_string) && !(*first_pass) && (*counter != 1)) {
          sprintf(new_buffer, "%6d\t", (*line_number)++);
        }
        if (*empty_string && !(*first_pass)) {
          sprintf(new_buffer, "%6d\t", (*line_number)++);
        }
        strcat(new_buffer, tmp);
        *buffer = new_buffer;
      }
      free(tmp);
    }
  }
}

void process_e_flag(char **buffer, size_t *buffer_size, int e_flag, int a_flag,
                    int *empty_string, int *counter, int last_str) {
  int length = strlen(*buffer);
  if (e_flag || a_flag) {
    char *new_buffer = realloc(*buffer, *buffer_size + 10);
    if (new_buffer != NULL) {
      if (((*counter) == last_str)) {
        if (*empty_string) {
          sprintf(new_buffer + length - 1, "%s", "$\n");
        }
      } else {
        if (length > 0 && new_buffer[length - 1] == '\n') {
          new_buffer[length - 1] = '\0';
          sprintf(new_buffer + length - 1, "%s", "$\n");
        } else {
          sprintf(new_buffer + length, "%s", "$");
        }
      }
      *buffer = new_buffer;
    }
  }
}

void process_t_flag(char **buffer, size_t *buffer_size, int t_flag,
                    int a_flag) {
  int length = strlen(*buffer);
  if (t_flag || a_flag) {
    char *new_buffer = realloc(*buffer, *buffer_size + 10);
    if (new_buffer != NULL) {
      for (int i = 0; i < length; i++) {
        if (new_buffer[i] == '\t') {
          memmove(new_buffer + i + 2, new_buffer + i + 1, length - i);
          new_buffer[i] = '^';
          new_buffer[i + 1] = 'I';
          length++;
          i++;
        }
        *buffer = new_buffer;
      }
    }
  }
}

void process_non_printable_chars(char **buffer, size_t *buffer_size, int e_flag,
                                 int t_flag) {
  if (e_flag || t_flag) {
    size_t length = strlen(*buffer);
    char *new_buffer = malloc(*buffer_size + 100);
    if (new_buffer != NULL) {
      size_t new_length = 0;
      for (size_t i = 0; i < length; ++i) {
        if ((*buffer)[i] != '\0' && (*buffer)[i] != '\n' &&
            (*buffer)[i] != '\t') {
          if (((*buffer)[i] >= 1 && (*buffer)[i] <= 8) ||
              ((*buffer)[i] >= 12 && (*buffer)[i] <= 31)) {
            new_buffer[new_length++] = '^';
            new_buffer[new_length++] = (*buffer)[i] + 64;
          } else if ((*buffer)[i] == 127) {
            new_buffer[new_length++] = '^';
            new_buffer[new_length++] = (*buffer)[i] - 64;
          } else {
            new_buffer[new_length++] = (*buffer)[i];
          }
        } else {
          new_buffer[new_length++] = (*buffer)[i];
        }
      }
      new_buffer[new_length] = '\0';
      free(*buffer);
      *buffer = new_buffer;
      *buffer_size = new_length;
    } else {
      fprintf(stderr, "Error: Memory allocation failed\n");
    }
  }
}
