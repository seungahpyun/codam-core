/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/04 09:58:18 by spyun         #+#    #+#                 */
/*   Updated: 2024/12/05 15:00:38 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"
#include "../libft/libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

void error_exit(void)
{
    perror("\033[31mError");
    exit(EXIT_FAILURE);
}

void free_array(char **array)
{
    int i;

    if (!array)
        return ;
    i = 0;
    while (array[i])
        free(array[i++]);
    free(array);
}

char *get_cmd_path(char **paths, char *cmd)
{
    char *path;
    char *part_path;
    int i;

    i = 0;
    if (cmd[0] == '/' || (cmd[0] == '.' && cmd[1] == '/'))
    {
        if (access(cmd, F_OK | X_OK) == 0)
            return (ft_strdup(cmd));
        return (NULL);
    }
    while (paths && paths[i])
    {
        part_path = ft_strjoin(paths[i], "/");
        if (!part_path)
            return (NULL);
        path = ft_strjoin(part_path, cmd);
        free(part_path);
        if (!path)
            return (NULL);
        if (access(path, F_OK | X_OK) == 0)
        {
            free_array(paths);
            return (path);
        }
        free(path);
        i++;
    }
    if (paths)
        free_array(paths);
    return (NULL);
}

char *find_path(char *cmd, char **envp)
{
    char **paths;
    char *path;

    if (!cmd || !cmd[0])
        return (NULL);
    while (envp && *envp && ft_strncmp("PATH=", *envp, 5))
        envp++;
    if (!envp || !*envp)
    {
        if (access(cmd, F_OK | X_OK) == 0)
            return (ft_strdup(cmd));
        return (NULL);
    }
    paths = ft_split(*envp + 5, ':');
    if (!paths)
        return (NULL);
    path = get_cmd_path(paths, cmd);
    return (path);
}

void execute_cmd(char *cmd, char **envp)
{
    char **cmd_args;
    char *cmd_path;

    cmd_args = parse_cmd(cmd);
    if (!cmd_args || !cmd_args[0])
    {
        free_array(cmd_args);
        error_exit();
    }
    cmd_path = find_path(cmd_args[0], envp);
    if (!cmd_path)
    {
        free_array(cmd_args);
        error_exit();
    }
    if (execve(cmd_path, cmd_args, envp) == -1)
    {
        free(cmd_path);
        free_array(cmd_args);
        error_exit();
    }
}
