/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elel-bah <elel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 21:31:26 by elel-bah          #+#    #+#             */
/*   Updated: 2025/02/28 15:50:33 by elel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT_bonus.h"

char	*append_char_to_string(char *original, char new_char, t_heap_track **g_garbage_collector)
{
	char	*new_str;
	size_t	i;
	size_t	original_len;

	original_len = 0;
	if (original)
		while (original[original_len])
			original_len++;
	new_str = gc_malloc(g_garbage_collector, (original_len + 2) * sizeof(char));
	if (!new_str)
		return (NULL);
	i = 0;
	while (i < original_len)
	{
		new_str[i] = original[i];
		i++;
	}
	new_str[original_len] = new_char;
	new_str[original_len + 1] = '\0';
	return (new_str);
}

static char	*read_line(int fd, char *line, t_heap_track **g_garbage_collector)
{
	char	c;

	while (read(fd, &c, 1))
	{
		if (c == '\n' && line == NULL)
			continue ;
		if (c == '\n')
		{
			if (line && line[0] == '#')
			{
				line = NULL;
				continue ;
			}
			break ;
		}
		line = append_char_to_string(line, c, g_garbage_collector);
		if (!line)
			(close(fd), report_error("line allocation error"), exit(2));
	}
	return (line);
}

char	*line(int fd, t_heap_track **g_garbage_collector)
{
	static char	*line;

	line = NULL;
	line = read_line(fd, line, g_garbage_collector);
	return (line);
}
