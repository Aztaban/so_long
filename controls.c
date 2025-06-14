/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjusta <mjusta@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 17:13:47 by mjusta            #+#    #+#             */
/*   Updated: 2025/06/14 18:01:21 by mjusta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void move_player(t_game *game, int keycode)
{
	if(keycode == KEY_W)
		fill_screen(game, 0x00FF0000);
	else if(keycode == KEY_S)
		fill_screen(game, 0x0000FF00);
	else if(keycode == KEY_A)
		fill_screen(game, 0x000000FF);
	else if(keycode == KEY_D)
		fill_screen(game, 0xFFFFFFFF);
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
