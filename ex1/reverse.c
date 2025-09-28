#include <unistd.h>
char *ft_re_print( char *str)
{
    int i=0;
    int last;
    while(str[i])
    {
        i++;
    }
    last=i-1;
    while(last>=0)
    {
        write (1, &str[last],1);
        last--;

    }
    write(1,"\n",1);
    return (str);
}
int main(void)
{
    char *text = "albania";
    ft_re_print(text);

    return 0;
}