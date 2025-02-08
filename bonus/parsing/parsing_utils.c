/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elel-bah <elel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:50:19 by elel-bah          #+#    #+#             */
/*   Updated: 2024/12/23 16:51:29 by elel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT_bonus.h"

// Helper function to validate camera parameters (args and count)
void validate_camera_input(char **args, t_scene *scene)
{
    if (!args || !args[1] || !args[2] || !args[3] || args[4])
        report_error("Invalid camera arguments.");
    if (scene->cam.count != 0)
        report_error("Only one camera is allowed.");
}

// Helper function to validate camera direction (orientation)
void validate_camera_orientation(t_vec dir)
{
    if (dir.x > 1 || dir.y > 1 || dir.z > 1)
        report_error("Camera direction components must be between -1 and 1.");
    if (dir.x < -1 || dir.y < -1 || dir.z < -1)
        report_error("Camera orientation cannot be a zero vector (0, 0, 0).");
    if (dir.x == 0 && dir.y == 0 && dir.z == 0)
        report_error("FOV must lie within the range [0, 180]");
}

// Helper function to validate camera FOV (field of view)
void validate_camera_fov(double fov)
{
    if (fov < 0 || fov > 180)
        report_error("FOV must be in the range [0, 180].");
}
//=-=-=-=-=-

// Helper function to validate light parameters (args and count)
void validate_light_input(char **args)
{
    if (!args || !args[1] || !args[2] || !args[3] || args[4])
        report_error("Light parameters are invalid.");
}

// Helper function to validate light brightness ratio
void validate_light_ratio(double ratio)
{
    if (ratio < 0 || ratio > 1)
        report_error("Light brightness ratio must lie between 0.0 and 1.0.");
}