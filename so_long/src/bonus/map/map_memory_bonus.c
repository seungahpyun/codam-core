/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_memory_bonus.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/13 10:46:15 by spyun         #+#    #+#                 */
/*   Updated: 2024/12/24 09:48:51 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static bool    validate_map_size(t_game *game)
{
    if (!game)
        return (false);
    if (game->height <= 0 || game->width <= 0)
        return (false);
    if (game->height > MAX_MAP_HEIGHT || game->width > MAX_MAP_WIDTH)
        return (false);
    return (true);
}

void	free_allocated_map(t_game *game, int last_row)
{
	int	i;

	if (!game || !game->map)
		return ;
	i = 0;
	while (i < last_row)
	{
		if (game->map[i])
		{
			free(game->map[i]);
			game->map[i] = NULL;
		}
		i++;
	}
	free(game->map);
	game->map = NULL;
}


bool    allocate_map(t_game *game)
{
    int    i;

    if (!validate_map_size(game))
        return (false);
    game->map = (char **)malloc(sizeof(char *) * game->height);
    if (!game->map)
        return (false);
    i = 0;
    while (i < game->height)
    {
        game->map[i] = (char *)malloc(sizeof(char) * (game->width + 1));
        if (!game->map[i])
        {
            free_allocated_map(game, i);
            return (false);
        }
        game->map[i][game->width] = '\0';
        i++;
    }
    return (true);
}

static bool    process_line(t_game *game, char *line, int row)
{
    size_t    line_len;

    if (!line)
        return (false);
    line_len = ft_strlen(line);
    if (line[line_len - 1] == '\n')
    {
        line[line_len - 1] = '\0';
        line_len--;
    }
    if (line_len != (size_t)game->width)
        return (false);
    if (!ft_strlcpy(game->map[row], line, game->width + 1))
        return (false);
    return (true);
}

bool    fill_map(t_game *game, char *file)
{
    int        fd;
    char    *line;
    int        i;

    fd = open(file, O_RDONLY);
    if (fd == -1)
        return (false);
    i = 0;
    while (i < game->height)
    {
        line = get_next_line(fd);
        if (!process_line(game, line, i))
        {
            free(line);
            close(fd);
            return (false);
        }
        free(line);
        i++;
    }
    close(fd);
    return (true);
}
