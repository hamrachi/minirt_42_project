/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamrachi <hamrachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 21:48:03 by elel-bah          #+#    #+#             */
/*   Updated: 2025/03/01 16:42:58 by hamrachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT.h"

void	validate_ambient_ratio_range(double ratio)
{
	if (ratio < 0 || ratio > 1)
		report_error("Ambient lighting ratio should be between 0.0 and 1.0.");
}

void	validate_ambient_input(char **args, t_world *scene)
{
	if (!args || !args[1] || !args[2] || args[3])
		report_error("Ambient lighting parameters are invalid!");
	if (scene->amb_light.light_count != 0)
		report_error("There can be only one ambient light source.");
}

void	validate_cylinder_diameter(double diameter, double height)
{
	if (diameter <= 0 || height <= 0)
		report_error("Cylinder diameter and height must both be positive.");
}

void	validate_cylinder_input(char **args)
{
	if (!args || !args[1] || !args[2] || !args[3] || \
			!args[4] || !args[5] || args[6])
		report_error("Invalid cylinder arguments.");
}

void	validate_cylinder_orientation(t_point3d dir)
{
	if (dir.x_coord > 1 || dir.y_coord > 1 || dir.z_coord > 1 \
		|| dir.x_coord < -1 || dir.y_coord < -1 || dir.z_coord < -1)
		report_error("Cylinder direction components must be between -1 and 1.");
}
