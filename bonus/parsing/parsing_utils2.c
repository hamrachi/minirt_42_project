/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elel-bah <elel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:21:28 by elel-bah          #+#    #+#             */
/*   Updated: 2025/02/23 21:55:32 by elel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT_bonus.h"

void	validate_color_input(char **args)
{
	if (!args || !args[1] || !args[2] || args[3])
		report_error("Invalid color format! Expected R,G,B.");
}

void	validate_color_range(t_point3d color)
{
	if (color.x_coord < 0 || color.y_coord < 0 || color.z_coord < 0 \
		|| color.x_coord > 255 || color.y_coord > 255 || color.z_coord > 255)
		report_error("Color values must be in the range [0, 255].");
}

//========

void	validate_vec_input(char **args)
{
	if (!args || !args[1] || !args[2] || args[3])
		report_error("Invalid vector format! Expected X,Y,Z.");
}

void	validate_sphere_input(char **args)
{
	int	arg_count;

	arg_count = 0;
	if (!args || !args[1] || !args[2] || !args[3])
		report_error("Sphere parameters are invalid.");
	while (args[arg_count])
		arg_count++;
	if (arg_count == 4)
		return ;
	else if (arg_count == 7 && ft_strcmp(args[4], "checker") == 0)
		return ;
	else if (arg_count == 8 && ft_strcmp(args[4], "texture") == 0)
		return ;
	else
		report_error("Invalid sphere format. Use one of:\n"
			"sp x,y,z diameter r,g,b\n"
			"sp x,y,z diameter r,g,b checker size r2,g2,b2\n"
			"sp x,y,z diameter r,g,b texture path scale_u scale_v");
}

void	validate_sphere_diameter(double diameter)
{
	if (diameter <= 0)
		report_error("Invalid sphere diameter: must be positive.");
}
