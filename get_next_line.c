/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabach <gabach@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 15:18:43 by gabach            #+#    #+#             */
/*   Updated: 2025/11/19 18:10:44 by gabach           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	load_buffer(int fd, t_rest *rest, char buffer[BUFFER_SIZE])
{
	int	index;
	int	index_b;

	if (rest->rests[0] == NULL)
	{
		rest->rests[0] = NULL;
		rest->rests[1] = NULL;
		rest->fds[0] = fd;
		rest->fds[1] = -1;
		return ;
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
			return ;
		}
	}
	rest->fds[index] = fd;
	rest->fds[index + 1] = -1;
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
		index = 0;
		while (index < BUFFER_SIZE && buffer[index])
		{
			if (buffer[index] == '\n')
				return (ft_realloc(line, index + 1, buffer));
			index++;
		}
		if (buffer[0] != '\0')
			line = ft_realloc(line, BUFFER_SIZE + 1, buffer);
		read_result = read(fd, buffer, BUFFER_SIZE);
		if (read_result == -1 || read_result == 0)
		{
			close_gnl(fd, rest);
			return (line);
		}
	}
}

static void	save_rest(int fd, t_rest *rest, char buffer[BUFFER_SIZE])
{
	int	index_fd;
	int	index;
	int	index_b;

	index_fd = 0;
	index = 0;
	index_b = 0;
	while (rest->fds[index_fd] != fd && rest->fds[index_fd] != -1)
		index_fd++;
	if (rest->fds[index_fd] == -1)
		return ;
	free(rest->rests[index_fd]);
	rest->rests[index_fd] = NULL;
	while (buffer[index_b] != '\n')
		index_b++;
	while (buffer[index_b + index] && index_b + index < BUFFER_SIZE)
		index++;
	rest->rests[index_fd] = malloc(sizeof(char) * index);
	if (!rest->rests[index_fd])
		return ;
	rest->rests[index_fd][index - 1] = '\0';
	while (--index > 0)
		rest->rests[index_fd][index - 1] = buffer[index_b + index];
}

char	*get_next_line(int fd)
{
	static t_rest	rest = {0};
	char			buffer[BUFFER_SIZE];
	char			*line;

	if (fd > 1024 || fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	buffer[0] = '\0';
	load_buffer(fd, &rest, buffer);
	line = load_line(fd, buffer, &rest);
	if (line)
		save_rest(fd, &rest, buffer);
	return (line);
}

/*
#include <stdio.h>
#include <fcntl.h>

int	main(void)
{
	int	fd1 = open("test.txt", O_RDONLY);
	//int	fd2 = open("test2.txt", O_RDONLY);
	//int	fd3 = open("test3.txt", O_RDONLY);
	char	*line = get_next_line(fd1);
	//char	*line2 = get_next_line(fd2);
	//char	*line3 = get_next_line(fd3);

	while (line)
	{
	//	printf("l1 : %s\nl2 : %s\nl3 : %s\n\n", line, line2, line3);
		printf("l1 : %s", line);
		line = get_next_line(fd1);
	//	line2 = get_next_line(fd2);
	//	line3 = get_next_line(fd3);
	}

}
*/
