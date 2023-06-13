CC=gcc -Wall -Werror -Wextra -std=c11 -D_GNU_SOURCE
all: s21_grep

s21_grep:
	$(CC) s21_grep.c -o s21_grep

test:
	leaks -atExit -- ./s21_grep -e lala ./tests/sample.txt
	cp ../../materials/linters/CPPLINT.cfg .
	python3 ../../materials/linters/cpplint.py --extensions=c s21_grep.c s21_grep.h

sh:
	sh ./tests/2sample_tests.sh
	sh ./tests/1sample_tests.sh

bigtest:
	sh test_sh/test_grep.sh

clean: 
	rm s21_grep CPPLINT.cfg
