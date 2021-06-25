/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casalaza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 19:55:25 by casalaza          #+#    #+#             */
/*   Updated: 2021/06/25 19:55:33 by casalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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


int is_there_newline(char *remainder)
{
    int i;

    i = 0;
    if (!remainder)
        return(0);
    while (remainder[i])
    {
        if (remainder[i] == '\n')
            return(1);
    }
    return(0); 
}




char *new_line(char *remainder)
{
    char *res;
    int i;

    i = 0;
    if (remainder == NULL)
        return(0);
    while (remainder[i] && remainder[i] != '\n')
        i++;
    res = malloc(sizeof(char) * (i + 1));
    if (!res)
        return(0);
    i = 0;
    while (remainder[i] && remainder[i] != '\n')
    {
        res[i] = remainder[i];
    }
    res[i] = '\0';
    return(res);
}

char *new_remainder(char *remainder)
{
    int i;
    char *res;
    int j;

    j = 0;
    i = 0;
    if (remainder == NULL)
        return(0);
    while (remainder[i] && remainder[i] != '\n')
        i++;
    if (remainder[i] == '\0')
    {
        free(remainder);
        return(0);
    }
    res = malloc(sizeof(char) * (ft_strlen(remainder) - 1 - i));
    if (!res)
        return(0);
    while (remainder[i + 1])
        res[j++] = remainder[i++];
    free(remainder);
    res[j] = '\0';
    return(res);
}

static void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*s;
	char	*d;
	size_t	i;

	s = (char *)src;
	d = (char *)dst;
	i = 0;
	if (!d && !s)
		return (NULL);
	if (len == 0)
		return (d);
	if (d > s)
	{
		while (len-- > 0)
			d[len] = s[len];
	}
	else
	{
		while (i < len)
		{
			d[i] = s[i];
			i++;
		}
	}
	return (dst);
}

char	*ft_join(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	size_t	st_len;
	char	*rtn;

	if (!s1 && !s2)
		return (0);
	s1_len = ft_strlen((char *)s1);
	s2_len = ft_strlen((char *)s2);
	st_len = s1_len + s2_len + 1;
	rtn = malloc(sizeof(char) * st_len);
	if (!rtn)
		return (0);
	ft_memmove(rtn, s1, s1_len);
	ft_memmove(rtn + s1_len, s2, s2_len);
	rtn[st_len - 1] = '\0';
	free((char *)s1);
	return (rtn);
}

int get_next_line(int fd, char **line)
{
    int ret;
    static char *remainder;
    char *buffer;

    ret = BUFFER_SIZE;
    if (fd < 0 || !line || BUFFER_SIZE <= 0)
		return (-1);
    buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
    if (!buffer)
        return(-1);
    while (is_there_newline(remainder) != 1 && ret != 0)
    {
        printf("%s\n", "were here");
        ret = read(fd, buffer, BUFFER_SIZE);
        if (ret == -1)
            return(-1);
        buffer[ret] = '\0';
        remainder = ft_join(remainder, buffer);
    }
    free(buffer);
    *line = new_line(remainder);
    remainder = new_remainder(remainder);
    return((ret > 0) ? 1 : 0);
}

int main(void)
{
    int fd;
    char *line;

    fd = open("test.txt", O_RDONLY);
    get_next_line(fd, &line);
    printf("line:%s\n", line);
    return(0);
}
