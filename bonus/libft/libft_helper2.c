/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_helper2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elel-bah <elel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 09:50:18 by elel-bah          #+#    #+#             */
/*   Updated: 2025/02/01 09:53:02 by elel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT_bonus.h"

char *ft_strdup(const char *source)
{
    char *duplicate;
    int index;

    index = ft_strlen(source);
    duplicate = (char *)malloc((sizeof(char) * index + 1));
    if (!duplicate)
        return (NULL);
    index = 0;
    while (source[index])
    {
        duplicate[index] = source[index];
        index++;
    }
    duplicate[index] = '\0';
    return (duplicate);
}

int ft_strncmp(char *first_str, const char *second_str, size_t max_len)
{
    size_t iterator;
    unsigned char *str1;
    unsigned char *str2;

    str1 = (unsigned char *)first_str;
    str2 = (unsigned char *)second_str;
    iterator = 0;
    while (first_str[iterator] != '\0' && second_str[iterator] != '\0' 
           && iterator < max_len)
    {
        if (first_str[iterator] != second_str[iterator])
            return (first_str[iterator] - second_str[iterator]);
        ++iterator;
    }
    if (iterator != max_len)
        return (first_str[iterator] - second_str[iterator]);
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
