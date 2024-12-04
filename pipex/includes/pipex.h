/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/04 09:51:45 by spyun         #+#    #+#                 */
/*   Updated: 2024/12/04 10:59:06 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

void	error_exit(char *error_msg);
char	*find_path(char *cmd, char **envp);
void	execute_cmd(char *cmd, char **envp);

void	child_process(char **argv, char **envp, int *pipe_fd);
void	parent_process(char **argv, char **envp, int *pipe_fd);
void	create_pipe(char **argv, char **envp);

void	check_args(int argc, char **argv);
void	check_infile(char *infile);
void	check_outfile(char *outfile);


# endif
