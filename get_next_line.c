/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skitsch <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 17:26:13 by skitsch           #+#    #+#             */
/*   Updated: 2020/11/27 17:26:51 by skitsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_list	*search_fd(t_list *start, int descriptor)
{
	if (!start)
	{
		if (!(start = (t_list *)malloc(sizeof(t_list))))
			return (NULL);
		start->descriptor = descriptor;
		start->next = NULL;
		if (!(start->reminfer = (char *)ft_calloc(1, 1)))
		{
			free(start);
			return (NULL);
		}
		start->eof_flag = 1;
		return (start);
	}
	while (descriptor != start->descriptor)
	{
		if ((start = start->next) == NULL)
		{
			if (!(start = (t_list *)malloc(sizeof(t_list))))
				return (NULL);
			start->next = NULL;
			start->descriptor = descriptor;
			if (!(start->reminfer = ft_calloc(1, 1)))
				return (NULL);
			start->eof_flag = 1;
			return (start);
		}
		if (start->descriptor == descriptor)
			return (start);
	}
	return (start);
}

int		get_next_line(int fd, char **line)
{
	static t_list		*start_list;
	t_list				*list_open;
	char				*temp;
	int					check_out;
	// int					get_read;

	if (!line || fd < 0 || BUFFER_SIZE <= 0)
		return (-1);
	if (start_list == NULL) // значит лист пуст, нужно создать первый элемент
	{
		if (!(start_list = search_fd(NULL, fd)))
			return (-1);
		list_open = start_list;
	}
	else // значит что-то уже читается => можно искать необходимый элемент листа
	{
		if (!(list_open = search_fd(start_list, fd)))
			return (-1);
	}
	if (!(list_open->buf = (char *)ft_calloc(1 + BUFFER_SIZE, sizeof(char))))
	{
		delete_list(list_open, start_list);
		return (-1);
	}
	if (!(*line = ft_calloc(1, 1)))
	{
		delete_list(list_open, start_list);
		return (-1);
	}
	if ((check_out = check_reminder(list_open, start_list, line)) != 2)
		return (check_out);
	while (ft_strchr(list_open->buf, '\n') == NULL)
	{
		if ((list_open->eof_flag = read(fd, list_open->buf, BUFFER_SIZE)) == -1)
		{
			delete_list(list_open, start_list);
			return (-1);
		}
		if (list_open->eof_flag == 0) // EOF has been reached
		{
			if (*list_open->buf == '\0')
			{
				free(*line);
				*line = NULL;
			}
			delete_list(list_open, start_list);
			return (0);
		}
		if ((temp = ft_strchr(list_open->buf, '\n')) != NULL)
		{
			*temp = '\0';
			free(list_open->reminfer);
			if (!(list_open->reminfer = ft_substr_gnl(temp + 1)))
			{
				delete_list(list_open, start_list);
				return (-1);
			}
			temp = *line;
			if (!(*line = ft_strjoin_gnl(temp, list_open->buf)))
			{
				delete_list(list_open, start_list);
				return (-1);
			}
			free(temp);
			free(list_open->buf);
			list_open->buf = NULL;
			// delete_list(list_open, start_list);
			return (1);
		}
		temp = *line;
		if (!(*line = ft_strjoin_gnl(temp, list_open->buf)))
		{
			delete_list(list_open, start_list);
			return (-1);
		}
		free(temp);
		// free(list_open->buf);
		// list_open->buf = NULL;
		temp = NULL;
	}
	return (-1);
}
