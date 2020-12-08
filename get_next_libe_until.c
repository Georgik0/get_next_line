/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_libe_until.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skitsch <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 21:02:01 by skitsch           #+#    #+#             */
/*   Updated: 2020/11/27 21:02:04 by skitsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t		ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t i;
	size_t src_size;

	i = 0;
	src_size = 0;
	if (!dst && !src)
		return (0);
	while (src[src_size] != '\0')
		src_size++;
	if (src_size == 0)
		return (0);
	while (i < size - 1 && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	if (size != 0)
		dst[i] = '\0';
	return (src_size);
}

char	*ft_substr_gnl(char	*buf)
{
	char	*line;
	int		size;

	size = 0;
	while (buf[size] != '\0')
		size++;
	if (!(line = (char *)malloc((size + 1) * sizeof(char))))
		return (NULL);
	line[size--] = '\0';
	while (size >= 0)
	{
		line[size] = buf[size];
		size--;
	}
	return (line);
}

char	*ft_strchr(const char *str, int ch)
{
	int i;

	i = 0;
	while (str[i] != ch && str[i] != '\0')
	{
		i++;
	}
	if (str[i] == ch)
		return (char*)(str + i);
	return (NULL);
}

char	*ft_calloc(size_t count, size_t size)
{
	char	*out;
	int		i;

	i = 0;
	if (!(out = (char *)malloc(count * size)))
		return (NULL);
	while (i < count * size)
		out[i] = '\0';
	return (out);
}

char		*ft_strjoin_gnl(char const *s1, char const *s2)
{
	char	*out;
	int		size1;
	int		size2;

	if (!s1 || !s2)
		return (NULL);
	size2 = 0;
	while (s2[size2] != '\0')
		size2++;
	// if (!s1 && s2)
	// {
	// 	if (!(out = ft_strlcpy_gnl(s1, s2, size2 + 1)))
	// 		return (NULL);
	// 	return (out);
	// }
	size1 = 0;
	while (s1[size1] != '\0')
		size1++;
	if (!(out = (char *)malloc((size1 + size2 + 1) * sizeof(char))))
		return (NULL);
	out[size2 + size1] = '\0';
	if (size1 == 0)
		ft_strlcpy(out, s1, size1);
	else
		ft_strlcpy(out, s1, size1 + 1);
	if (size2 != 0)
		size2++;
	ft_strlcpy(out + size1, s2, size2);
	return (out);
}
