/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/04 09:58:18 by spyun         #+#    #+#                 */
<<<<<<< Updated upstream
/*   Updated: 2024/12/04 18:41:36 by spyun         ########   odam.nl         */
=======
/*   Updated: 2024/12/05 08:33:08 by spyun         ########   odam.nl         */
>>>>>>> Stashed changes
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

void	free_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
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

	cmd_args = parse_cmd(cmd);
	if (!cmd_args)
		error_exit("ERROR : split failed", STDERR_FILENO);
	if (!cmd_args[0])
	{
		free_array(cmd_args);
		error_exit("ERROR : empty command", 127);
	}
	cmd_path = find_path(cmd_args[0], envp);
	if (!cmd_path)
	{
		free_array(cmd_args);
		error_exit("ERROR : command not found", 127);
	}
	execve(cmd_path, cmd_args, envp);
	free(cmd_path);
	free_array(cmd_args);
	error_exit("ERROR : execve failed", 126);
}
