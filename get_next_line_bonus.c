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

t_list	*search_fd1(t_list **start, int descriptor)
{
	t_list *tmp;

	tmp = *start;
	while (descriptor != tmp->descriptor)
	{
		if ((tmp->next) == NULL)
		{
			if (!(tmp->next = (t_list *)malloc(sizeof(t_list))))
				return (NULL);
			tmp->next->descriptor = descriptor;
			if (!(tmp->next->reminfer = ft_calloc(1, 1)))
			{
				free(tmp->next);
				return (NULL);
			}
			tmp->next->eof_flag = 1;
			tmp->next->next = NULL;
			return (tmp->next);
		}
		tmp = tmp->next;
	}
	return (tmp);
}

t_list	*search_fd(t_list **start, int descriptor)
{
	t_list *tmp;

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
	tmp = search_fd1(start, descriptor);
	return ((tmp));
}

int		delete_list(t_list *list_open, t_list **start_list)
{
	t_list	*temp;
	t_list	*out;

	temp = *start_list;
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
		*start_list = out->next;
	}
	free(out->buf);
	free(out->reminfer);
	free(out);
	out = NULL;
	return (0);
}

int		get_next_line1(t_list **list_open, t_list **start_list, char **line, char *temp)
{
	if (((*list_open)->eof_flag = read((*list_open)->descriptor, (*list_open)->buf, BUFFER_SIZE)) == -1)
		return (delete_list(*list_open, start_list) - 1);
	if ((temp = ft_strchr((*list_open)->buf, '\n')) != NULL)
	{
		*temp = '\0';
		free((*list_open)->reminfer);
		if (!((*list_open)->reminfer = ft_strjoin_gnl(temp + 1, NULL, *list_open, start_list)))
			return (-1);
		temp = *line;
		if (!(*line = ft_strjoin_gnl(temp, (*list_open)->buf, *list_open, start_list)))
			return (-1);
		free(temp);
		free((*list_open)->buf);
		(*list_open)->buf = NULL;
		return (1);
	}
	temp = *line;
	if (!(*line = ft_strjoin_gnl(temp, (*list_open)->buf, *list_open, start_list)))
		return (-1);
	free(temp);
	if ((*list_open)->eof_flag == 0)
		return(delete_list(*list_open, start_list));
	return (2);
}

int		get_next_line(int fd, char **line)
{
	static t_list		*start_list;
	t_list				*list_open;
	char				*temp;
	int					out;

	if (!line || fd < 0 || BUFFER_SIZE <= 0)
		return (-1);
	if (!(list_open = search_fd(&start_list, fd)))
		return (-1);
	if (!(list_open->buf = (char *)ft_calloc(1 + BUFFER_SIZE, sizeof(char))) ||
	!(*line = ft_calloc(1, 1)))
		return (delete_list(list_open, &start_list) - 1);
	if ((list_open->check_out = check_reminder(&list_open, &start_list, line, temp = NULL)) != 2)
		return (list_open->check_out);
	while (ft_strchr(list_open->buf, '\n') == NULL)
	{
		list_open->i = 0;
		while (list_open->buf[list_open->i] != '\0')
			list_open->buf[list_open->i++] = '\0';
		if ((out = get_next_line1(&list_open, &start_list, line, temp)) != 2)
			return (out);
	}
	return (-1);
}
