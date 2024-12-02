/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <marvin@42.fr>                         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/24 11:16:58 by spyun         #+#    #+#                 */
/*   Updated: 2024/12/02 11:07:46 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "../libft/libft.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

typedef struct s_gnl_list
{
	int					fd;
	char				*buffer;
	struct s_gnl_list	*next;
}	t_gnl_list;

char	*get_next_line(int fd);

#endif
