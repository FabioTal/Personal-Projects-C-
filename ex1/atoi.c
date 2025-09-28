#include <unistd.h>
#include <stdio.h>

int ft_atoi(char *str)
{
    int sum = 0;
    int i = 0;
    int sign = 1;

    // Skip whitespaces dhe tab/newline
    while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
        i++;

    // Kontrollo shenjën
    if (str[i] == '-')
    {
        sign = -1;
        i++;
    }
    else if (str[i] == '+')
    {
        i++;
    }

    // Shndërrimi i shifrave
    while (str[i] >= '0' && str[i] <= '9')
    {
        sum = (sum * 10) + (str[i] - '0');
        i++;
    }

    return (sign * sum);
}

int main()
{
    char *n = "-1234ab567";

    printf("Me atoi:    %d\n", atoi(n));     // libraria standarde
    printf("Me ft_atoi: %d\n", ft_atoi(n));  // funksioni yt
    return 0;
}
