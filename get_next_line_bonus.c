/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabach <gabach@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 15:18:43 by gabach            #+#    #+#             */
/*   Updated: 2025/11/20 17:20:16 by gabach           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <stdio.h>
#include <fcntl.h>

static int	load_buffer(int fd, t_rest *rest, char buffer[BUFFER_SIZE])
{
	int	index;
	int	index_b;

	if (rest->rests[0] == NULL)
	{
		rest->fds[0] = fd;
		rest->fds[1] = -1;
		return (0);
	}
	index = -1;
	index_b = -1;
	while (rest->fds[++index] != -1)
	{
		if (rest->fds[index] == fd)
		{
			while (++index_b < BUFFER_SIZE - 1 && rest->rests[index][index_b])
				buffer[index_b] = rest->rests[index][index_b];
			buffer[index_b] = rest->rests[index][index_b];
			return (index);
		}
	}
	rest->fds[index] = fd;
	rest->fds[index + 1] = -1;
	return (index);
}

static void	close_gnl(int fd, t_rest *rest)
{
	int	index;
	int	index_last;

	index = 0;
	index_last = 0;
	while (rest->fds[index_last] != -1)
		index_last++;
	while (rest->fds[index] != fd)
		index++;
	free(rest->rests[index]);
	if (index_last == index)
	{
		rest->rests[index] = NULL;
		rest->fds[index] = -1;
		return ;
	}
	rest->rests[index] = rest->rests[index_last];
	rest->fds[index] = rest->fds[index_last];
	rest->rests[index_last] = NULL;
	rest->fds[index_last] = -1;
	return ;
}

static char	*load_line(int fd, char buffer[BUFFER_SIZE], t_rest *rest)
{
	int		index;
	char	*line;
	int		read_result;

	line = NULL;
	while (1)
	{
		index = -1;
		while (++index < BUFFER_SIZE && buffer[index])
			if (buffer[index] == '\n')
				return (ft_realloc(line, index + 1, buffer));
		if (buffer[0] != '\0')
			line = ft_realloc(line, BUFFER_SIZE + 1, buffer);
		read_result = read(fd, buffer, BUFFER_SIZE);
		if (read_result == 0 || read_result == -1)
			close_gnl(fd, rest);
		if (read_result == -1)
		{
			free(line);
			return (NULL);
		}
		if (read_result == 0)
			return (line);
		buffer[read_result] = '\0';
	}
}

static void	save_rest(int fd_index, t_rest *rest, char buffer[BUFFER_SIZE])
{
	int	start;
	int	len;
	int	index;

	start = 0;
	while (buffer[start] != '\0' && buffer[start] != '\n')
		start++;
	if (buffer[start] == '\0')
		return ;
	start++;
	len = 0;
	while (buffer[start + len] && (start + len) < BUFFER_SIZE)
		len++;
	free(rest->rests[fd_index]);
	rest->rests[fd_index] = malloc(sizeof(char) * (len + 1));
	if (rest->rests[fd_index] == NULL)
		return ;
	index = 0;
	while (index < len)
	{
		rest->rests[fd_index][index] = buffer[start + index];
		index++;
	}
	rest->rests[fd_index][index] = '\0';
}

char	*get_next_line(int fd)
{
	static t_rest	rest = {0};
	char			*buffer;
	char			*line;
	int				fd_index;

	if (fd > 1024 || fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buffer == NULL)
		return (NULL);
	buffer[0] = '\0';
	fd_index = load_buffer(fd, &rest, buffer);
	line = load_line(fd, buffer, &rest);
	if (line)
		save_rest(fd_index, &rest, buffer);
	free(buffer);
	return (line);
}

/*

int	main(void)
{
	int	index = 1;
	int	fd1 = open("test.txt", O_RDONLY);
	int	fd2 = open("test2.txt", O_RDONLY);
	int	fd3 = open("test3.txt", O_RDONLY);
	char	*line = get_next_line(fd1);
	char	*line2 = get_next_line(fd2);
	char	*line3 = get_next_line(fd3);

	while (line)
	{
		printf("line : %i\nl1 : %sl2 : %sl3 : %s\n", index, line, line2, line3);
		free(line);
		free(line2);
		free(line3);
		line = get_next_line(fd1);
		line2 = get_next_line(fd2);
		line3 = get_next_line(fd3);
		index++;
	}

}

int	main(void)
{
	int	fd1 = open("read_error.txt", O_RDONLY);
	char	*line = get_next_line(fd1);

	while (line)
	{
		printf("l1 : %s", line);
		free(line);
		line = get_next_line(fd1);
	}

}
*/
