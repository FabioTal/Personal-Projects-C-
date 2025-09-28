#include <stdio.h>
char *ft_strrev(char *str)
{
 int i=0;
 int last;
 char temp;
 while (str[i])
 {
    i++;

 }   
 last=i-1;
 i=0;
 while(last>i)
 {
    temp=str[i];
    str[i]=str[last];
    str[last]=temp;
    i++;
    last--;
 }
 return str;
}
int main (void)
{
    char str [17]="Words and Letters";
    printf("Regular :%s",str);
    printf("Reversed :%s",ft_strrev(str));
    return 0;

}