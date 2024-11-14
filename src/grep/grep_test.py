import subprocess
import re
from itertools import combinations

test_file = 'tests/test.txt'
test_file_2 = 'tests/test_2.txt'
test_file_3 = 'tests/pattern.txt'
test_file_4 = 'tests/result.txt'

flags = ['-i', '-v', '-c', '-l', '-n', '-h', '-s', '-e', '-f', '-o']
f_flag = '-f'

search_strings = ['[Tt]', 'and', '1.[0-9][0-9]', 'were', 'for', 'aboba']

def execute_command(command):
    result = subprocess.run(command, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
    return result.stdout.strip()

success_count = 0
fail_count = 0

for search_string in search_strings:

    for r in range(1, 11):
        for flag_combination in combinations(flags, r):

            if f_flag in flag_combination and '-c' in flag_combination and '-o' in flag_combination:
                continue
            if f_flag in flag_combination and '-e' in flag_combination and '-o' in flag_combination:
                continue

            command_flags = list(flag_combination)

            if f_flag in flag_combination:
                command_flags.remove(f_flag)
                command_flags.append(f_flag)

            original_command = ['grep'] + command_flags + [search_string, test_file, test_file_2, test_file]
            original_output = execute_command(original_command)
            if f_flag in flag_combination:
                original_command = ['grep'] + command_flags + [test_file_3, test_file_4]
            original_output = execute_command(original_command)

            my_command = ['./s21_grep'] + command_flags + [search_string, test_file, test_file_2, test_file]
            my_output = execute_command(my_command)
            if f_flag in flag_combination:
                my_command = ['./s21_grep'] + command_flags + [test_file_3, test_file_4]
            my_output = execute_command(my_command)

            # Удаление ANSI-цветовых кодов
            original_output = re.sub(r'\x1b\[[0-9;]*[mK]', '', original_output)
            my_output = re.sub(r'\x1b\[[0-9;]*[mK]', '', my_output)

            if original_output == my_output:
                result = 'SUCCESS'
                success_count += 1
            else:
                result = 'FAIL'
                fail_count += 1

            if f_flag in flag_combination:
                print(f"Flags: {' '.join(flag_combination)}, Result: {result}")
            else:
                print(f"Search String: {search_string}, Flags: {' '.join(flag_combination)}, Result: {result}")

print(f"TOTAL: SUCCESS - {success_count}, FAIL - {fail_count}")








# import subprocess
# import difflib
# import re
# from itertools import combinations

# test_file = 'tests/test.txt'
# test_file_2 = 'tests/test_2.txt'
# test_file_3 = 'tests/pattern.txt'
# test_file_4 = 'tests/result.txt'

# flags = ['-i', '-v', '-c', '-l', '-n', '-h', '-s', '-e', '-f', '-o']
# f_flag = '-f'

# search_strings = ['[Tt]', 'and', '1.[0-9][0-9]', 'were', 'for', 'aboba']

# success_count = 0
# fail_count = 0

# def execute_command(command, use_valgrind=False):
#     if use_valgrind:
#         process = subprocess.Popen(['valgrind', '--leak-check=full'] + command, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
#     else:
#         process = subprocess.Popen(command, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
#     stdout, stderr = process.communicate()
#     return stdout.strip(), stderr.strip()

# for search_string in search_strings:
#     command_flags = []  # перемещаем инициализацию сюда, за пределы цикла по r
#     for r in range(1, 3):
#         for flag_combination in combinations(flags, r):
#             if f_flag in flag_combination and '-c' in flag_combination and '-o' in flag_combination:
#                 continue
#             if f_flag in flag_combination and '-e' in flag_combination and '-o' in flag_combination:
#                 continue
#             command_flags = list(flag_combination)  # сохраняем текущую комбинацию флагов

#             if f_flag in flag_combination:
#                 command_flags.remove(f_flag)
#                 command_flags.append(f_flag)

#             original_command = ['grep'] + command_flags + [search_string, test_file, test_file_2, test_file]
#             original_output, original_valgrind_output = execute_command(['valgrind', '--leak-check=full'] + original_command, use_valgrind=False)
#             if f_flag in flag_combination:
#                 original_command = ['grep'] + command_flags + [test_file_3, test_file_4]
#                 original_output, original_valgrind_output = execute_command(['valgrind', '--leak-check=full'] + original_command, use_valgrind=False)

#             my_command = ['./s21_grep'] + command_flags + [search_string, test_file, test_file_2, test_file]
#             my_output, my_valgrind_output = execute_command(['valgrind', '--leak-check=full'] + my_command, use_valgrind=True)
#             if f_flag in flag_combination:
#                 my_command = ['./s21_grep'] + command_flags + [test_file_3, test_file_4]
#                 my_output, my_valgrind_output = execute_command(['valgrind', '--leak-check=full'] + my_command, use_valgrind=False)

#             original_output = re.sub(r'\x1b\[[0-9;]*[mK]', '', original_output)
#             my_output = re.sub(r'\x1b\[[0-9;]*[mK]', '', my_output)

#             if original_output == my_output and "ERROR SUMMARY: 0 errors" in my_valgrind_output and "no leaks are possible" in my_valgrind_output:
#                 result = 'SUCCESS'
#                 success_count += 1
#             else:
#                 result = 'FAIL'
#                 fail_count += 1
#                 if "ERROR SUMMARY: 0 errors" not in my_valgrind_output or "no leaks are possible" not in my_valgrind_output:
#                     print("My Valgrind output:", my_valgrind_output)
#             if f_flag in flag_combination:
#                     print(f"Flags: {' '.join(flag_combination)}, Result: {result}")
#             else:
#                 print(f"Search String: {search_string}, Flags: {' '.join(command_flags)}, Result: {result}")

# print(f"TOTAL: SUCCESS - {success_count}, FAIL - {fail_count}")