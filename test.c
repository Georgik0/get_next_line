#include "get_next_line.h"

int		check_reminder(t_list *list_open, char **line)
{
	char	*temp;

	temp = NULL;
	if (temp = ft_strchr(list_open->reminfer, '\n') != NULL)
	{
		*temp = '\0';
		free(list_open->reminfer);
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
		return (1); // a line has been read
	}
	temp = *line;
	if (!(*line = ft_strjoin_gnl(temp, list_open->reminfer)))
	{
		// чистка
		return (-1);
	}
	// чистка temp, list_open->buf, list_open->reminder
}
