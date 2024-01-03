/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avoronko <avoronko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 18:47:55 by avoronko          #+#    #+#             */
/*   Updated: 2023/12/30 17:41:02 by avoronko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

void	free_temp_map(t_complete *game, char **temp_map)
{
	int	i;

	i = 0;
	while (i < game->heightmap)
	{
		free(temp_map[i]);
		i++;
	}
	free(temp_map);
}

void	flood_fill(t_complete *game, int y, int x, char **temp_map)
{
	if (x < 0 || x >= game->widthmap || y < 0 || y >= game->heightmap)
		return ;
	if (temp_map[y][x] == '1' || temp_map[y][x] == 'F')
		return ;
	if (temp_map[y][x] == 'E' || temp_map[y][x] == 'X') 
		temp_map[y][x] = 'X'; 
	else
		temp_map[y][x] = 'F';
	flood_fill(game, y, x + 1, temp_map);
	flood_fill(game, y, x - 1, temp_map);
	flood_fill(game, y + 1, x, temp_map);
	flood_fill(game, y - 1, x, temp_map);
}

void	check_reachability(t_complete *game, char **temp_map)
{
	int	i;
	int	j;
	int	exit_y;
	int	exit_x;
	int	exit_found;

	i = -1;
	exit_found = 0;
	while (++i < game->heightmap)
	{
		j = -1;
		while (++j < game->widthmap)
		{
			if (temp_map[i][j] == 'C')
				throw_error(game, "\nNot all collectibles are reachable\n");
			if (temp_map[i][j] == 'X') 
			{
				exit_found = 1;
				exit_y = i;
				exit_x = j;
			}
		}
	}
	if (!exit_found || temp_map[exit_y][exit_x] != 'X')
	{
		free_temp_map(game, temp_map);
		throw_error(game, "\nThe exit is not reachable\n");
	}
}

void	create_temp_map(t_complete *game, char ***temp_map)
{
	int	i;
	int	j;

	*temp_map = malloc(sizeof(char *) * game->heightmap);
	if (!(*temp_map))
		throw_error(game, "\nMemory allocation failed for temp_map\n");
	i = 0;
	while (i < game->heightmap)
	{
		(*temp_map)[i] = malloc(sizeof(char) * (game->widthmap + 1));
		if (!(*temp_map)[i])
			throw_error(game, "\nMemory allocation failed for temp_map row\n");
		j = 0;
		while (j < game->widthmap)
		{
			(*temp_map)[i][j] = game->map[i][j];
			j++;
		}
		(*temp_map)[i][j] = '\0';
		i++;
	}
}


void	path_check(t_complete *game)
{
	char	**temp_map;

	create_temp_map(game, &temp_map);
	flood_fill(game, game->player_y, game->player_x, temp_map);
	check_reachability(game, temp_map);
	free_temp_map(game, temp_map);
}
