#include <stdio.h>
#include <string.h>
#include "s21_cat.h"

int main(int argc, char *argv[]) {
    if (output(argc, argv) == 1) {
        printf("ERROR");
    }
    return 0;
}

int output(int argc, char **argv) {
    int flag = 1;
    int have_flag = 0;
    struct flags myflags = {0, 0, 0, 0, 0, 0, 0};
    FILE *file;
    if (argc > 1) {
        flag = 0;
        for (int i = 1; i < argc; i++) {
            if (argv[i][0] == '-') {
                for (size_t r = 1; r < strlen(argv[i]); r++) {
                    if (argv[i][r] == 'b') {
                        myflags.b = 1;
                    }
                    if (argv[i][r] == 'e') {
                        myflags.e = 1;
                    }
                    if (argv[i][r] == 'n') {
                        myflags.n = 1;
                    }
                    if (argv[i][r] == 's') {
                        myflags.s = 1;
                    }
                    if (argv[i][r] == 't') {
                        myflags.t = 1;
                    }
                    if (argv[i][r] == 'E') {
                        myflags.e_big = 1;
                    }
                    if (argv[i][r] == 'T') {
                        myflags.t_big = 1;
                    }
                    if (argv[i][r] != 'b' && argv[i][r] != 'e' &&
                    argv[i][r] != 'n' && argv[i][r] != 's' &&
                    argv[i][r] != 't' && argv[i][r] != 'E' &&
                    argv[i][r] != 'T') {
                        printf("cat: illegal option -- %c\nusage: cat [-benstuv] [file ...]\n", argv[i][r]);
                        have_flag = 1;
                    }
                }
            }
        }
    }
    if (flag == 0 && have_flag == 0) {
        for (int i = 1; i < argc; i++) {
            if (argv[i][0] != '-') {
                file = fopen(argv[i], "r");
                if (!file) {
                    printf("cat: %s: No such file or directory\n", argv[i]);
                } else {
                    make_magic(myflags, file);
                    fclose(file);
                }
            }
        }
    }
    return flag;
}

int make_magic(struct flags myflags, FILE *file) {
    int c = fgetc(file);
    int prev_c = c;
    int count_str = 1;
    int s_flag = 0;
    int t_flag = 0;
    int big_flag = 0;

    for (int i = 0; c != EOF; i++) {
        if (myflags.b == 1) {
            if ((i == 0 && c != '\n') || (prev_c == '\n' && c != '\n')) {
                printf("%6d\t", count_str);
                count_str++;
            }
        }
        if (myflags.n == 1 && myflags.b != 1) {
            if ((i == 0 || prev_c == '\n') && s_flag == 0) {
                printf("%6d\t", count_str);
                count_str++;
            }
        }
        if (myflags.e == 1 && s_flag == 0) {
            if (c == '\n' && s_flag == 0) {
                printf("%c", '$');
            }
            big_flag = 1;
        }
        if (myflags.e_big == 1) {
            if (c == '\n' && s_flag == 0) {
                printf("%c", '$');
            }
            big_flag = 2;
        }
        if (myflags.s == 1) {
            if (prev_c == '\n' && c == '\n' && s_flag == 0) {
                printf("\n");
                s_flag = 1;
            } else if (c != '\n') {
                if (myflags.n == 1 && s_flag == 1 && myflags.b != 1) {
                    printf("%6d\t", count_str);
                    count_str++;
                }
                s_flag = 0;
            }
        }
        if (myflags.t == 1) {
            if (c == '\t') {
                printf("^I");
                t_flag = 1;
            } else {
                t_flag = 0;
            }
            big_flag = 1;
        }
        if (myflags.t_big == 1) {
            if (c == '\t') {
                printf("^I");
                t_flag = 1;
            } else {
                t_flag = 0;
            }
            big_flag = 2;
        }

        if (s_flag == 0 && t_flag == 0) {
            if (((0 <= c && c < 9) || (10 < c && c < 32)) && big_flag == 1) {
                printf("^%c", c + 64);
            } else if (c > 126 && big_flag == 1) {
                printf("^%c", c - 64);
            } else if (((c > 8 && c < 11) || (c > 31 && c < 127)) && big_flag == 2) {
                printf("%c", c);
            } else if (big_flag == 0 || big_flag == 1) {
                printf("%c", c);
            }
        }
        prev_c = c;
        c = fgetc(file);
    }
    return 0;
}
