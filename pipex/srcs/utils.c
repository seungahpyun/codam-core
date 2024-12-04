/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/04 09:58:18 by spyun         #+#    #+#                 */
/*   Updated: 2024/12/04 10:59:10 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"
#include "../libft/libft.h"
#include <unistd.h>
#include <stdlib.h>

void	error_exit(char *error_msg)
{
	ft_putendl_fd(error_msg, STDERR_FILENO);
	exit(EXIT_FAILURE);
}
char	*get_cmd_path(char **paths, char *cmd)
{
	char	*path;
	char	*part_path;
	int		i;

	i = 0;
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(path, F_OK | X_OK) == 0)
		{
			while (paths[i])
				free(paths[i++]);
			free(paths);
			return (path);
		}
		free(path);
		i++;
	}
	return (NULL);
}

char	*find_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path;

	while (*envp && ft_strncmp("PATH=", *envp, 5))
		envp++;
	if (!*envp)
		return (NULL);
	paths = ft_split(*envp + 5, ':');
	if (!paths)
		return (NULL);
	path = get_cmd_path(paths, cmd);
	return (path);
}

void	execute_cmd(char *cmd, char **envp)
{
	char	**cmd_args;
	char	*cmd_path;

	cmd_args = ft_split(cmd, ' ');
	if (cmd_args == NULL)
		error_exit("ERROR : split failed");
	cmd_path = find_path(cmd_args[0], envp);
	if (!cmd_path)
	{
		while (*cmd_args)
			free(*cmd_args++);
		free(cmd_args);
		error_exit("ERROR : command not found");
	}
	if (execve(cmd_path, cmd_args, envp) == -1)
	{
		free(cmd_path);
		while (*cmd_args)
			free(*cmd_args++);
		free(cmd_args);
		error_exit("ERROR : execve failed");
	}
}
