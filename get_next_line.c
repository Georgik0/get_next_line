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
		return (start);
	}
	while (descriptor != start->descriptor)
	{
		if (start = start->next == NULL)
		{
			if (!(start = (t_list *)malloc(sizeof(t_list))))
				return (NULL);
			start->next = NULL;
			start->descriptor = descriptor;
			return (start);
		}
		if (start->descriptor == descriptor)
			return (start);
	}
	return (start);
}

void		delete_list_element(t_buffer)
{

}

char		*check_reminder(char *reminder, char *line, int size_reminder)
{
	char	*out;
	char	*start_reminder;

	if (!(out = ft_strchr(reminder, '\n'))) // если не нашли, то копируем остаток в *line
		ft_strlcpy(line, out, size_reminder + 1);
	else // если нашли, то скопировали в line и перезаписали reminder, предварительно заменив '\n' на '\0'
	{
		*(--out) = '\0';
		ft_strlcpy(line, out, size_reminder + 1);
	}
}

int		get_next_line(int fd, char **line)
{
	static t_list		*start_list;
	t_list				*list_open;
	char				*temp;
	int					get_read;
	int					i;

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
		// чистим лист
		return (-1);
	}
	i = 0;

	while (1)
	{
		if (list_open->buf[i] == '\0')
		{
			if (!(temp = ft_substr_gnl(list_open->buf)))
			{
				// чистка
				return (-1);
			}
			if (i != BUFFER_SIZE)
			{
				if (!(*line = ft_strjoin_gnl(temp, list_open->buf)))
				{
					// чистка
					return (-1); // an error happened
				}
				else
				{
					// чистка
					return (0); // EOF has benn read
				}
			}
			else
			{
				if (!(*line = ft_strjoin_gnl(temp, list_open->buf)))
				{
					// чистка
					return (-1); // an error happened
				}
				else
				{
					i = 0;
					free(list_open->buf);
					list_open->buf = NULL;
					if (!(list_open->buf = (char *)ft_calloc(1 + BUFFER_SIZE, sizeof(char))))
					{
						// чистка
						return (-1); // an error happened
					}
					if (read(fd, list_open->buf, BUFFER_SIZE) == -1)
					{
						// чистка
						return (-1); // an error happened
					}
				}
			}
		}
		if (list_open->buf[i] == '\n')
		{
			list_open->buf[i] = '\0';
			if (!(temp = ft_substr_gnl(list_open->buf)))
			{
				// чистка
				return (-1);
			}
			if (!(*line = ft_strjoin_gnl(temp, list_open->buf)))
			{
				// чистка
				return (-1); // an error happened
			}
			if (!(ft_strlcpy(list_open->reminfer, list_open->buf + i, BUFFER_SIZE)))
			{
				// чистка
				return (-1); // an error happened
			}
		}
		free(temp);
	}

	while (ft_strchr(list_open->buf, '\n') == NULL)
	{
		if (get_read = read(fd, list_open->buf, BUFFER_SIZE) == -1)
		{
			// чистка
			return (-1); // an error happened
		}
		if (temp = ft_strchr(list_open->buf, '\n') != NULL)
		{
			*temp = '\0';
			if (!(list_open->reminfer = ft_substr_gnl(temp + 1)))
			{
				// чистка
				return (-1);
			}
			temp = *line;
			if (!(*line = ft_strjoin_gnl(temp, list_open->buf)))
			{
				// чистка
				return (-1);
			}
			// чистка temp и list_open->buf и остального
			return (1);
		}
		if (get_read == 0) // EOF has been reached
		{
			temp = *line;
			if (!(*line = ft_strjoin_gnl(temp, list_open->buf)))
			{
				// чистка
				return (-1);
			}
			// чистка temp и list_open->buf и остального
			return (1);
		}
	}

}
