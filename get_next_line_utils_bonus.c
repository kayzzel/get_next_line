/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabach <gabach@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 15:53:21 by gabach            #+#    #+#             */
/*   Updated: 2025/11/20 13:30:52 by gabach           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_realloc(char *line, int to_add, char buffer[BUFFER_SIZE])
{
	int		index_l;
	int		index_b;
	char	*new_line;

	index_l = 0;
	if (line)
		while (line[index_l] != '\0')
			index_l++;
	new_line = malloc(sizeof(char) * (index_l + to_add + 1));
	if (!new_line)
		return (NULL);
	index_l = 0;
	if (line)
	{
		index_l = -1;
		while (line[++index_l])
			new_line[index_l] = line[index_l];
	}
	index_b = -1;
	while (++index_b < to_add)
		new_line[index_l + index_b] = buffer[index_b];
	free(line);
	new_line[index_l + index_b] = '\0';
	return (new_line);
}
