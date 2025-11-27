/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabach <gabach@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 15:18:43 by gabach            #+#    #+#             */
/*   Updated: 2025/11/27 11:27:39 by gabach           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*ft_realloc(char *line, int to_add, \
char rests[1025][BUFFER_SIZE + 1], int fd)
{
	int		index_l;
	int		index_b;
	char	*new_line;

	index_l = 0;
	if (line)
		while (line[index_l] != '\0')
			index_l++;
	new_line = malloc(sizeof(char) * (index_l + to_add + 1));
	index_l = 0;
	if (line && new_line)
	{
		index_l = -1;
		while (line[++index_l])
			new_line[index_l] = line[index_l];
	}
	free(line);
	if (!new_line)
		return (NULL);
	index_b = -1;
	while (++index_b < to_add)
		new_line[index_l + index_b] = rests[fd][index_b];
	new_line[index_l + index_b] = '\0';
	return (new_line);
}

static char	*load_line(int fd, char rests[1025][BUFFER_SIZE + 1], char	*line)
{
	int		index;
	int		read_result;

	while (1)
	{
		index = -1;
		while (++index < BUFFER_SIZE && rests[fd][index])
			if (rests[fd][index] == '\n')
				return (ft_realloc(line, index + 1, rests, fd));
		if (rests[fd][0] != '\0')
			line = ft_realloc(line, index, rests, fd);
		if (rests[fd][0] != '\0' && line == NULL)
			return (NULL);
		read_result = read(fd, rests[fd], BUFFER_SIZE);
		if (read_result == -1 || read_result == 0)
			rests[fd][0] = '\0';
		if (read_result == -1)
		{
			free(line);
			return (NULL);
		}
		if (read_result == 0)
			return (line);
		rests[fd][read_result] = '\0';
	}
}

static void	save_rest(int fd, char rests[1025][BUFFER_SIZE + 1])
{
	int	start;
	int	len;
	int	index;

	start = 0;
	while (rests[fd][start] != '\0' && rests[fd][start] != '\n')
		start++;
	if (rests[fd][start] == '\0')
	{
		rests[fd][0] = '\0';
		return ;
	}
	start++;
	len = 0;
	while (rests[fd][start + len] && (start + len) < BUFFER_SIZE)
		len++;
	index = 0;
	while (index < len)
	{
		rests[fd][index] = rests[fd][start + index];
		index++;
	}
	rests[fd][index] = '\0';
}

char	*get_next_line(int fd)
{
	static char	rests[1025][BUFFER_SIZE + 1];
	char		*line;

	if (fd > 1024 || fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	line = load_line(fd, rests, NULL);
	if (line)
		save_rest(fd, rests);
	return (line);
}
