#include <unistd.h>

int main(int ac, char **av)
{
    int i;

    if (ac == 2)
    {
        // Gjej fundin e stringut
        i = 0;
        while (av[1][i])
            i++;
        i--; // i = indeksi i fundit

        // Lëviz mbrapsht për të hequr hapësirat në fund
        while (i >= 0 && (av[1][i] == ' ' || av[1][i] == '\t'))
            i--;

        // Ruaj fundin e fjalës së fundit
        int end = i;

        // Lëviz mbrapsht deri tek fillimi i fjalës
        while (i >= 0 && av[1][i] != ' ' && av[1][i] != '\t')
            i--;

        // Print fjalën e fundit
        int start = i + 1;
        while (start <= end)
        {
            write(1, &av[1][start], 1);
            start++;
        }
    }

    write(1, "\n", 1);
    return 0;
}
