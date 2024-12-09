/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_utils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/09 08:01:55 by spyun         #+#    #+#                 */
/*   Updated: 2024/12/09 14:02:49 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"
#include "../libft/libft.h"

static char	*get_cmd_path(char **paths, char *cmd)
{
	char	*path;
	char	*part_path;
	int		i;

	i = 0;
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

void	execute_cmd(char *cmd, char **envp)
{
	char	**cmd_args;
	char	*cmd_path;

	cmd_args = parse_cmd(cmd);
	if (!cmd_args || !cmd_args[0])
	{
		free_array(cmd_args);
		ft_putstr_fd("Command parsing failed\n", 2);
		exit(127);
	}
	cmd_path = find_path(cmd_args[0], envp);
	if (!cmd_path)
	{
		ft_putstr_fd("Command not found\n", 2);
		free_array(cmd_args);
		exit(127);
	}
	if (execve(cmd_path, cmd_args, envp) == -1)
	{
		perror("Command execution failed");
		free(cmd_path);
		free_array(cmd_args);
		exit(126);
	}
}
