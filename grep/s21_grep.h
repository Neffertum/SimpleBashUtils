#ifndef SRC_GREP_S21_GREP_H_
#define SRC_GREP_S21_GREP_H_

struct flags {
    int e;
    int i;
    int v;
    int c;
    int l;
    int n;
    int h;
    int s;
    int f;
    int o;
};

int output(int argc, char **argv);
int make_magic(struct flags myflags, FILE *file, char *temp, char *filename, int count_file);

#endif  //  SRC_GREP_S21_GREP_H_
