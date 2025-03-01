/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamrachi <hamrachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:21:28 by elel-bah          #+#    #+#             */
/*   Updated: 2025/03/01 16:42:55 by hamrachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT.h"

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

void	validate_vec_input(char **args)
{
	if (!args || !args[1] || !args[2] || args[3])
		report_error("Invalid vector format! Expected X,Y,Z.");
}

void	validate_sphere_input(char **args)
{
	if (!args || !args[1] || !args[2] || !args[3] || args[4])
		report_error("Sphere parameters are invalid.");
}

void	validate_sphere_diameter(double diameter)
{
	if (diameter <= 0)
		report_error("Invalid sphere diameter: must be positive.");
}
