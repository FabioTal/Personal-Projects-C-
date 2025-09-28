#include <unistd.h>
int main (int argc , char **argv)
{
    if(argc!=3)
    {
        write(1, "\n" ,1);
        return 0;
    }
    char used[256]={0};
    int i=0;
    while (argv[1][i])
    {
        unsigned char c=argv[1][i];
        if(!used[c])
        {
            write (1, &c ,1);
            used[c]=1;
        }
        i++;
    }
    i=0;
    while (argv[2][i])
    {
        unsigned char c=argv[2][ i];
        if(!used[c])
        {
            write(1, &c ,1);
            used[c]=1;
        }
        i++;
    }
    write(1 ,"\n",1);
    return 0;
}