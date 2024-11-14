import subprocess
import difflib
from itertools import combinations

flags = ['-b', '-e', '-E', '-n', '-s', '-t', '-A', '-T']

def execute_command(command):
    result = subprocess.run(command, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
    return result.stdout.strip()

all_combinations = []
for r in range(1, len(flags) + 1):
    all_combinations.extend(combinations(flags, r))

test_file = 'tests/test.txt'
test_file_1 = 'tests/1.txt'
test_file_2 = 'tests/test.txt'
test_file_3 = 'tests/1.txt'

success_count = 0
fail_count = 0

for i, flags_combo in enumerate(all_combinations, 1):

    original_command = ['cat', test_file, test_file_1, test_file_2, test_file_3] + list(flags_combo)
    original_output = execute_command(original_command)

    my_command = ['./s21_cat', test_file, test_file_1, test_file_2, test_file_3] + list(flags_combo)
    my_output = execute_command(my_command)

    if original_output == my_output:
        result = 'SUCCESS'
        success_count += 1
    else:
        result = 'FAIL'
        fail_count += 1
        # print(f"Original output:\n{original_output}")
        # print(f"My output:\n{my_output}")
        # print(f"Difference:\n{[line for line in difflib.unified_diff(original_output, my_output, lineterm='')]}\n")

    print(f"Combination {i}, Flags: {' '.join(flags_combo)}, Result: {result}")

print(f"TOTAL: SUCCESS - {success_count}, FAIL - {fail_count}")




# import subprocess
# import difflib
# from itertools import combinations

# flags = ['-b', '-e', '-E', '-n', '-s', '-t', '-A', '-T']

# def execute_command(command):
#     process = subprocess.Popen(['valgrind', '--leak-check=full'] + command, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
#     stdout, stderr = process.communicate()
#     return stdout.strip(), stderr.strip()

# all_combinations = []
# for r in range(1, len(flags) + 1):
#     all_combinations.extend(combinations(flags, r))

# test_file = 'tests/test.txt'
# test_file_1 = 'tests/1.txt'
# test_file_2 = 'tests/test.txt'
# test_file_3 = 'tests/1.txt'

# success_count = 0
# fail_count = 0

# for i, flags_combo in enumerate(all_combinations, 1):

#     original_command = ['cat', test_file, test_file_1, test_file_2, test_file_3] + list(flags_combo)
#     original_output, original_valgrind_output = execute_command(original_command)

#     my_command = ['./s21_cat', test_file, test_file_1, test_file_2, test_file_3] + list(flags_combo)
#     my_output, my_valgrind_output = execute_command(my_command)

#     if original_output == my_output and "ERROR SUMMARY: 0 errors" in my_valgrind_output and "no leaks are possible" in my_valgrind_output:
#         result = 'SUCCESS'
#         success_count += 1
#     else:
#         result = 'FAIL'
#         fail_count += 1
#         if "ERROR SUMMARY: 0 errors" not in my_valgrind_output or "no leaks are possible" not in my_valgrind_output:
#             print("My Valgrind output:", my_valgrind_output)

#     print(f"Combination {i}, Flags: {' '.join(flags_combo)}, Result: {result}")

# print(f"TOTAL: SUCCESS - {success_count}, FAIL - {fail_count}")

