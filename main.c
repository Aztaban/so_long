/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjusta <mjusta@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 23:58:01 by mjusta            #+#    #+#             */
/*   Updated: 2025/06/14 18:12:55 by mjusta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	exit_game(t_game *game)
{
	mlx_destroy_image(game->mlx_display, game->img.img);
	mlx_destroy_window(game->mlx_display, game->win);
	mlx_destroy_display(game->mlx_display);
	exit(0);
}

int	close_game(t_game *game)
{
	exit_game(game);
	return (0);
}

void	fill_screen(t_game *game, int color)
{
	int x;
	int y;

	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			my_mlx_pixel_put(&game->img, x, y, color);
			x++;
		}
		y++;
	}		
	mlx_put_image_to_window(game->mlx_display, game->win, game->img.img, 0 , 0);
}


int	main(void)
{
	t_game	game;
	
	game.mlx_display = mlx_init();
	game.win = mlx_new_window(game.mlx_display, WIN_WIDTH, WIN_HEIGHT, "Hello 42");
	game.img.img = mlx_new_image(game.mlx_display, WIN_WIDTH, WIN_HEIGHT);
	game.img.addr = mlx_get_data_addr(game.img.img, &game.img.bits_per_pixel, &game.img.line_length, &game.img.endian);
	mlx_key_hook(game.win, handle_keypress, &game);
	mlx_hook(game.win, 17, 0, close_game, &game);
	mlx_loop(game.mlx_display);
	return (0);
}
