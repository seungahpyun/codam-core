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

int		ft_find_newline(t_list *list);
t_list	*ft_find_lstlast(t_list *list);
void	ft_free_list(t_list **list);
int		ft_copy_to_line(t_list *temp, char *line, int total_len);
char	*ft_create_line_from_list(t_list *list, int total_len);
void	ft_create_list(t_list **list, int fd);
char	*ft_get_line(t_list *list);
void	ft_append_list(t_list **list, char *buffer);
void	ft_create_list(t_list **list, int fd);
char	*get_next_line(int fd);
#endif
