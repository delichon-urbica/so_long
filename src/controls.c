/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avoronko <avoronko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 18:30:20 by avoronko          #+#    #+#             */
/*   Updated: 2023/12/29 17:34:28 by avoronko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

void	ft_win(t_complete *game)
{
	if (game->collectables != 0)
	{
		ft_printf("\nYou have left something behind!\n");
		return ;
	}
	ft_printf("\nToodaloo!\n");
	ft_exit(game);
}

void	ft_move(t_complete *game, int new_y, int new_x)
{
	char	new_pos;

	if (new_x < 0 || new_x >= game->widthmap 
		|| new_y < 0 || new_y >= game->heightmap)
		return ;
	new_pos = game->map[new_y][new_x];
	if (new_pos == 'E')
		ft_win(game);
	else if (new_pos == '0' || new_pos == 'C')
	{
		game->map[game->player_y][game->player_x] = '0';
		render_tile(game, game->player_y, game->player_x);
		game->map[new_y][new_x] = 'P';
		game->player_x = new_x;
		game->player_y = new_y;
		render_tile(game, game->player_y, game->player_x);
		game->counter++;
		if (new_pos == 'C')
			game->collectables--;
		ft_printf("Steps: %i\n", game->counter);
		ft_printf("Collectables left: %i\n", game->collectables);
	}
}

int	handle_command(int command, t_complete *game)
{
	if (command == KEY_EXIT)
		ft_exit(game);
	else if (command == KEY_DOWN || command == KEY_S)
		ft_move(game, game->player_y + 1, game->player_x);
	else if (command == KEY_LEFT || command == KEY_A)
		ft_move(game, game->player_y, game->player_x - 1);
	else if (command == KEY_RIGHT || command == KEY_D)
		ft_move(game, game->player_y, game->player_x + 1);
	else if (command == KEY_UP || command == KEY_W)
		ft_move(game, game->player_y - 1, game->player_x);
	return (1);
}
