#include <stdlib.h>
#include <unistd.h>

// Kontrollon nëse karakteri është hapësirë
int is_space(char c)
{
    return (c == ' ' || c == '\t' || c == '\n');
}

// Numëron fjalët në string
int count_words(char *str)
{
    int i = 0;
    int count = 0;

    while (str[i])
    {
        while (str[i] && is_space(str[i]))
            i++;
        if (str[i])
        {
            count++;
            while (str[i] && !is_space(str[i]))
                i++;
        }
    }
    return count;
}

// Kopjon një fjalë nga [start..end)
char *copy_word(char *str, int start, int end)
{
    int len = end - start;
    char *word = malloc(len + 1);
    int j = 0;

    if (!word)
        return NULL;
    while (j < len)
    {
        word[j] = str[start + j];
        j++;
    }
    word[j] = '\0';
    return word;
}

// Funksioni kryesor split
char **ft_split(char *str)
{
    int i = 0, start, j = 0;
    int words = count_words(str);
    char **result = malloc(sizeof(char *) * (words + 1));

    if (!result)
        return NULL;
    while (str[i])
    {
        while (str[i] && is_space(str[i]))
            i++;
        start = i;
        while (str[i] && !is_space(str[i]))
            i++;
        if (i > start)
            result[j++] = copy_word(str, start, i);
    }
    result[j] = NULL;
    return result;
}

// strlen custom
int ft_strlen(char *s)
{
    int i = 0;
    while (s[i])
        i++;
    return i;
}

// Testim
int main(void)
{
    char str[] = " ksafknfksdmfdsp\n\n\tsdamdkamdk\ndsadad";
    char **words = ft_split(str);
    int i = 0;

    while (words[i])
    {
        write(1, words[i], ft_strlen(words[i]));
        write(1, "\n", 1);
        free(words[i]);
        i++;
    }
    free(words);
    return 0;
}
