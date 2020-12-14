/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skitsch <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 19:48:22 by skitsch           #+#    #+#             */
/*   Updated: 2020/12/13 19:48:24 by skitsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

t_list	*search_fd(t_list **start, int descriptor)
{
	t_list *tmp;
	t_list *list_open;

	if (!(*start))
	{
		if (!(*start = (t_list *)malloc(sizeof(t_list))))
			return (NULL);
		(*start)->descriptor = descriptor;
		(*start)->next = NULL;
		if (!((*start)->reminfer = (char *)ft_calloc(1, 1)))
		{
			free((*start));
			return (NULL);
		}
		(*start)->eof_flag = 1;
		return ((*start));
	}
	tmp = *start;
	while (descriptor != tmp->descriptor)
	{
		if ((tmp->next) == NULL)
		{
			if (!(list_open = (t_list *)malloc(sizeof(t_list))))
				return (NULL);
			tmp->next = list_open;
			list_open->descriptor = descriptor;
			if (!(list_open->reminfer = ft_calloc(1, 1)))
			{
				free(tmp);
				return (NULL);
			}
			list_open->eof_flag = 1;
			list_open->next = NULL;
			return (list_open);
		}
		tmp = tmp->next;
		// if ((*start)->descriptor == descriptor)
		// 	return ((*start));
	}
	return ((tmp));
}

int		get_next_line(int fd, char **line)
{
	static t_list		*start_list;
	t_list				*list_open;
	char				*temp;
	int					check_out;
	int					i;

	i = 0;
	if (!line || fd < 0 || BUFFER_SIZE <= 0)
		return (-1);
	if (start_list == NULL) // значит лист пуст, нужно создать первый элемент
	{
		if (!(list_open = search_fd(&start_list, fd)))
			return (-1);
		// list_open = start_list;
	}
	else // значит что-то уже читается => можно искать необходимый элемент листа
	{
		if (!(list_open = search_fd(&start_list, fd)))
			return (-1);
	}
	if (!(list_open->buf = (char *)ft_calloc(1 + BUFFER_SIZE, sizeof(char))))
	{
		delete_list(list_open, &start_list);
		return (-1);
	}
	if (!(*line = ft_calloc(1, 1)))
	{
		delete_list(list_open, &start_list);
		return (-1);
	}
	if ((check_out = check_reminder(&list_open, &start_list, line)) != 2)
		return (check_out);
	while (ft_strchr(list_open->buf, '\n') == NULL)
	{
		i = 0;
		while (list_open->buf[i] != '\0')
			list_open->buf[i++] = '\0';
		if (read(fd, list_open->buf, BUFFER_SIZE) == -1)
		{
			delete_list(list_open, &start_list);
			return (-1);
		}
		if ((temp = ft_strchr(list_open->buf, '\0')) != (list_open->buf + BUFFER_SIZE))
			list_open->eof_flag = 0;
		if ((temp = ft_strchr(list_open->buf, '\n')) != NULL)
		{
			*temp = '\0';
			free(list_open->reminfer);
			if (!(list_open->reminfer = ft_substr_gnl(temp + 1)))
			{
				delete_list(list_open, &start_list);
				return (-1);
			}
			temp = *line;
			if (!(*line = ft_strjoin_gnl(temp, list_open->buf)))
			{
				delete_list(list_open, &start_list);
				return (-1);
			}
			free(temp);
			free(list_open->buf);
			list_open->buf = NULL;
			return (1);
		}
		temp = *line;
		if (!(*line = ft_strjoin_gnl(temp, list_open->buf)))
		{
			delete_list(list_open, &start_list);
			return (-1);
		}
		free(temp);
		temp = NULL;
		if (list_open->eof_flag == 0)
		{
			delete_list(list_open, &start_list);
			return(0);
		}
	}
	return (-1);
}
