/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabach <gabach@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 15:18:43 by gabach            #+#    #+#             */
/*   Updated: 2025/11/26 14:46:25 by gabach           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_realloc(char *line, int to_add, char buffer[BUFFER_SIZE])
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
		new_line[index_l + index_b] = buffer[index_b];
	new_line[index_l + index_b] = '\0';
	return (new_line);
}

static void	load_buffer(int fd, char rest[1025][BUFFER_SIZE], \
char buffer[BUFFER_SIZE])
{
	int	index;

	index = 0;
	while (rest[fd][index] != '\0' && index < BUFFER_SIZE)
	{
		buffer[index] = rest[fd][index];
		index++;
	}
	buffer[index] = '\0';
}

static char	*load_line(int fd, char rests[1025][BUFFER_SIZE], \
char buffer[BUFFER_SIZE], char	*line)
{
	int		index;
	int		read_result;

	while (1)
	{
		index = -1;
		while (++index < BUFFER_SIZE && buffer[index])
			if (buffer[index] == '\n')
				return (ft_realloc(line, index + 1, buffer));
		if (buffer[0] != '\0')
			line = ft_realloc(line, index, buffer);
		if (buffer[0] != '\0' && line == NULL)
			return (NULL);
		read_result = read(fd, buffer, BUFFER_SIZE);
		if (read_result == -1 || read_result == 0)
			rests[fd][0] = '\0';
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

static void	save_rest(int fd, char rests[1025][BUFFER_SIZE], \
char buffer[BUFFER_SIZE])
{
	int	start;
	int	len;
	int	index;

	start = 0;
	while (buffer[start] != '\0' && buffer[start] != '\n')
		start++;
	if (buffer[start] == '\0')
	{
		rests[fd][0] = '\0';
		return ;
	}
	start++;
	len = 0;
	while (buffer[start + len] && (start + len) < BUFFER_SIZE)
		len++;
	index = 0;
	while (index < len)
	{
		rests[fd][index] = buffer[start + index];
		index++;
	}
	rests[fd][index] = '\0';
}

char	*get_next_line(int fd)
{
	static char	rests[1025][BUFFER_SIZE];
	char		buffer[BUFFER_SIZE + 1];
	char		*line;

	if (fd > 1025 || fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	buffer[0] = '\0';
	load_buffer(fd, rests, buffer);
	line = load_line(fd, rests, buffer, NULL);
	if (line)
		save_rest(fd, rests, buffer);
	return (line);
}

/*
#include <stdio.h>
#include <fcntl.h>

int	main(void)
{
	int	index = 1;
	int	fd1 = open("test1.txt", O_RDONLY);
	int	fd2 = open("test2.txt", O_RDONLY);
	int	fd3 = open("test.txt", O_RDONLY);
	char	*line = get_next_line(fd1);
	char	*line2 = get_next_line(fd2);
	char	*line3 = get_next_line(fd3);

	while (line || line2 || line3)
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

int	main(int argc, char **argv)
{
	(void)argc;
	int		index = 1;
	int		fd1 = open(argv[1], O_RDONLY);
	char	*line = get_next_line(fd1);

	while (line)
	{
		printf("line %i : %s", index, line);
		free(line);
		line = get_next_line(fd1);
		index++;
	}
	close(fd1);
}
*/
