/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjusta <mjusta@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 17:41:24 by mjusta            #+#    #+#             */
/*   Updated: 2025/06/13 18:31:14 by mjusta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*buffer;
	char		*next_line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (free_stash(&stash));
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (free_stash(&stash));
	fill_stash(fd, &stash, buffer);
	free(buffer);
	if (!stash || *stash == '\0')
		return (free_stash(&stash));
	next_line = extract_and_trim(&stash);
	if (!next_line)
		return (free_stash(&stash));
	return (next_line);
}

char	*get_next_line_multi_fd(int fd)
{
	static char	*stash[MAX_FD];
	char		*buffer;
	char		*next_line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (free_stash(&stash[fd]));
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (free_stash(&stash[fd]));
	fill_stash(fd, &stash[fd], buffer);
	free(buffer);
	if (!stash[fd] || *stash[fd] == '\0')
		return (free_stash(&stash[fd]));
	next_line = extract_and_trim(&stash[fd]);
	if (!next_line)
		return (free_stash(&stash[fd]));
	return (next_line);
}

/* 
#include <stdio.h>
int	main(void)
{
	char *test_stash = ft_strdup("Hello\n42\nWorld");
	//char *str = " of Warcraft";
	//printf("%s World", extract_line(test_stash));

	test_stash = trim_stash(test_stash);
	
	//test_stash = ft_strjoin_free_stash(test_stash, str);
	printf("%s", test_stash);
	free(test_stash);
}
*/
/* 
#include <stdio.h>
#include <fcntl.h>
int	main(void)
{
	int fd = open("test.txt", O_RDONLY);
	if (fd < 0)
		return (1);
	char *line = "";
	while (line)
	{
		line = get_next_line(fd);
		if (!line)
			break;
    	printf("Line: %s", line);
    	free(line);	
	}
	
	close(fd);
	return (0);
} */
