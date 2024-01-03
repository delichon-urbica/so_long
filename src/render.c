/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avoronko <avoronko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 18:30:59 by avoronko          #+#    #+#             */
/*   Updated: 2023/12/29 17:21:44 by avoronko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

void	take_images(t_complete *game)
{
	int	i;
	int	j;

	game->floor = mlx_xpm_file_to_image(game->mlx,
			"game_images/floor.xpm", &i, &j);
	game->wall = mlx_xpm_file_to_image(game->mlx,
			"game_images/wall.xpm", &i, &j);
	game->player = mlx_xpm_file_to_image(game->mlx,
			"game_images/player.xpm", &i, &j);
	game->exit = mlx_xpm_file_to_image(game->mlx,
			"game_images/exit.xpm", &i, &j);
	game->collectable = mlx_xpm_file_to_image(game->mlx,
			"game_images/item.xpm", &i, &j);
}

void	render_tile(t_complete *game, int y, int x)
{
	char	tile;
	void	*image_to_render;

	image_to_render = NULL;
	tile = game->map[y][x];
	if (tile == 'P')
		image_to_render = game->player;
	else if (tile == '0')
		image_to_render = game->floor;
	else if (tile == 'C')
		image_to_render = game->collectable;
	else if (tile == '1')
		image_to_render = game->wall;
	else if (tile == 'E')
		image_to_render = game->exit;
	if (image_to_render != NULL)
		mlx_put_image_to_window(game->mlx, game->win, 
			image_to_render, x * 50, y * 50);
}

void	initial_render(t_complete *game)
{
	int	y;
	int	x;

	game->collectables = 0;
	y = 0;
	while (y < game->heightmap)
	{
		x = 0;
		while (game->map[y][x])
		{
			render_tile(game, y, x);
			if (game->map[y][x] == 'C')
				game->collectables++;
			x++;
		}
		y++;
	}
}
