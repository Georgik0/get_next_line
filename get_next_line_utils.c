/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skitsch <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 21:18:17 by skitsch           #+#    #+#             */
/*   Updated: 2020/12/15 21:18:24 by skitsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t		ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t i;
	size_t src_size;

	i = 0;
	src_size = 0;
	if ((!dst && !src))
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

char		*ft_strchr(const char *str, int ch)
{
	int i;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i] != ch && str[i] != '\0')
	{
		i++;
	}
	if (str[i] == ch)
		return (char*)(str + i);
	return (NULL);
}

char		*ft_calloc(size_t count, size_t size)
{
	char		*out;
	size_t		i;

	i = 0;
	if (!(out = (char *)malloc(count * size)))
		return (NULL);
	while (i < count * size)
	{
		out[i] = '\0';
		i++;
	}
	return (out);
}

char		*fsjoin(char *s1, char *s2, t_list *lop,
			t_list **start_list)
{
	char	*out;
	int		size1;
	int		size2;

	size2 = 0;
	while (s2 && s2[size2] != '\0')
		size2++;
	size1 = 0;
	while (s1[size1] != '\0')
		size1++;
	if (!(out = (char *)ft_calloc(size1 + size2 + 1, sizeof(char))))
	{
		delete_list(lop, start_list);
		return (NULL);
	}
	out[size2 + size1] = '\0';
	if (size1 == 0)
		ft_strlcpy(out, s1, size1);
	else
		ft_strlcpy(out, s1, size1 + 1);
	if (size2 != 0)
		size2++;
	s2 ? (void)ft_strlcpy(out + size1, s2, size2) : NULL;
	return (out);
}

int			check_reminder(t_list **lop, t_list **start_list, char **line,
			char *temp)
{
	char	*save;

	if ((temp = ft_strchr((*lop)->reminfer, '\n')) != NULL)
	{
		*temp = '\0';
		save = *line;
		if (!(*line = fsjoin(save, (*lop)->reminfer,
		*lop, start_list)))
			return (-1);
		free(save);
		save = (*lop)->reminfer;
		if (!((*lop)->reminfer = fsjoin(temp + 1, NULL, *lop, start_list)))
			return (-1);
		free(save);
		free((*lop)->buf);
		(*lop)->buf = NULL;
		return (1);
	}
	temp = *line;
	if (!(*line = fsjoin(temp, (*lop)->reminfer, *lop, start_list)))
		return (-1);
	free(temp);
	if ((*lop)->eof_flag == 0)
		return (delete_list(*lop, start_list));
	return (2);
}
