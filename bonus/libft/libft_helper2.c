/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_helper2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elel-bah <elel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 09:50:18 by elel-bah          #+#    #+#             */
/*   Updated: 2024/12/30 17:25:38 by elel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT_bonus.h"

char	*ft_strdup(const char *s1)//need
{
	char	*dup;
	int		i;

	i = ft_strlen(s1);
	dup = (char *) malloc((sizeof(char) * i + 1));
	if (!dup)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		dup[i] = s1[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}


int	ft_strncmp(char *s1, const char *s2, size_t n)
{
	size_t			it;
	unsigned char	*str1;
	unsigned char	*str2;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	it = 0;
	while (s1[it] != '\0' && s2[it] != '\0' && it < n)
	{
		if (s1[it] != s2[it])
			return (s1[it] - s2[it]);
		++it;
	}
	if (it != n)
		return (s1[it] - s2[it]);
	return (0);
}

int ft_strcmp(const char *s1, const char *s2)
{
    if (!s1 || !s2) // Null-pointer check
        return (-1); // Return an error code or handle appropriately

    while (*s1 && *s2 && *s1 == *s2)
    {
        s1++;
        s2++;
    }
    return ((unsigned char)*s1 - (unsigned char)*s2);
}
