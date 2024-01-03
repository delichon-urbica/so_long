/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avoronko <avoronko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 18:30:43 by avoronko          #+#    #+#             */
/*   Updated: 2023/12/29 20:48:39 by avoronko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

static int	check_map_rectangular(t_complete *game)
{
	int	y;
	int	first_row_length;
	int	i;
	int	row_length;

	y = 0;
	first_row_length = 0;
	while (game->map[y] != NULL)
	{
		row_length = 0;
		i = 0;
		while (game->map[y][i] && game->map[y][i] != '\n')
		{
			row_length++;
			i++;
		}
		if (y == 0)
			first_row_length = row_length;
		else if (row_length != first_row_length)
			return (0);
		y++;
	}
	return (1);
}

static int	check_walls(t_complete *game)
{
	int	height;
	int	width;

	height = 0;
	width = 0;
	while (height < game->heightmap)
	{
		if (game->map[height][0] != '1' 
			|| game->map[height][game->widthmap - 1] != '1')
			return (0);
		height++;
	}
	height = 0;
	while (width < game->widthmap)
	{
		if (game->map[0][width] != '1' 
			|| game->map[game->heightmap - 1][width] != '1')
			return (0);
		width++;
	}
	return (1);
}

static void	count_checker(t_complete *game, int height, int width)
{
	if (game->map[height][width] != '1' &&
		game->map[height][width] != '0' &&
		game->map[height][width] != 'P' &&
		game->map[height][width] != 'E' &&
		game->map[height][width] != 'C' &&
		game->map[height][width] != '\n')
		throw_error(game, "\nInvalid characters in the map\n");
	if (game->map[height][width] == 'C')
		game->colcount++;
	if (game->map[height][width] == 'P')
		game->playercount++;
	if (game->map[height][width] == 'E')
		game->exitcount++;
}

void	character_valid(t_complete *game)
{
	int	y;
	int	x;

	y = 0;
	while (y < game->heightmap - 1)
	{
		x = 0;
		while (x < game->widthmap)
		{
			count_checker(game, y, x);
			x++;
		}
		y++;
	}
}

void	check_errors(t_complete *game)
{
	character_valid(game);
	if (!(game->playercount == 1 && game->colcount >= 1 
			&& game->exitcount == 1))
		throw_error(game, "\nError in the map\n");
	if (!check_map_rectangular(game))
		throw_error(game, "\nThe map is not rectangular\n");
	if (!check_walls(game))
		throw_error(game, "\nThe map is not properly enclosed\n");
}
