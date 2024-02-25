/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beddinao <beddinao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 12:26:07 by beddinao          #+#    #+#             */
/*   Updated: 2024/01/01 03:41:03 by beddinao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*re_cycle(char **trash, int *how_bad, char *line, int *lsize)
{
	char				*new_line;
	char				*new_trash;
	int					size;

	size = is_divided(*trash, 0, *how_bad);
	new_line = re_tighten(*trash, 0, size, 0);
	if (size != *how_bad)
	{
		new_trash = re_tighten(*trash, size, *how_bad, 1);
		*trash = new_trash;
	}
	else
	{
		*trash = re_clean(*trash, 0, *how_bad);
		free(*trash);
	}
	*how_bad -= size;
	if (!line)
		*lsize = size;
	else
		*lsize += size;
	return (new_line);
}

char	*re_cpy(char *line, int *size, char *pre_line, int *pre_size)
{
	char				*new_line;

	if (line != NULL)
	{
		new_line = re_tightenthem(line, pre_line, *size, *pre_size);
		*size += *pre_size;
	}
	else
	{
		new_line = re_tighten(pre_line, 0, *pre_size, 1);
		*size = *pre_size;
		free(line);
	}
	*pre_size = 0;
	return (new_line);
}

char	*re_check(char **pre_line, int *pre_size, char **trash, int *how_bad)
{
	int					size;
	char				*new_pre_line;
	char				*new_trash;

	size = is_divided(*pre_line, 0, *pre_size);
	if (size == *pre_size)
		return (*pre_line);
	new_pre_line = re_tighten(*pre_line, 0, size, 0);
	new_trash = re_tighten(*pre_line, size, *pre_size, 1);
	*trash = new_trash;
	*how_bad = *pre_size - size;
	*pre_size -= *how_bad;
	return (new_pre_line);
}

char	*re_read(int fd, int *pre_size, char **line, int *size)
{
	char				*pre;
	int					readed;

	pre = malloc((BUFFER_SIZE + 1) * sizeof(*pre));
	if (!pre)
	{
		free(pre);
		return (NULL);
	}
	pre = re_clean(pre, 0, BUFFER_SIZE + 1);
	readed = read(fd, pre, BUFFER_SIZE);
	if (readed <= 0)
	{
		free(pre);
		if (readed < 0 && *size)
			free(*line - (*size = 0));
		return (NULL);
	}
	if (readed < BUFFER_SIZE)
		pre = re_tighten(pre, 0, readed, 1);
	*pre_size = readed;
	return (pre);
}

char	*get_next_line(int fd)
{
	static char		*trash;
	static int		how_bad;
	char			*line;
	char			*pre_line;
	int				size[2];

	line = NULL;
	while (1)
	{
		if (how_bad > 0)
			line = re_cycle(&trash, &how_bad, line, &size[1]);
		else
		{
			pre_line = re_read(fd, &size[0], &line, &size[1]);
			if (!pre_line)
				break ;
			pre_line = re_check(&pre_line, &size[0], &trash, &how_bad);
			line = re_cpy(line, &size[1], pre_line, &size[0]);
		}
		if (line[size[1] - 1] == '\n')
			break ;
	}
	if (size[1] <= 0)
		return (NULL);
	return (line);
}
