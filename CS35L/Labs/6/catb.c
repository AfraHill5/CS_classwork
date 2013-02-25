#include <stdio.h>

/* Uses getchar and putchar to copy all the bytes in stdin to stdio */

int main()
{
    int c = getchar();
    while (c != EOF)
    {
        putchar(c);
        c = getchar();
    }
}
