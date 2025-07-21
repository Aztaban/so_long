/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjusta <mjusta@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 23:39:07 by mjusta            #+#    #+#             */
/*   Updated: 2025/07/21 23:56:20 by mjusta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	free_sprite(t_game *game, t_sprite *sprite)
{
	if (sprite->up)
		mlx_destroy_image(game->mlx_display, sprite->up);
	if (sprite->down)
		mlx_destroy_image(game->mlx_display, sprite->down);
	if (sprite->left)
		mlx_destroy_image(game->mlx_display, sprite->left);
	if (sprite->right)
		mlx_destroy_image(game->mlx_display, sprite->right);
}

static void	free_textures(t_game *game)
{
	free_sprite(game, &game->textures.player);
	free_sprite(game, &game->textures.collectible);
	if (game->textures.wall)
		mlx_destroy_image(game->mlx_display, game->textures.wall);
	if (game->textures.floor)
		mlx_destroy_image(game->mlx_display, game->textures.floor);
	if (game->textures.exit)
		mlx_destroy_image(game->mlx_display, game->textures.exit);
	if (game->img.img)
		mlx_destroy_image(game->mlx_display, game->img.img);
}

void	exit_game(t_game *game)
{
	free_textures(game);
	if (game->win)
		mlx_destroy_window(game->mlx_display, game->win);
	if (game->mlx_display)
	{
		mlx_destroy_display(game->mlx_display);
		free(game->mlx_display);
	}
	if (game->map.grid)
		free_map(game->map.grid);
	exit(EXIT_SUCCESS);
}

int	close_game(t_game *game)
{
	exit_game(game);
	return (EXIT_SUCCESS);
}

void	exit_with_error(t_game *game, char *message)
{
	ft_putstr_fd("Error\n", STDERR_FILENO);
	if (message)
	{
		ft_putstr_fd(message, STDERR_FILENO);
		if (errno)
		{
			ft_putstr_fd(": ", STDERR_FILENO);
			ft_putstr_fd(strerror(errno), STDERR_FILENO);
		}
		ft_putchar_fd('\n', STDERR_FILENO);
	}
	if (game)
		exit_game(game);
	else
		exit(EXIT_FAILURE);
}
