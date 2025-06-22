/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjusta <mjusta@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 23:58:18 by mjusta            #+#    #+#             */
/*   Updated: 2025/06/22 02:21:51 by mjusta           ###   ########.fr       */
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

# define TILE_SIZE 96

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

# define ERR_NOT_RECTANGULAR 1
# define ERR_INVALID_CHAR 2
# define ERR_PLAYER 3
# define ERR_EXIT 4
# define ERR_COLLECTIBLES 5
# define ERR_WRONG_PATH 6
# define ERR_WALLS 7

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_img;

typedef struct s_player
{
	int	x;
	int	y;
	int	moves_count;
}				t_player;

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
	int		collectible_count;
}				t_map;

typedef struct s_textures
{
	void	*wall;
	void	*floor;
	void	*collectible;
	void	*player;
	void	*exit;
}				t_textures;

typedef struct s_game
{
	void		*mlx_display;
	void		*win;
	t_img		img;
	t_map		map;
	t_player	player;
	t_textures	textures;
}				t_game;

typedef struct s_count
{
	int	player;
	int	exit;
	int	collectibles;
}				t_count;

int		handle_keypress(int keycode, t_game *game);

// game.c
void	init_game(t_game *game, const char *filename);
void	exit_game(t_game *game);
int		close_game(t_game *game);

// graphic.c
void	init_graphics(t_game *game);

// helpers.c
void	exit_with_error(t_game *game, char *message);

// map.c
char	**read_map(const char *filename);
void	validate_map(t_game *game);
void	free_map(char **map);

// draw.c
void	draw_map(t_game *game);

#endif