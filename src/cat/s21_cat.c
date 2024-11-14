#include "s21_cat.h"

int main(int argc, char *argv[]) {
  int line_number = 1;
  int first_pass = 1;
  int empty_string = 0;
  int b_flag = 0, e_flag = 0, n_flag = 0, s_flag = 0, t_flag = 0, a_flag = 0;

  parse_args(argc, argv, &b_flag, &e_flag, &n_flag, &s_flag, &t_flag, &a_flag);

  for (int i = optind; i < argc; i++) {
    FILE *file = open_file(argv[i], argv);
    int counter = 0;
    process_file(file, b_flag, e_flag, n_flag, s_flag, t_flag, a_flag,
                 &line_number, &first_pass, &counter, &empty_string);
    first_pass = 0;
    fclose(file);
  }

  return 0;
}
