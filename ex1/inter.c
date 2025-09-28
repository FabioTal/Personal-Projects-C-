#include <unistd.h>

// Kontrollon nëse c ekziston në str[0..pos-1]
int fillim(char *str, char c, int pos)
{
    int i = 0;
    while (i < pos)
    {
        if (str[i] == c)
            return 1;
        i++;
    }
    return 0;
}

// Printon karakteret që janë të përbashkëta në s1 dhe s2, pa përsëritje
void inter(char *s1, char *s2)
{
    int i = 0;
    int j;

    while (s1[i])
    {
        if (!fillim(s1, s1[i], i)) // karakteri nuk është përdorur më parë
        {
            j = 0;
            while (s2[j])
            {
                if (s1[i] == s2[j])
                {
                    write(1, &s1[i], 1);
                    break;
                }
                j++;
            }
        }
        i++;
    }
}

int main(int ac, char **av)
{
    if (ac == 3)
        inter(av[1], av[2]);

    write(1, "\n", 1);
    return 0;
}
