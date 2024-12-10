/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc_bonus.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/09 07:16:48 by spyun         #+#    #+#                 */
/*   Updated: 2024/12/10 08:18:25 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	handle_here_doc(t_pipex *pipex)
{
	char	*line;
	int		temp_pipe[2];

	if (pipe(temp_pipe) == -1)
		error_exit("Pipe failed\n");
	while (1)
	{
		ft_putstr_fd("heredoc> ", STDOUT_FILENO);
		line = get_next_line(0);
		if (!line)
			break ;
		if (ft_strncmp(line, pipex->limiter, ft_strlen(pipex->limiter)) == 0
			&& line[ft_strlen(pipex->limiter)] == '\n')
		{
			free(line);
			break ;
		}
		write(temp_pipe[1], line, ft_strlen(line));
		free(line);
	}
	close(temp_pipe[1]);
	if (dup2(temp_pipe[0], STDIN_FILENO) == -1)
		error_exit("Dup2 failed");
	close(temp_pipe[0]);
}
