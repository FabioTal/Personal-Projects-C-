#include <unistd.h>
#include <stdlib.h>

int is_space(char c)
{
    return (c == ' ' || c == '\n' || c == '\t');
}

int count_words(char *str)
{
    int i = 0, count = 0;
    while (str[i])
    {
        while (str[i] && is_space(str[i]))
            i++;
        if (str[i] && !is_space(str[i]))
        {
            count++;
            while (str[i] && !is_space(str[i]))
                i++;
        }
    }
    return count;
}

char *copy_word(char *str, int start, int end)
{
    int length = end - start;
    char *word = malloc(sizeof(char) * (length + 1));
    int j = 0;

    if (!word)
        return NULL;
    while (j < length)
    {
        word[j] = str[start + j];
        j++;
    }
    word[j] = '\0';
    return word;
}

char **ft_split(char *str)
{
    int i = 0, j = 0, start;
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

int ft_strlen(char *str)
{
    int i = 0;
    while (str[i])
        i++;
    return i;
}

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
