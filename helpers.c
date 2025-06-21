/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjusta <mjusta@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 00:07:05 by mjusta            #+#    #+#             */
/*   Updated: 2025/06/22 00:26:12 by mjusta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	exit_with_error(t_game *game, char *message)
{
	ft_putstr_fd("Error: ", 2);
	ft_putstr_fd(message, 2);
	ft_putchar_fd('\n', 2);
	exit_game(game);
}
