/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elel-bah <elel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 21:48:03 by elel-bah          #+#    #+#             */
/*   Updated: 2024/12/23 16:51:42 by elel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT_bonus.h"


//=-=-=-==-=-Ambients-light

// Helper function to validate the ambient lighting ratio
void validate_ambient_ratio_range(double ratio)
{
    if (ratio < 0 || ratio > 1)
        report_error("Ambient lighting ratio should be between 0.0 and 1.0.");
}

// Helper function to validate ambient parameters (tokens and count)
void validate_ambient_input(char **args, t_scene *scene)
{
    // Check if tokens are valid (must have at least 3 elements, no more than 3)
    if (!args || !args[1] || !args[2] || args[3])
        report_error("Ambient lighting parameters are invalid!");
    // Check if ambient count is already set
    if (scene->amb.count != 0)
        report_error("There can be only one ambient light source.");
}
// Helper function to validate the cylinder diameter
void validate_cylinder_diameter(double diameter, double height)
{
    if (diameter <= 0 || height <= 0)
        report_error("Cylinder diameter and height must both be positive.");
}