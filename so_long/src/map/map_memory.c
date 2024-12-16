/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_memory.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/13 10:46:15 by spyun         #+#    #+#                 */
/*   Updated: 2024/12/16 12:08:03 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_allocated_map(t_game *game, int last_row)
{
	int	i;

	i = 0;
	while (i < last_row)
	{
		free(game->map[i]);
		i++;
	}
	free(game->map);
	game->map = NULL;
}

int	fill_map(t_game *game, char *file)
{
    int		fd;
    char	*line;
    int		i;
    size_t	len;

    if ((fd = open(file, O_RDONLY)) == -1)
        return (0);

    i = 0;
    while (i < game->height)
    {
        if (!(line = get_next_line(fd)))
        {
            close(fd);
            return (0);
        }
        len = ft_strlen(line);
        if (len > 0 && line[len - 1] == '\n')
            line[len - 1] = '\0';
        ft_strlcpy(game->map[i], line, game->width + 1);
        free(line);
        i++;
    }
    close(fd);
    return (1);
}

int	allocate_map(t_game *game)
{
	int	i;

	game->map = (char **)malloc(sizeof(char *) * game->height);
	if (!game->map)
		return (0);
	i = 0;
	while (i < game->height)
	{
		game->map[i] = (char *)malloc(sizeof(char) * (game->width + 1));
		if (!game->map[i])
		{
			free_allocated_map(game, i);
			return (0);
		}
		i++;
	}
	return (1);
}

int	allocate_and_fill_map(t_game *game, char *file)
{
	if (!allocate_map(game))
		return (0);
	if (!fill_map(game, file))
	{
		free_allocated_map(game, game->height);
		return (0);
	}
	return (1);
}
