CC = gcc
FLAGS = -Wall -Werror -Wextra --std=c11
LIBS = -lcheck -lsubunit -lm -lgcov
FUNC_FILES_C = *.c 
FUNC_FILES_O = *.o
CHECKFLAGS = $(shell pkg-config --cflags --libs check)
GCOVFLAGS = -fprofile-arcs -ftest-coverage
LIBNAME = s21_decimal.a
GLFLAGS = --coverage
EXCLUDE = --exclude "shift_bits.c" --exclude "unit_tests/*" --exclude "align.c" --exclude "big_decimal.c" --exclude "decimal_func.c"

all: s21_decimal.a

peer: 
	make gcov_open

build_object_files:
	$(CC) $(FLAGS) $(GCOVFLAGS) $(GLFLAGS) -c $(FUNC_FILES_C)

build_library:
	ar rcs $(LIBNAME) $(FUNC_FILES_O)

s21_decimal.a:
	$(CC) $(FLAGS) -c $(FUNC_FILES_C)
	make build_library
	rm -rf *.o

test: all
	$(CC) unit_tests/s21_add_test.c -L. s21_decimal.a $(CHECKFLAGS) $(GLFLAGS) $(GCOVFLAGS) -o s21_add_test
	$(CC) unit_tests/s21_sub_test.c -L. s21_decimal.a $(CHECKFLAGS) $(GLFLAGS) $(GCOVFLAGS) -o s21_sub_test
	$(CC) unit_tests/s21_mul_test.c -L. s21_decimal.a $(CHECKFLAGS) $(GLFLAGS) $(GCOVFLAGS) -o s21_mul_test
	$(CC) unit_tests/s21_div_test.c -L. s21_decimal.a $(CHECKFLAGS) $(GLFLAGS) $(GCOVFLAGS) -o s21_div_test
	$(CC) unit_tests/s21_is_less_test.c -L. s21_decimal.a $(CHECKFLAGS) $(GLFLAGS) $(GCOVFLAGS) -o s21_is_less_test
	$(CC) unit_tests/s21_is_less_or_equal_test.c -L. s21_decimal.a $(CHECKFLAGS) $(GLFLAGS) $(GCOVFLAGS) -o s21_is_less_or_equal_test
	$(CC) unit_tests/s21_is_greater_test.c -L. s21_decimal.a $(CHECKFLAGS) $(GLFLAGS) $(GCOVFLAGS) -o s21_is_greater_test
	$(CC) unit_tests/s21_is_greater_or_equal_test.c -L. s21_decimal.a $(CHECKFLAGS) $(GLFLAGS) $(GCOVFLAGS) -o s21_is_greater_or_equal_test
	$(CC) unit_tests/s21_is_equal_test.c -L. s21_decimal.a $(CHECKFLAGS) $(GLFLAGS) $(GCOVFLAGS) -o s21_is_equal_test
	$(CC) unit_tests/s21_is_not_equal_test.c -L. s21_decimal.a $(CHECKFLAGS) $(GLFLAGS) $(GCOVFLAGS) -o s21_is_not_equal_test
	$(CC) unit_tests/s21_from_int_to_decimal_test.c -L. s21_decimal.a $(CHECKFLAGS) $(GLFLAGS) $(GCOVFLAGS) -o s21_from_int_to_decimal_test
	$(CC) unit_tests/s21_from_float_to_decimal_test.c -L. s21_decimal.a $(CHECKFLAGS) $(GLFLAGS) $(GCOVFLAGS) -o s21_from_float_to_decimal_test
	$(CC) unit_tests/s21_from_decimal_to_int_test.c -L. s21_decimal.a $(CHECKFLAGS) $(GLFLAGS) $(GCOVFLAGS) -o s21_from_decimal_to_int_test
	$(CC) unit_tests/s21_from_decimal_to_float_test.c -L. s21_decimal.a $(CHECKFLAGS) $(GLFLAGS) $(GCOVFLAGS) -o s21_from_decimal_to_float_test
	$(CC) unit_tests/s21_floor_test.c -L. s21_decimal.a $(CHECKFLAGS) $(GLFLAGS) $(GCOVFLAGS) -o s21_floor_test
	$(CC) unit_tests/s21_round_test.c -L. s21_decimal.a $(CHECKFLAGS) $(GLFLAGS) $(GCOVFLAGS) -o s21_round_test
	$(CC) unit_tests/s21_truncate_test.c -L. s21_decimal.a $(CHECKFLAGS) $(GLFLAGS) $(GCOVFLAGS) -o s21_truncate_test
	$(CC) unit_tests/s21_negate_test.c -L. s21_decimal.a $(CHECKFLAGS) $(GLFLAGS) $(GCOVFLAGS) -o s21_negate_test
	make start_tests

start_tests:
	./s21_add_test
	./s21_sub_test
	./s21_mul_test
	./s21_div_test
	./s21_is_less_test
	./s21_is_less_or_equal_test
	./s21_is_greater_test
	./s21_is_greater_or_equal_test
	./s21_is_equal_test
	./s21_is_not_equal_test
	./s21_from_int_to_decimal_test
	./s21_from_float_to_decimal_test
	./s21_from_decimal_to_int_test
	./s21_from_decimal_to_float_test
	./s21_floor_test
	./s21_round_test
	./s21_truncate_test
	./s21_negate_test

gcov_report: clean build_object_files build_library test
	gcov $(FUNC_FILES_C) 
	~/.local/bin/gcovr -r . $(EXCLUDE) --html --html-details -o s21_decimal.html

gcov_open: 
	make gcov_report
	xdg-open s21_decimal.html

clean:
	rm -f *.o
	rm -f *.gcno
	rm -f *.gcov
	rm -f *.gcda
	rm -f *.a
	rm -f *.info
	rm -f *.html
	rm -f *.css
	rm -f s21_*_test

rebuild:
	make clean
	make

del: clean
	rm -f *.c *.h unit_tests/*.c
	rmdir unit_tests