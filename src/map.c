/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avoronko <avoronko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 18:30:54 by avoronko          #+#    #+#             */
/*   Updated: 2023/12/29 18:24:11 by avoronko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

static int	get_width(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	if (str[i - 1] == '\n')
		i--;
	return (i);
}

static int	height_read(t_complete *game, char *line)
{
	char	**tmp;
	int		i;

	if (!line)
		return (0);
	i = 0;
	game->heightmap++;
	tmp = (char **)malloc(sizeof(char *) * (game->heightmap + 1));
	if (tmp == NULL)
		throw_error(game, "\nMemory allocation failed\n");
	tmp[game->heightmap] = NULL;
	while (i < game->heightmap - 1)
	{
		tmp[i] = game->map[i];
		i++;
	}
	tmp[i] = line;
	if (game->map)
		free(game->map);
	game->map = tmp;
	return (1);
}

static bool	is_ber(const char *av)
{
	char	*str;

	str = ft_strchr(av, '.');
	if (str)
		return (ft_strcmp(str, ".ber") == 0);
	return (false);
}

void	map_player(t_complete *game)
{
	int		y;
	int		x;
	bool	player_found;

	y = 0;
	player_found = false;
	while (y < game->heightmap && !player_found) 
	{
		x = 0;
		while (x < game->widthmap) 
		{
			if (game->map[y][x] == 'P') 
			{
				game->player_x = x;
				game->player_y = y;
				player_found = true;
				break ;
			}
			x++;
		}
		y++;
	}
	if (!player_found) 
		throw_error(game, "Player starting position not found in the map\n");
}

int	map_reading(t_complete *game, char **av)
{
	char	*line;

	if (!(is_ber(av[1])))
		throw_error(game, "\nThe format of the map is not supported\n");
	game->fd = open(av[1], O_RDONLY);
	if (game->fd < 0)
		throw_error(game, "\nFailed to read the map\n");
	while (1)
	{
		line = get_next_line(game->fd);
		if (!height_read(game, line))
			break ;
	}
	close (game->fd);
	game->widthmap = get_width(game->map[0]);
	map_player(game);
	return (1);
}
