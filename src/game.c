/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjusta <mjusta@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 00:56:33 by mjusta            #+#    #+#             */
/*   Updated: 2025/08/04 00:33:25 by mjusta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// Checks if the given filename ends with ".ber".
// Returns 1 if true, 0 otherwise.
static int	is_ber_file(const char *filename)
{
	size_t	len;

	len = ft_strlen(filename);
	if (len > 4)
		return (ft_strncmp(filename + len - 4, ".ber", 4) == 0);
	return (0);
}

// Initializes the game by loading and validating the map,
// setting up graphics, and rendering the initial map state.
// Exits with error if any step fails.
void	init_game(t_game *game, const char *filename)
{
	if (!is_ber_file(filename))
		exit_with_error(NULL, "Map is not .ber file");
	ft_bzero(game, sizeof(t_game));
	game->map.grid = read_map(filename);
	if (!game->map.grid)
		exit_with_error(game, "Map file could not be open or read");
	validate_map(game);
	init_graphics(game);
	draw_map(game);
}
