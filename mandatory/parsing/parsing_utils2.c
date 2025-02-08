/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elel-bah <elel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:21:28 by elel-bah          #+#    #+#             */
/*   Updated: 2025/01/30 17:37:50 by elel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT.h"

// Helper function to validate the color parameters (input format)
void validate_color_input(char **args)
{
    if (!args || !args[1] || !args[2] || args[3])
        report_error("Invalid color format! Expected R,G,B.");
}

// Helper function to validate the color range
void validate_color_range(t_point3d color)
{
    if (color.x_coord < 0 || color.y_coord < 0 || color.z_coord < 0 || 
        color.x_coord > 255 || color.y_coord > 255 || color.z_coord > 255)
        report_error("Color values must be in the range [0, 255].");
}

//========

void validate_vec_input(char **args)
{
    if (!args || !args[1] || !args[2] || args[3])
        report_error("Invalid vector format! Expected X,Y,Z.");
}
//=-=-=-

// Helper function to validate sphere input (args and count)
void validate_sphere_input(char **args)
{
    if (!args || !args[1] || !args[2] || !args[3] || args[4])
        report_error("Sphere parameters are invalid.");
}

// Helper function to validate the sphere diameter
void validate_sphere_diameter(double diameter)
{
    if (diameter <= 0)
        report_error("Invalid sphere diameter: must be positive.");
}
//=========

// Helper function to validate cylinder input (args and count)
void validate_cylinder_input(char **args)
{
    if (!args || !args[1] || !args[2] || !args[3] || \
			!args[4] || !args[5] || args[6])
        report_error("Invalid cylinder arguments.");
}

// Helper function to validate the cylinder orientation
void validate_cylinder_orientation(t_point3d dir)
{
    if (dir.x_coord > 1 || dir.y_coord > 1 || dir.z_coord > 1 || \
			dir.x_coord < -1 || dir.y_coord < -1 || dir.z_coord < -1)
        report_error("Cylinder direction components must be between -1 and 1.");
}