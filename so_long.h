/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjusta <mjusta@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 23:58:18 by mjusta            #+#    #+#             */
/*   Updated: 2025/06/14 18:07:04 by mjusta           ###   ########.fr       */
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

# define WIN_WIDTH 800
# define WIN_HEIGHT 600

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

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_game
{
	void	*mlx_display;
	void	*win;
	t_data	img;
}				t_game;

void	exit_game(t_game *game);
void	fill_screen(t_game *game, int color);
int		handle_keypress(int keycode, t_game *game);

#endif