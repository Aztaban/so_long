/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjusta <mjusta@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 00:56:43 by mjusta            #+#    #+#             */
/*   Updated: 2025/06/22 01:15:08 by mjusta           ###   ########.fr       */
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
		map[i] = ft_strdup(lines->content);
		if (!map[i])
		{
			while (i-- > 0)
				free(map[i]);
			free(map);
			return (NULL);
		}
		lines = lines->next;
		i++;
	}
	map[i] = NULL;
	return (map);
}

static t_list	*read_lines(int fd)
{
	t_list	*lines;
	t_list	*node;
	char	*line;
	char	*trim;

	lines = NULL;
	line = get_next_line(fd);
	while (line)
	{
		trim = ft_strtrim(line, "\n");
		free(line);
		node = ft_lstnew(trim);
		free(trim);
		if (!node)
		{
			ft_lstclear(&lines, free);
			return (NULL);
		}
		ft_lstadd_back(&lines, node);
		line = get_next_line(fd);
	}
	return (lines);
}

char	**read_map(const char *filename)
{
	int		fd;
	t_list	*lines;
	char	**map;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL);
	lines = read_lines(fd);
	close(fd);
	if (!lines)
		return (NULL);
	map = convert_list_to_map(lines);
	ft_lstclear(&lines, free);
	return (map);
}

void	free_map(char **map)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}
