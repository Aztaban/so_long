/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjusta <mjusta@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 18:29:01 by mjusta            #+#    #+#             */
/*   Updated: 2025/06/13 18:41:01 by mjusta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft_memory.h"
#include "libft_string.h"

void	*free_stash(char **stash)
{
	if (stash && *stash)
		free(*stash);
	if (stash)
		*stash = NULL;
	return (NULL);
}

void	ft_strjoin_free_stash(char **stash, char const *s2)
{
	char	*result;
	size_t	len1;
	size_t	len2;

	if (!*stash)
		*stash = ft_strdup("");
	if (!*stash || !s2)
		return ;
	len1 = ft_strlen(*stash);
	len2 = ft_strlen(s2);
	result = (char *)malloc(len1 + len2 + 1);
	if (!result)
	{
		free_stash(stash);
		return ;
	}
	ft_memcpy(result, *stash, len1);
	ft_memcpy(result + len1, s2, len2);
	result[len1 + len2] = '\0';
	free(*stash);
	*stash = result;
}

char	*extract_and_trim(char **stash)
{
	size_t	len;
	char	*line;
	char	*new_stash;

	len = 0;
	if (!*stash || **stash == '\0')
		return (NULL);
	while ((*stash)[len] && (*stash)[len] != '\n')
		len++;
	if ((*stash)[len] == '\n')
		len++;
	line = ft_substr(*stash, 0, len);
	if (!(*stash)[len])
		return (free_stash(stash), line);
	new_stash = ft_strdup(*stash + len);
	if (!new_stash || *new_stash == '\0')
	{
		free(new_stash);
		return (free_stash(stash), line);
	}
	free(*stash);
	*stash = new_stash;
	return (line);
}

void	fill_stash(int fd, char **stash, char *buffer)
{
	int		bytes_read;

	if (!*stash)
		*stash = ft_strdup("");
	if (!*stash)
		return ;
	while (!ft_strchr(*stash, '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read <= 0)
			break ;
		buffer[bytes_read] = '\0';
		ft_strjoin_free_stash(stash, buffer);
		if (!*stash)
			return ;
	}
}
