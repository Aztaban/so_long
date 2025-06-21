/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjusta <mjusta@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 17:13:47 by mjusta            #+#    #+#             */
/*   Updated: 2025/06/21 22:41:17 by mjusta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void move_player(t_game *game, int keycode)
{
	(void)game;
	if(keycode == KEY_W)
		return ;
		//fill_screen(game, 0x00FF0000);
	else if(keycode == KEY_S)
		//fill_screen(game, 0x0000FF00);
		return ;
	else if(keycode == KEY_A)
		return ;
		//fill_screen(game, 0x000000FF);
	else if(keycode == KEY_D)
		return ;
		//fill_screen(game, 0xFFFFFFFF);
}

int	handle_keypress(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		exit_game(game);
	else if(keycode == KEY_W)
		move_player(game, KEY_W);
	else if(keycode == KEY_S)
		move_player(game, KEY_S);
	else if(keycode == KEY_A)
		move_player(game, KEY_A);
	else if(keycode == KEY_D)
		move_player(game, KEY_D);
	return (0);
}

/* void	fill_screen(t_game *game, int color)
{
	int x;
	int y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			my_mlx_pixel_put(&game->img, x, y, color);
			x++;
		}
		y++;
	}		
	mlx_put_image_to_window(game->mlx_display, game->win, game->img.img, 0 , 0);
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
} */