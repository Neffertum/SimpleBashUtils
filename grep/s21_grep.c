#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>
#include "s21_grep.h"

int main(int argc, char *argv[]) {
    if (output(argc, argv) == 1) {
        printf("ERROR\n");
    }
    return 0;
}

int output(int argc, char **argv) {
    int flag = 1;
    int have_flag = 0;
    struct flags myflags;
    myflags.e = myflags.i = myflags.v = myflags.c = myflags.l =
    myflags.n = myflags.h = myflags.s = myflags.f = myflags.o = 0;
    FILE *file;
    char temp[256];
    int temp_place;
    int start = 0;
    if (argc > 2) {
        flag = 0;
        for (int i = 1; i < argc; i++) {
            if (argv[i][0] == '-') {
                have_flag++;
                for (size_t r = 1; r < strlen(argv[i]); r++) {
                    if (argv[i][r] == 'e') {
                        myflags.e = 1;
                    }
                    if (argv[i][r] == 'i') {
                        myflags.i = 1;
                    }
                    if (argv[i][r] == 'v') {
                        myflags.v = 1;
                    }
                    if (argv[i][r] == 'c') {
                        myflags.c = 1;
                    }
                    if (argv[i][r] == 'l') {
                        myflags.l = 1;
                    }
                    if (argv[i][r] == 'n') {
                        myflags.n = 1;
                    }
                    if (argv[i][r] == 'h') {
                        myflags.h = 1;
                    }
                    if (argv[i][r] == 's') {
                        myflags.s = 1;
                    }
                    if (argv[i][r] == 'f') {
                        myflags.f = 1;
                        FILE *f_file = fopen(argv[i + 1], "r");
                        if (!f_file) {
                            printf("grep: %s: No such file or directory", argv[i + 1]);
                            have_flag = -1;
                            break;
                        } else {
                            temp_place = i + 1;
                            char c = getc(f_file);
                            int t;
                            for (t = 0; c != EOF; t++) {
                                temp[t] = c;
                                c = getc(f_file);
                            }
                            fclose(f_file);
                            temp[t] = '\0';
                        }
                    }
                    if (argv[i][r] == 'o') {
                        myflags.o = 1;
                    }
                    if (argv[i][r] != 'e' && argv[i][r] != 'i' &&
                    argv[i][r] != 'v' && argv[i][r] != 'c' &&
                    argv[i][r] != 'l' && argv[i][r] != 'n' &&
                    argv[i][r] != 'h' && argv[i][r] != 's' &&
                    argv[i][r] != 'f' && argv[i][r] != 'o') {
                        have_flag = -1;
                        break;
                    }
                }
            }
        }
    }
    if (have_flag == -1 && myflags.f != 1) {
        if (myflags.s != 1) {
            printf("grep: %s: No such file or directory", argv[2]);
        }
    } else if (myflags.f != 1) {
        for (int i = 1; i < argc; i++) {
            if (((have_flag == 0) || (have_flag > 0 && start == 1)) &&
            argv[i][0] != '-' && myflags.f != 1) {
                size_t t = 0;
                for ( ; t < strlen(argv[i]); t++) {
                    temp[t] = argv[i][t];
                }
                temp[t] = '\0';
                temp_place = i;
                break;
            }
            if (argv[i][0] == '-') start = 1;
        }
    }
    int count_file = 0;
    if (flag == 0 && have_flag != -1) {
        if (argc - have_flag - 2 > 1) {
            count_file = 1;
        }
        for (int i = 1; i < argc; i++) {
            if (argv[i][0] != '-' && i != temp_place) {
                file = fopen(argv[i], "r");
                if (!file) {
                    if (myflags.s != 1) {
                        printf("grep: %s: No such file or directory\n", argv[i]);
                    }
                } else {
                    make_magic(myflags, file, temp, argv[i], count_file);
                    fclose(file);
                }
            }
        }
    }
    return flag;
}

int make_magic(struct flags myflags, FILE *file, char *temp, char *filename, int count_file) {
    int find_flag = 1;
    int success_flag = 0;
    int count_str = 1;
    int err = 1;
    regex_t re[1];

    size_t t_size = 0;
    char *str = NULL;
    regmatch_t o_flag;
    size_t step = 0;
    int for_v = 1;

    if (myflags.i == 1) {
        err = regcomp(re, temp, REG_ICASE);
    } else {
        err = regcomp(re, temp, 0);
    }

    if (err == 0) {
        while (getline(&str, &t_size, file) != -1) {
            if (myflags.o == 1 && myflags.v != 1 &&
            myflags.c != 1 && myflags.l != 1) {
                while (regexec(re, str + step, 1, &o_flag, 0) == 0) {
                    if (count_file == 1 && myflags.h != 1) {
                        printf("%s:", filename);
                    }
                    if (myflags.n == 1 && step == 0) printf("%d:", count_str);
                    for (int i = 0; i < o_flag.rm_eo - o_flag.rm_so; i++) {
                        printf("%c", str[o_flag.rm_so + i + step]);
                    }
                    printf("\n");
                    step += o_flag.rm_eo;
                }
            } else {
                find_flag = regexec(re, str, 0, NULL, 0);
                if ((find_flag == 0 && myflags.v != 1) ||
                (find_flag != 0 && myflags.v == 1)) {
                    success_flag++;
                    if (str[strlen(str) - 1] == '\n') {
                        for_v = 1;
                    } else {
                        for_v = 0;
                    }
                }
            }

            if ((myflags.o != 1 || (myflags.o == 1 && myflags.v == 1))
            && myflags.l != 1 && myflags.c != 1) {
                if ((myflags.v == 1 && find_flag != 0) ||
                (myflags.v != 1 && find_flag == 0)) {
                    if (myflags.h != 1 && count_file == 1) {
                        printf("%s:", filename);
                    }
                    if (myflags.n == 1) {
                        printf("%d:", count_str);
                    }
                    printf("%s", str);
                }
            }

            count_str++;
            step = 0;
        }
        if (myflags.c == 1) {
            if (count_file == 1 && myflags.h != 1) {
                printf("%s:", filename);
            }
            if (myflags.l == 1) {
                if (success_flag > 0) {
                    printf("1\n");
                } else {
                    printf("0\n");
                }
            } else {
                printf("%d\n", success_flag);
            }
        }
        if (myflags.l == 1) {
            if (success_flag > 0) {
                printf("%s\n", filename);
            }
        }
    }

    if (for_v == 0 && myflags.c != 1 && myflags.l != 1) {
        printf("\n");
    }
    free(str);
    regfree(re);
    return 0;
}
