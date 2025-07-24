/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjusta <mjusta@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 21:55:18 by mjusta            #+#    #+#             */
/*   Updated: 2025/07/24 02:25:53 by mjusta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	clear_text_area(t_game *game, int w, int h, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < h)
	{
		j = 0;
		while (j < w)
		{
			mlx_pixel_put(game->mlx_display, game->win, 10 + j, 5 + i, color);
			j++;
		}
		i++;
	}
}

void	draw_move_count(t_game *game)
{
	char	*count_str;
	char	*label;

	clear_text_area(game, 80, 20, 0x000000);
	count_str = ft_itoa(game->player.moves_count);
	label = ft_strjoin("Steps: ", count_str);
	free(count_str);
	mlx_string_put(game->mlx_display, game->win, 20, 20, 0xFFFFFF, label);
	free(label);
}
