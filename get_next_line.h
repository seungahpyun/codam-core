/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   get_next_line.h                                     :+:    :+:           */
/*                                                      +:+                   */
/*   By: spyun <marvin@42.fr>                          +#+                    */
/*                                                    +#+                     */
/*   Created: 2024/10/24 11:16:58 by spyun          #+#    #+#                */
/*   Updated: 2024/10/24 11:17:00 by spyun          ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

typedef struct s_list
{
	char			*str_buffer;
	struct s_list	*next;
}	t_list;

char	*get_next_line(int fd);
int		read_and_store(t_list **list, int fd);
char	*extract_line(t_list *list);
t_list	*store_remaining(t_list *list);
void	free_list(t_list **list);
int		find_newline(t_list *list);
void	append_buffer_to_list(t_list **list, char *buffer);
char	*create_line_buffer(t_list *list, int *total_len);
void	copy_line(t_list *list, char *line, int total_len);

#endif
