/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/04 09:58:18 by spyun         #+#    #+#                 */
/*   Updated: 2024/12/04 14:15:16 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"
#include "../libft/libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

void	error_exit(char *error_msg, int status)
{
	perror(error_msg);
	exit(status);
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
	if (!cmd_args)
		error_exit("ERROR : split failed", STDERR_FILENO);
	if (!cmd_args[0])
	{
		free(cmd_args);
		perror("ERROR : empty command");
		exit(127);
	}
	cmd_path = find_path(cmd_args[0], envp);
	if (!cmd_path)
	{
		while (*cmd_args)
			free(*cmd_args++);
		free(cmd_args);
		perror("ERROR : command not found");
		exit(127);
	}
	if (execve(cmd_path, cmd_args, envp) == -1)
	{
		free(cmd_path);
		while (*cmd_args)
			free(*cmd_args++);
		free(cmd_args);
		perror("ERROR : execve failed");
		exit(126);
	}
}
