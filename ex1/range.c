#include <stdlib.h>
#include <stdio.h>

int *ft_range(int start, int end)
{
    int size = abs(end - start) + 1;
    int *tab = malloc(sizeof(int) * size);
    if (!tab)
        return NULL;

    for (int i = 0; i < size; i++)
    {
        tab[i] = (start <= end) ? start + i : start - i;
    }
    return tab;
}

int main(void)
{
    int start = 0;
    int end = -3;
    int size = abs(end - start) + 1;
    int *tab = ft_range(start, end);

    if (tab)
    {
        for (int i = 0; i < size; i++)
            printf("%d\n", tab[i]);
        free(tab);
    }
}
