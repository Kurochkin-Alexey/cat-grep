#include "s21_grep.h"

int main(int argc, char *argv[]) {
  int file_counter = 0;
  int f_cycle_counter = 0;
  int v_f_counter = 0;
  char *required_data = NULL;
  char *e_arg = NULL;
  char *f_arg = NULL;
  char **f_flag_lines;
  int num_lines;
  int e_flag = 0, i_flag = 0, v_flag = 0, c_flag = 0, l_flag = 0, n_flag = 0,
      h_flag = 0, s_flag = 0, f_flag = 0, o_flag = 0;
  parse_args(argc, argv, &e_flag, &i_flag, &v_flag, &c_flag, &l_flag, &n_flag,
             &h_flag, &s_flag, &f_flag, &o_flag, &e_arg, &f_arg);
  if (!e_flag && !f_flag) {
    required_data = argv[optind];
  }
  if (e_flag) {
    required_data = e_arg;
    optind -= 1;
  }
  define_f_flag(f_flag, &f_flag_lines, &f_arg, &num_lines, s_flag, argv, argc,
                file_counter, &f_cycle_counter, &v_f_counter, required_data,
                v_flag, i_flag, c_flag, n_flag, l_flag, h_flag, o_flag);
  if (argc - optind > 2) {
    file_counter = 1;
  }
  for (int i = optind + 1; i < argc; i++) {
    FILE *file = open_file(argv[i], argv, s_flag);
    if (file != NULL) {
      finder(file, argc, &i, argv[i], f_flag_lines, &f_cycle_counter,
             &v_f_counter, num_lines, required_data, v_flag, i_flag, c_flag,
             n_flag, l_flag, h_flag, o_flag, file_counter, f_flag);
      fclose(file);
    }
  }
  if (f_flag) {
    for (int i = 0; i < num_lines; i++) {
      free(f_flag_lines[i]);
    }
    free(f_flag_lines);
  }
  return 0;
}
