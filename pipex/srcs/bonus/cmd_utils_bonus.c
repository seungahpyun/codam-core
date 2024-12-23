/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_utils_bonus.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/09 07:56:54 by spyun         #+#    #+#                 */
/*   Updated: 2024/12/23 16:13:26 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

static char	*get_cmd_path(char **paths, char *cmd)
{
	char	*path;
	char	*part_path;
	int		i;

	i = 0;
	if (!cmd || !paths || !cmd[0])
		return (NULL);
	if (access(cmd, F_OK | X_OK) == 0)
		return (ft_strdup(cmd));
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		if (!part_path)
			return (NULL);
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (!path)
			return (NULL);
		if (access(path, F_OK | X_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	return (NULL);
}

char	*find_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path;

	if (!cmd ||!*cmd || !envp)
		return (NULL);
	if (access(cmd, F_OK | X_OK) == 0)
		return (ft_strdup(cmd));
	while (*envp && ft_strncmp("PATH=", *envp, 5))
		envp++;
	if (!*envp)
		return (NULL);
	paths = ft_split(*envp + 5, ':');
	if (!paths)
		return (NULL);
	path = get_cmd_path(paths, cmd);
	free_array(paths);
	return (path);
}

void	execute_cmd(char *cmd, char **envp, t_pipex *pipex)
{
	char	**cmd_args;
	char	*cmd_path;

	cmd_args = parse_cmd(cmd);
	if (!cmd_args || !cmd_args[0])
	{
		free_array(cmd_args);
		error_exit("Command parsing failed", pipex);
	}
	if (access(cmd_args[0], F_OK | X_OK) == 0)
		cmd_path = ft_strdup(cmd_args[0]);
	else
		cmd_path = find_path(cmd_args[0], envp);
	if (!cmd_path)
	{
		free_array(cmd_args);
		error_exit("Command not found", pipex);
	}
	if (execve(cmd_path, cmd_args, envp) == -1)
	{
		free(cmd_path);
		free_array(cmd_args);
		perror_exit("Command execution failed", pipex);
	}
}
