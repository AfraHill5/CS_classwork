#include <unistd.h>

int main()
{
    char buf[1];
    int inFileNum = fileno(stdin);
    int outFileNum = fileno(stdout);
    while (read(inFileNum, buf, 1) > 0) /*negative #s are errors */
    {
        write(outFileNum, buf, 1);
    }
}
