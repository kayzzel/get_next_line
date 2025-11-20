/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabach <gabach@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 15:19:37 by gabach            #+#    #+#             */
/*   Updated: 2025/11/20 13:30:20 by gabach           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

// INCLUDES

# include <stdlib.h>
# include <unistd.h>

// MACROS

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

// STRUCS

typedef struct s_rest
{
	int		fds[1025];
	char	*rests[1025];
}	t_rest;

// FUNCTIONS

char	*get_next_line(int fd);
char	*ft_realloc(char *line, int to_add, char buffer[BUFFER_SIZE]);

#endif
