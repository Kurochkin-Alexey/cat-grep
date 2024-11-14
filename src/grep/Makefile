CC = gcc -std=c11
CFLAGS = -Wall -Wextra  -Werror
SOURCES = s21_grep.c s21_grep_utils.c
OBJECTS = $(SOURCES:.c=.o)

s21_grep: $(OBJECTS)
	$(CC) $(CFLAGS) -o s21_grep $(OBJECTS)

clean:
	rm -rf s21_grep $(OBJECTS)