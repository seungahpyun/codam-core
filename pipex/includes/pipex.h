/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/04 09:51:45 by spyun         #+#    #+#                 */
/*   Updated: 2024/12/10 09:39:27 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/wait.h>
# include "../libft/libft/libft.h"

typedef struct s_pipex
{
	int		pipe_fd[2];
	pid_t	pid1;
	pid_t	pid2;
	char	*infile;
	char	*outfile;
	char	*cmd1;
	char	*cmd2;
}	t_pipex;

void	init_pipex(t_pipex *pipex, char **argv);
void	create_pipe(t_pipex *pipex);
void	execute_commands(t_pipex *pipex, char **envp);
void	error_exit(const char *msg);
char	*find_path(char *cmd, char **envp);
char	**parse_cmd(char *str);
void	free_array(char **array);
void	check_args(int argc, char **argv);
void	execute_cmd(char *cmd, char **envp);
int		is_quote(char c);
char	*parse_quoted_arg(char *str, int *i);
char	*parse_non_quoted_arg(char *str, int *i);
char	**init_args(char *str, int *arg_count);

#endif
