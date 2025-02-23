/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elel-bah <elel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 21:31:26 by elel-bah          #+#    #+#             */
/*   Updated: 2025/02/23 20:39:59 by elel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT_bonus.h"

char	*append_char_to_string(char *original, char new_char)
{
	char	*new_str;
	size_t	i;
	size_t	original_len;

	original_len = 0;
	if (original)
		while (original[original_len])
			original_len++;
	new_str = malloc((original_len + 2) * sizeof(char));
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
	free(original);
	return (new_str);
}

static char	*read_line(int fd, char *line)
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
				free(line);
				line = NULL;
				continue ;
			}
			break ;
		}
		line = append_char_to_string(line, c);
		if (!line)
			(close(fd), report_error("line allocation error"), exit(2));
	}
	return (line);
}

char	*line(int fd)
{
	static char	*line;

	line = NULL;
	if (line)
	{
		free(line);
		line = NULL;
	}
	line = read_line(fd, line);
	return (line);
}
