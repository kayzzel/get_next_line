/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabach <gabach@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 15:19:37 by gabach            #+#    #+#             */
/*   Updated: 2025/11/19 15:53:47 by gabach           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

// INCLUDES

# include <stdlib.h>
# include <unistd.h>

// MACROS

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

// FUNCTIONS

char	*get_next_line(int fd);

#endif
