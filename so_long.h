/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjusta <mjusta@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 23:58:18 by mjusta            #+#    #+#             */
/*   Updated: 2025/06/16 01:20:12 by mjusta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

// for testing
# include <stdio.h>

# include "mlx/mlx.h"
# include "libft/include/libft.h"

# define WIDTH 800
# define HEIGHT 600

# define FLOOR '0'
# define WALL '1'
# define COLLECTIBLE 'C'
# define EXIT 'E'
# define PLAYER 'P'

# define KEY_ESC 65307
# define KEY_W 119
# define KEY_S 115
# define KEY_A 97
# define KEY_D 100

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_player
{
	int	x;
	int	y;
	int	moves_count;
}	t_player;

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
	int		collectible_count;
}	t_map;

typedef struct s_game
{
	void		*mlx_display;
	void		*win;
	t_img		img;
	t_map		map;
	t_player	player;
}				t_game;

void	fill_screen(t_game *game, int color);
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
int		handle_keypress(int keycode, t_game *game);

// game.c
void	init_game(t_game *game, const char *filename);
void	exit_game(t_game *game);
int		close_game(t_game *game);

// map.c
char	**read_map(const char *filename);
void	validate_map(char **map);
void	free_map(char **map);

// draw.c
void	draw_map(t_game *game);

#endif