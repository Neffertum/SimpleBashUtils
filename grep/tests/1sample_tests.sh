#!/bin/bash

grep -e t ./tests/sample.txt > ./tests/grep_tests.txt
./s21_grep -e t ./tests/sample.txt > ./tests/s21_grep_tests.txt

cmp ./tests/grep_tests.txt ./tests/s21_grep_tests.txt && echo -e YES || echo -e NO


grep -i T ./tests/sample.txt ./tests/sample.txt > ./tests/grep_tests.txt
./s21_grep -i T ./tests/sample.txt ./tests/sample.txt > ./tests/s21_grep_tests.txt

cmp ./tests/grep_tests.txt ./tests/s21_grep_tests.txt && echo -i YES || echo -i NO


grep -v t ./tests/sample.txt > ./tests/grep_tests.txt
./s21_grep -v t ./tests/sample.txt > ./tests/s21_grep_tests.txt

cmp ./tests/grep_tests.txt ./tests/s21_grep_tests.txt && echo -v YES || echo -v NO


grep -c t ./tests/sample.txt > ./tests/grep_tests.txt
./s21_grep -c t ./tests/sample.txt > ./tests/s21_grep_tests.txt

cmp ./tests/grep_tests.txt ./tests/s21_grep_tests.txt && echo -c YES || echo -c NO


grep -l t ./tests/sample.txt > ./tests/grep_tests.txt
./s21_grep -l t ./tests/sample.txt > ./tests/s21_grep_tests.txt

cmp ./tests/grep_tests.txt ./tests/s21_grep_tests.txt && echo -l YES || echo -l NO


grep -n t ./tests/sample.txt > ./tests/grep_tests.txt
./s21_grep -n t ./tests/sample.txt > ./tests/s21_grep_tests.txt

cmp ./tests/grep_tests.txt ./tests/s21_grep_tests.txt && echo -n YES || echo -n NO


grep -h t ./tests/sample.txt > ./tests/grep_tests.txt
./s21_grep -h t ./tests/sample.txt > ./tests/s21_grep_tests.txt

cmp ./tests/grep_tests.txt ./tests/s21_grep_tests.txt && echo -h YES || echo -h NO


grep -s t ./tests/sample.txt > ./tests/grep_tests.txt tey
./s21_grep -s t ./tests/sample.txt > ./tests/s21_grep_tests.txt tey

cmp ./tests/grep_tests.txt ./tests/s21_grep_tests.txt && echo -s YES || echo -s NO

grep -f ./tests/f_file.txt ./tests/sample.txt > ./tests/grep_tests.txt
./s21_grep -f ./tests/f_file.txt ./tests/sample.txt > ./tests/s21_grep_tests.txt

cmp ./tests/grep_tests.txt ./tests/s21_grep_tests.txt && echo -f file YES || echo -f file NO

grep -o t ./tests/sample.txt > ./tests/grep_tests.txt
./s21_grep -o t ./tests/sample.txt > ./tests/s21_grep_tests.txt

cmp ./tests/grep_tests.txt ./tests/s21_grep_tests.txt && echo -o YES || echo -o NO

grep -iv T ./tests/sample.txt > ./tests/grep_tests.txt
./s21_grep -iv T ./tests/sample.txt > ./tests/s21_grep_tests.txt

cmp ./tests/grep_tests.txt ./tests/s21_grep_tests.txt && echo -iv YES || echo -iv NO

grep -in T ./tests/sample.txt > ./tests/grep_tests.txt
./s21_grep -in T ./tests/sample.txt > ./tests/s21_grep_tests.txt

cmp ./tests/grep_tests.txt ./tests/s21_grep_tests.txt && echo -in YES || echo -in NO

echo nofile grep:
grep lala mnb.txt ./tests/sample.txt

echo nofile s21_grep:
./s21_grep lala mnb.txt ./tests/sample.txt