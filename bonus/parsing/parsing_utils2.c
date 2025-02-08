/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elel-bah <elel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:21:28 by elel-bah          #+#    #+#             */
/*   Updated: 2025/01/30 17:49:17 by elel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT_bonus.h"
//=--=-=-=-=-=
void valid_orient_cone_range(t_point3d direction)
{
   if (direction.x_coord > 1 || direction.y_coord > 1 || direction.z_coord > 1)
		report_error("invalid orientation cone");
	if (direction.x_coord < -1 || direction.y_coord < -1 || direction.z_coord < -1)
		report_error("invalid orientation cone"); 
}

void validate_cone_input(char **args)
{
    int arg_count = 0;
    
    // Check required parameters (position, direction, diameter, height, angle, color)
    if (!args || !args[1] || !args[2] || !args[3] || !args[4] || !args[5] || !args[6])
        report_error("Cone parameters are invalid.");
    
    while (args[arg_count])
        arg_count++;
    
    // Valid cases:
    // 1. Basic cone: exactly 7 arguments (co x,y,z dx,dy,dz diameter height angle r,g,b)
    // 2. Cone with checker: exactly 10 arguments (adding: checker size r2,g2,b2)
    if (arg_count == 7)
        return;
    else if (arg_count == 10 && ft_strcmp(args[7], "checker") == 0)
        return;
    else
        report_error("Invalid number of arguments for cone. Use either:\n"
                    "co x,y,z dx,dy,dz diameter height angle r,g,b\n"
                    "or\n"
                    "co x,y,z dx,dy,dz diameter height angle r,g,b checker size r2,g2,b2");
}

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

void validate_sphere_input(char **args)
{
    int arg_count = 0;
    
    if (!args || !args[1] || !args[2] || !args[3])
        report_error("Sphere parameters are invalid.");
    
    while (args[arg_count])
        arg_count++;
    
    // Valid formats:
    // 1. Basic sphere: sp x,y,z diameter r,g,b
    // 2. Checker texture: sp x,y,z diameter r,g,b checker size r2,g2,b2
    // 3. Image texture: sp x,y,z diameter r,g,b texture path scale_u scale_v
    if (arg_count == 4)
        return; // Basic sphere
    else if (arg_count == 7 && ft_strcmp(args[4], "checker") == 0)
        return; // Checker pattern
    else if (arg_count == 8 && ft_strcmp(args[4], "texture") == 0)
        return; // Image texture
    else
        report_error("Invalid sphere format. Use one of:\n"
                    "sp x,y,z diameter r,g,b\n"
                    "sp x,y,z diameter r,g,b checker size r2,g2,b2\n"
                    "sp x,y,z diameter r,g,b texture path scale_u scale_v");
}

// Helper function to validate the sphere diameter
void validate_sphere_diameter(double diameter)
{
    if (diameter <= 0)
        report_error("Invalid sphere diameter: must be positive.");
}
//=========

void validate_cylinder_input(char **args)
{
    int arg_count = 0;
    
    if (!args || !args[1] || !args[2] || !args[3] || !args[4] || !args[5])
        report_error("Cylinder parameters are invalid.");
    
    while (args[arg_count])
        arg_count++;
    
    if (arg_count == 6)
        return;
    else if (arg_count == 9 && ft_strcmp(args[6], "checker") == 0)
        return;
    else
        report_error("Invalid number of arguments for cylinder.");
}

// Helper function to validate the cylinder orientation
void validate_cylinder_orientation(t_point3d dir)
{
    if (dir.x_coord > 1 || dir.y_coord > 1 || dir.z_coord > 1 || \
			dir.x_coord < -1 || dir.y_coord < -1 || dir.z_coord < -1)
        report_error("Cylinder direction components must be between -1 and 1.");
}