/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avoronko <avoronko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 18:44:18 by avoronko          #+#    #+#             */
/*   Updated: 2023/12/29 18:52:32 by avoronko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# ifndef FD_MAX
#  define FD_MAX 1024
# endif

# define KEY_W				119
# define KEY_A				97
# define KEY_S				115
# define KEY_D				100

# define KEY_UP  			65362
# define KEY_LEFT  			65361
# define KEY_RIGHT 			65363
# define KEY_DOWN  			65364

# define KEY_EXIT			65307

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include <stdbool.h>
# include <stdlib.h>
# include <limits.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include "../minilibx/mlx.h"
# include "libft/libft.h"
# include "ft_printf/ft_printf.h"

typedef struct t_start
{
	int		fd;
	int		heightmap;
	int		widthmap;
	int		playercount;
	int		colcount;
	int		exitcount;
	int		player_x;
	int		player_y;
	int		counter;
	int		collectables;

	char	**map;

	void	*floor;
	void	*wall;
	void	*player;
	void	*exit;
	void	*collectable;
	void	*mlx;
	void	*win;

}	t_complete;

int		ft_exit(t_complete *game);
void	throw_error(t_complete *game, char *str);
int		map_reading(t_complete *game, char **argv);
void	check_errors(t_complete *game);
void	path_check(t_complete *game);
void	initial_render(t_complete *game);
void	render_tile(t_complete *game, int y, int x);
void	take_images(t_complete *game);
int		handle_command(int command, t_complete *game);
char	*get_next_line(int fd);

#endif