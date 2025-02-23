/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_helper3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elel-bah <elel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 16:48:31 by elel-bah          #+#    #+#             */
/*   Updated: 2025/02/23 16:56:40 by elel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT.h"

int	ft_strlcpy(char *dest, const char *source, int max_size)
{
	int	index;
	int	source_len;

	index = 0;
	source_len = ft_strlen((char *)source);
	if (!source)
		return (0);
	if (max_size == 0)
		return (source_len);
	while (source[index] && index < (max_size - 1))
	{
		dest[index] = source[index];
		index++;
	}
	dest[index] = '\0';
	return (source_len);
}
