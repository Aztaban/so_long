/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjusta <mjusta@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 00:56:43 by mjusta            #+#    #+#             */
/*   Updated: 2025/06/16 01:56:32 by mjusta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static char	**convert_list_to_map(t_list *lines)
{
	int		i;
	int		height;
	char	**map;

	height = ft_lstsize(lines);
	map = malloc(sizeof(char *) * (height + 1));
	if (!map)
		return (NULL);
	i = 0;
	while (lines)
	{
		map[i] = lines->content;
		lines = lines->next;
		i++;
	}
	map[i] = NULL;
	return (map);
}

char	**read_map(const char *filename)
{
	int		fd;
	t_list	*lines;
	char	*line;
	char	**map;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL); //TODO error message
	lines = NULL;
	line = get_next_line(fd);
	while (line)
	{
		ft_lstadd_back(&lines, ft_lstnew(line));
		line = get_next_line(fd);
	}
	close(fd);
	if (!lines)
		return (NULL); //TODO error message
	map = convert_list_to_map(lines);
	ft_lstclear(&lines, NULL);
	return (map);
}