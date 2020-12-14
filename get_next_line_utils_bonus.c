/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skitsch <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 19:51:38 by skitsch           #+#    #+#             */
/*   Updated: 2020/12/13 19:51:40 by skitsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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

char	*ft_substr_gnl(char	*buf)
{
	char	*line;
	int		size;

	size = 0;
	if (!buf)
	{
		if (!(line = (char *)ft_calloc(1, 1)))
			return (NULL);
		return (line);
	}
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

char	*ft_calloc(size_t count, size_t size)
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

char		*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*out;
	int		size1;
	int		size2;

	size2 = 0;
	if (s2)
	{
		while (s2[size2] != '\0')
			size2++;
	}
	size1 = 0;
	if (s1)
	{
		while (s1[size1] != '\0')
			size1++;
	}
	if (!(out = (char *)ft_calloc(size1 + size2 + 1, sizeof(char))))
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

void	delete_list(t_list *list_open, t_list **start_list)
{
	t_list	*temp;
	t_list	*out;

	temp = *start_list;
	// if (!*start_list)
	// 	return ;
	// while (temp && temp->next)
	// {
	// 	if (temp->next == list_open)
	// 	{
	// 		out = temp->next;
	// 		temp->next = out->next;
	// 	}
	// 	temp = temp->next;
	// }
	if (temp != list_open)
	{
		while (temp && temp->next != list_open)
			temp = temp->next;
		out = temp->next;
		temp->next = out->next;
	}
	else
	{
		out = *start_list;
		*start_list = NULL;
	}
	free(out->buf);
	free(out->reminfer);
	// free(out->next);
	free(out);
	out = NULL;
}

int		check_reminder(t_list **list_open, t_list **start_list, char **line)
{
	char	*temp;
	char	*save;

	if ((temp = ft_strchr((*list_open)->reminfer, '\n')) != NULL)
	{
		*temp = '\0';
		save = *line;
		if (!(*line = ft_strjoin_gnl(save, (*list_open)->reminfer)))
		{
			delete_list(*list_open, start_list);
			return (-1);
		}
		free(save);
		save = (*list_open)->reminfer;
		if (!((*list_open)->reminfer = ft_substr_gnl(temp + 1)))
		{
			delete_list(*list_open, start_list);
			return (-1);
		}
		free(save);
		save = NULL;
		free((*list_open)->buf);
		(*list_open)->buf = NULL;
		return (1); // a line has been read
	}
	temp = *line;
	if (!(*line = ft_strjoin_gnl(temp, (*list_open)->reminfer)))
	{
		delete_list(*list_open, start_list);
		return (-1);
	}
	free(temp);
	temp = NULL;
	if ((*list_open)->eof_flag == 0)
	{
		delete_list(*list_open, start_list);
		return (0);
	}
	return (2); // нужно читать дальше
}
