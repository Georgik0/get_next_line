/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skitsch <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 17:22:52 by skitsch           #+#    #+#             */
/*   Updated: 2020/11/27 17:25:56 by skitsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>
# include <unistd.h>

# define BUFFER_SIZE 10

typedef struct		s_list
{
	int				descriptor;
	char			*buf;
	char			test[BUFFER_SIZE];
	char			*reminfer;
	int				position_save;
	void			*next;

}					t_list;


int			get_next_line(int fd, char **line);
char		*ft_strjoin_gnl(char const *s1, char const *s2);
size_t		ft_strlcpy(char *dst, const char *src, size_t size);
char		*ft_strchr(const char *str, int ch);
char		*ft_calloc(size_t count, size_t size);
char		*ft_substr_gnl(char *buf);

#endif
