CC = gcc -std=c11
CFLAGS = -Wall -Werror -Wextra
SOURCES = s21_cat.c s21_cat_utils.c
OBJECTS = $(SOURCES:.c=.o)

s21_cat: $(OBJECTS)
	$(CC) $(CFLAGS) -o s21_cat $(OBJECTS)

clean:
	rm -rf s21_cat $(OBJECTS)