CC=gcc -Wall -Werror -Wextra -std=c11

all: s21_cat

s21_cat:
	$(CC) s21_cat.c -o s21_cat

test:
	leaks -atExit -- ./s21_cat -b ./tests/sample.txt
	cp ../../materials/linters/CPPLINT.cfg .
	python3 ../../materials/linters/cpplint.py --extensions=c s21_cat.c s21_cat.h

sh:
	sh ./tests/asci_tests.sh
	sh ./tests/sample_tests.sh

bigtest:
	sh test_sh/test_cat.sh

clean: 
	rm s21_cat CPPLINT.cfg
