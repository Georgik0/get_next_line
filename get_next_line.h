/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skitsch <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 21:17:52 by skitsch           #+#    #+#             */
/*   Updated: 2020/12/15 21:18:05 by skitsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>
# include <unistd.h>

typedef struct		s_list
{
	int				descriptor;
	char			*buf;
	int				eof_flag;
	char			*reminfer;
	int				check_out;
	int				i;
	struct s_list	*next;

}					t_list;

int					get_next_line(int fd, char **line);
char				*fsjoin(char *s1, char *s2, t_list *list_open,
					t_list **start_list);
size_t				ft_strlcpy(char *dst, const char *src, size_t size);
char				*ft_strchr(const char *str, int ch);
char				*ft_calloc(size_t count, size_t size);
char				*ft_substr_gnl(char *buf, t_list *list_open,
					t_list **start_list);
int					delete_list(t_list *list_open, t_list **start_list);
int					check_reminder(t_list **list_open, t_list **start_list,
					char **line, char *temp);

#endif
