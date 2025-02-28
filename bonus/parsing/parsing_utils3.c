/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elel-bah <elel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 21:48:03 by elel-bah          #+#    #+#             */
/*   Updated: 2025/02/28 16:55:11 by elel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT_bonus.h"

void	validate_ambient_ratio_range_b(double ratio)
{
	if (ratio < 0 || ratio > 1)
		report_error_b("Ambient lighting ratio should be between 0.0 and 1.0.");
}

void	validate_ambient_input_b(char **args, t_world *scene)
{
	if (!args || !args[1] || !args[2] || args[3])
		report_error_b("Ambient lighting parameters are invalid!");
	if (scene->amb_light.light_count != 0)
		report_error_b("There can be only one ambient light source.");
}

void	validate_cylinder_diameter_b(double diameter, double height)
{
	if (diameter <= 0 || height <= 0)
		report_error_b("Cylinder diameter and height must both be positive.");
}

void	validate_cylinder_input_b(char **args)
{
	int	arg_count;

	arg_count = 0;
	if (!args || !args[1] || !args[2] || !args[3] || !args[4] || !args[5])
		report_error_b("Cylinder parameters are invalid.");
	while (args[arg_count])
		arg_count++;
	if (arg_count == 6)
		return ;
	else if (arg_count == 9 && ft_strcmp_b(args[6], "checker") == 0)
		return ;
	else
		report_error_b("Invalid number of arguments for cylinder.");
}

void	validate_cylinder_orientation_b(t_point3d dir)
{
	if (dir.x_coord > 1 || dir.y_coord > 1 || dir.z_coord > 1 \
		|| dir.x_coord < -1 || dir.y_coord < -1 || dir.z_coord < -1)
		report_error_b("Cylinder direction components must be between -1 and 1.");
}
