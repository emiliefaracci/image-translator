#include<stdio.h>
#include<ctype.h>

//reader tool, taken from class notes by professor Shaw:

int main()
{
    int c = getc(stdin);
    int i = 0;
    while (c != EOF) {
        fprintf(stdout, "%5d\t%3d\t%c\n", i, c, isgraph(c)?c:'.');
        c = getc(stdin);
        ++i;
    }
}
