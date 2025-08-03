/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjusta <mjusta@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 23:58:18 by mjusta            #+#    #+#             */
/*   Updated: 2025/08/04 00:50:31 by mjusta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

// so_long.h - Main header for the So Long game project.
// Defines constants, types, and function prototypes used throughout the game.
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>

# include "mlx.h"
# include "libft.h"

// === General Config ===
# define TILE_SIZE 64
# define FRAME_COUNT 4

// === Map Symbols ===
# define FLOOR '0'
# define WALL '1'
# define COLLECTIBLE 'C'
# define EXIT 'E'
# define PLAYER 'P'
# define FLOOD 'F'
# define ENEMY 'X'

// === Key Codes (WASD + ESC) ===
# define KEY_ESC 65307
# define KEY_W 119
# define KEY_S 115
# define KEY_A 97
# define KEY_D 100

// === Error Codes ===
# define ERR_NOT_RECTANGULAR 1
# define ERR_INVALID_CHAR 2
# define ERR_PLAYER 3
# define ERR_EXIT 4
# define ERR_COLLECTIBLES 5
# define ERR_WRONG_PATH 6
# define ERR_WALLS 7

// === Sprite Directions ===
# define SPR_DOWN 0
# define SPR_LEFT 1
# define SPR_RIGHT 2
# define SPR_UP 3

// Image buffer metadata (for advanced MLX image use)
typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img;

// Player position, move counter, and last direction
typedef struct s_player
{
	int		x;
	int		y;
	int		moves_count;
	char	sprite;
}				t_player;

// Map grid and properties
typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
	int		collectible_count;
	int		x_exit;
	int		y_exit;
}				t_map;

// Holds multiple frames for animated sprites
typedef struct s_sprite
{
	void	*frame[FRAME_COUNT];
	int		current;
}				t_sprite;

// All loaded textures for the game
typedef struct s_textures
{
	void		*wall;
	void		*floor;
	void		*exit;
	void		*exit_open;
	t_sprite	collectible;
	t_sprite	player;
	t_sprite	enemy;
}				t_textures;

// Game-wide state and resources
typedef struct s_game
{
	void		*mlx_display;
	void		*win;
	t_img		img;
	t_map		map;
	t_player	player;
	t_textures	textures;
}				t_game;

// Counters used during map validation
typedef struct s_count
{
	int	player;
	int	exit;
	int	collectibles;
}				t_count;

// === Game Loop ===
int		game_loop(t_game *game);

// === Cleanup & Exit ===
void	exit_game(t_game *game);
int		close_game(t_game *game);
void	exit_with_error(t_game *game, char *message);

// === Controls ===
int		handle_keypress(int keycode, t_game *game);

// === Drawing ===
void	draw_map(t_game *game);
void	draw_tile(t_game *game, char tile, int x, int y);

// === Enemies ===
void	update_enemies(t_game *game);

// === Game Setup ===
void	init_game(t_game *game, const char *filename);
void	init_graphics(t_game *game);

// === Map Handling ===
char	**read_map(const char *filename);
void	free_map(char **map);

// === UI ===
void	draw_move_count(t_game *game);

// === Map Validation ===
void	validate_map(t_game *game);
int		validate_path(t_game *game);

#endif