
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1

size_t ft_strlen(char *str)
{
    size_t i;

    i = 0;
    if (!str)
        return (0);
    while (str[i])
        i++;
    return(i);
}
int main(void)
{
    char *line;
    int res;

    line = NULL;
    res = ft_strlen(line);
    printf("%d\n", res);
}