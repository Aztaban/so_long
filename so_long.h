/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjusta <mjusta@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 23:58:18 by mjusta            #+#    #+#             */
/*   Updated: 2025/07/21 02:01:39 by mjusta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>

# include "mlx.h"
# include "libft.h"

# define TILE_SIZE 64

# define FLOOR '0'
# define WALL '1'
# define COLLECTIBLE 'C'
# define EXIT 'E'
# define PLAYER 'P'
# define FLOOD 'F'

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

# define SPR_UP 'U'
# define SPR_DOWN 'D'
# define SPR_LEFT 'L'
# define SPR_RIGHT 'R'

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img;

typedef struct s_player
{
	int		x;
	int		y;
	int		moves_count;
	char	sprite;
}				t_player;

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
	int		collectible_count;
	int		x_exit;
	int		y_exit;
}				t_map;

typedef struct s_sprite
{
	void	*up;
	void	*down;
	void	*left;
	void	*right;
}				t_sprite;

typedef struct s_textures
{
	void		*wall;
	void		*floor;
	void		*collectible;
	void		*exit;
	void		*exit_open;
	t_sprite	player;
	//t_sprite	enemy;
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

// control.c
int		handle_keypress(int keycode, t_game *game);

// game.c
void	init_game(t_game *game, const char *filename);
void	exit_game(t_game *game);
int		close_game(t_game *game);
void	exit_with_error(t_game *game, char *message);

// graphic.c
void	init_graphics(t_game *game);

// map.c
char	**read_map(const char *filename);
void	validate_map(t_game *game);
void	free_map(char **map);

// draw.c
void	draw_map(t_game *game);
void	draw_tile(t_game *game, char tile, int x, int y);

// validate_path.c
int		validate_path(t_game *game);

// ui.c
void	draw_move_count(t_game *game);

#endif