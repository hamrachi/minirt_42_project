/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elel-bah <elel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 11:40:45 by elel-bah          #+#    #+#             */
/*   Updated: 2025/02/28 15:50:22 by elel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT.h"

double	parse_decimal_part(const char *str, int start_idx, \
		double whole_num, int sign)
{
	int		multiplier;
	int		i;
	double	result;

	multiplier = 10;
	i = start_idx;
	result = whole_num;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result + (double)(str[i] - '0') / multiplier;
		multiplier *= 10;
		i++;
	}
	return (result * sign);
}

double	ft_atod(const char *str)
{
	double	number;
	int		sign;
	int		i;

	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	sign = 1;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			sign = -1;
	number = 0;
	while (str[i] >= '0' && str[i] <= '9')
		number = number * 10 + (str[i++] - '0');
	if (str[i] != '.')
		return (number * sign);
	return (parse_decimal_part(str, i + 1, number, sign));
}

int	handle_number_conversion(const char *str, int start_idx, int sign)
{
	int	result;
	int	it;

	result = 0;
	it = start_idx;
	while (str[it] >= '0' && str[it] <= '9')
	{
		result = result * 10 + (str[it] - '0');
		it++;
	}
	return (result * sign);
}

int	ft_atoi(const char *str)
{
	int	it;
	int	sign;

	it = 0;
	sign = 1;
	while (str[it] == 32 || (str[it] >= 9 && str[it] <= 13))
		it++;
	if (str[it] == '-' || str[it] == '+')
	{
		if (str[it] == '-')
			sign = -1;
		it++;
	}
	return (handle_number_conversion(str, it, sign));
}
