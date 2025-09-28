#include <unistd.h>

void inter_or_union(char *s1, char *s2)
{
    unsigned char used[256] = {0};
    int i = 0;

    // Print karakteret nga s1
    while (s1[i])
    {
        unsigned char c = s1[i];
        if (!used[c])
        {
            write(1, &c, 1);
            used[c] = 1;
        }
        i++;
    }

    // Print karakteret nga s2 që nuk janë përdorur më parë
    i = 0;
    while (s2[i])
    {
        unsigned char c = s2[i];
        if (!used[c])
        {
            write(1, &c, 1);
            used[c] = 1;
        }
        i++;
    }

    write(1, "\n", 1);
}

int main(int argc, char **argv)
{
    if (argc == 3)
        inter_or_union(argv[1], argv[2]);
    else
        write(1, "\n", 1);

    return 0;
}
// merr 2 stringje dhe printon karakteret qe gjenden vtm ne 1 string//