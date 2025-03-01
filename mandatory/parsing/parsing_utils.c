/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamrachi <hamrachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:50:19 by elel-bah          #+#    #+#             */
/*   Updated: 2025/03/01 16:42:47 by hamrachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT.h"

void	validate_camera_input(char **args, t_world *scene)
{
	if (!args || !args[1] || !args[2] || !args[3] || args[4])
		report_error("Invalid camera arguments.");
	if (scene->camera.cam_count != 0)
		report_error("Only one camera is allowed.");
}

void	validate_camera_orientation(t_point3d dir)
{
	if (dir.x_coord > 1 || dir.y_coord > 1 || dir.z_coord > 1)
		report_error("Camera direction components must be between -1 and 1.");
	if (dir.x_coord < -1 || dir.y_coord < -1 || dir.z_coord < -1)
		report_error("Camera orientation cannot be a zero vector (0, 0, 0).");
	if (dir.x_coord == 0 && dir.y_coord == 0 && dir.z_coord == 0)
		report_error("FOV must lie within the range [0, 180]");
}

void	validate_camera_fov(double fov)
{
	if (fov < 0 || fov > 180)
		report_error("FOV must be in the range [0, 180].");
}

void	validate_light_input(char **args)
{
	if (!args || !args[1] || !args[2] || !args[3] || args[4])
		report_error("Light parameters are invalid.");
}

void	validate_light_ratio(double ratio)
{
	if (ratio < 0 || ratio > 1)
		report_error("Light brightness ratio must lie between 0.0 and 1.0.");
}
