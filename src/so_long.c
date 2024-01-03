/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avoronko <avoronko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 18:31:04 by avoronko          #+#    #+#             */
/*   Updated: 2024/01/03 14:14:06 by avoronko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

void	throw_error(t_complete *game, char *str)
{
	int	line;

	line = 0;
	ft_printf("%s\n", str);
	while (line < game->heightmap)
		free(game->map[line++]);
	free(game->map);
	exit(EXIT_FAILURE);
}

int	ft_exit(t_complete *game)
{
	int	line;

	line = 0;
	if (game->floor)
		mlx_destroy_image(game->mlx, game->floor);
	if (game->wall)
		mlx_destroy_image(game->mlx, game->wall);
	if (game->player)
		mlx_destroy_image(game->mlx, game->player);
	if (game->exit)
		mlx_destroy_image(game->mlx, game->exit);
	if (game->collectable)
		mlx_destroy_image(game->mlx, game->collectable);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	while (line < game->heightmap)
		free(game->map[line++]);
	free(game->map);
	exit(EXIT_SUCCESS);
}

int	main(int ac, char **av)
{
	t_complete	game;
	
	ft_bzero(&game, sizeof(t_complete));
	if (ac != 2)
		throw_error(&game, "\nInvalid number of arguments\n");
	map_reading(&game, av);
	check_errors(&game);
	path_check(&game);
	game.mlx = mlx_init();
	if (!game.mlx)
		throw_error(&game, "\nFailed to initiate the library\n");
	game.win = mlx_new_window(game.mlx, (game.widthmap * 50),
			(game.heightmap * 50), "solong");
	if (!game.win)
		throw_error(&game, "\nFailed to create a window\n");
	take_images(&game);
	initial_render(&game);
	mlx_key_hook(game.win, handle_command, &game);
	mlx_hook(game.win, 17, 0, (void *)exit, 0);
	mlx_loop(game.mlx);
}
