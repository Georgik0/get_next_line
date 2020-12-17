/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skitsch <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 21:17:32 by skitsch           #+#    #+#             */
/*   Updated: 2020/12/15 21:17:41 by skitsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

int		delete_list(t_list *lop, t_list **start_list)
{
	t_list	*temp;
	t_list	*out;

	temp = *start_list;
	if (temp != lop)
	{
		while (temp && temp->next != lop)
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

int		get_next_line1(t_list **lop, t_list **start_list,
		char **line, char *temp)
{
	if (((*lop)->eof_flag = read((*lop)->descriptor,
	(*lop)->buf, BUFFER_SIZE)) == -1)
		return (delete_list(*lop, start_list) - 1);
	if ((temp = ft_strchr((*lop)->buf, '\n')) != NULL)
	{
		*temp = '\0';
		free((*lop)->reminfer);
		if (!((*lop)->reminfer = fsjoin(temp + 1, NULL, *lop, start_list)))
			return (-1);
		temp = *line;
		if (!(*line = fsjoin(temp, (*lop)->buf, *lop, start_list)))
			return (-1);
		free(temp);
		free((*lop)->buf);
		(*lop)->buf = NULL;
		return (1);
	}
	temp = *line;
	if (!(*line = fsjoin(temp, (*lop)->buf, *lop, start_list)))
		return (-1);
	free(temp);
	if ((*lop)->eof_flag == 0)
		return (delete_list(*lop, start_list));
	return (2);
}

int		get_next_line(int fd, char **line)
{
	static t_list		*start_list;
	t_list				*lop;
	char				*temp;
	int					out;

	if (!line || fd < 0 || BUFFER_SIZE <= 0)
		return (-1);
	if (!(lop = search_fd(&start_list, fd)))
		return (-1);
	if (!(lop->buf = (char *)ft_calloc(1 + BUFFER_SIZE, sizeof(char))) ||
	!(*line = ft_calloc(1, 1)))
		return (delete_list(lop, &start_list) - 1);
	temp = NULL;
	if ((lop->check_out = check_reminder(&lop, &start_list, line, temp)) != 2)
		return (lop->check_out);
	while (ft_strchr(lop->buf, '\n') == NULL)
	{
		lop->i = 0;
		while (lop->buf[lop->i] != '\0')
			lop->buf[lop->i++] = '\0';
		if ((out = get_next_line1(&lop, &start_list, line, temp)) != 2)
			return (out);
	}
	return (-1);
}
