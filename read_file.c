/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read_file.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: epanholz <epanholz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/03 17:48:19 by epanholz      #+#    #+#                 */
/*   Updated: 2020/09/10 12:35:15 by pani_zino     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		ft_strlen(char *s)
{
	int i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t		i;
	char		*d;
	const char	*s;

	if (!dst && !src)
		return (dst);
	d = dst;
	s = src;
	i = 0;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return ((void *)dst);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		len1;
	int		len2;
	char	*new;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	if (!s1)
	{
		new = (char*)malloc((len2 + 1) * sizeof(char));
		if (new == NULL)
			ft_error(MALLOC);
		ft_memcpy(new, s2, len2 + 1);
		return (new);
	}
	new = (char*)malloc((len1 + len2 + 1) * sizeof(char));
	if (new == NULL)
		ft_error(MALLOC);
	ft_memcpy(new, s1, len1);
	ft_memcpy(new + len1, s2, len2 + 1);
	free(s1);
	return (new);
}

char	*read_file(int fd, char *temp)
{
	char	buff[1024 + 1];
	int		bytes_read;

	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buff, 1024);
		if (bytes_read < 0)
			ft_error(READ);
		buff[bytes_read] = '\0';
		temp = ft_strjoin(temp, buff);
	}
	return (temp);
}
