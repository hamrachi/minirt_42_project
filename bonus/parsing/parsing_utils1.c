/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elel-bah <elel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:36:29 by elel-bah          #+#    #+#             */
/*   Updated: 2025/01/30 17:48:53 by elel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT_bonus.h"

void validate_plane_input(char **args)
{
    int arg_count = 0;
    
    if (!args || !args[1] || !args[2] || !args[3])
        report_error("Plane parameters are invalid.");
    
    while (args[arg_count])
        arg_count++;
    
    if (arg_count == 4)
        return;
    else if (arg_count == 7 && ft_strcmp(args[4], "checker") == 0)
        return;
    else
        report_error("Invalid number of arguments for plane.");
}

// Helper function to validate the plane orientation
void validate_plane_orientation(t_point3d dir)
{
    if (dir.x_coord > 1 || dir.y_coord > 1 || dir.z_coord > 1 || \
			dir.x_coord < -1 || dir.y_coord < -1 || dir.z_coord < -1)
        report_error("Plane direction components must be between -1 and 1.");
}