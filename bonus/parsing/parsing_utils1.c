/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elel-bah <elel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:36:29 by elel-bah          #+#    #+#             */
/*   Updated: 2025/01/03 18:38:23 by elel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT_bonus.h"

// // Modified validation functions
// void validate_plane_input(char **args)
// {
//     if ((!args || !args[1] || !args[2] || !args[3]) && (!args[4] || !args[5] || !args[6]))
//         report_error("Invalid plane arguments.");
//     // Allow optional checker parameters
//     if (args[4] && ft_strcmp(args[4], "checker") == 0 && (!args[5] || !args[6] || args[7]))
//         report_error("Invalid checkerboard parameters for plane.");
// }

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

// void validate_plane_input(char **args)
// {
//     int arg_count = 0;

//     // Count the number of arguments
//     while (args[arg_count])
//         arg_count++;

//     // Validate required arguments (minimum 4)
//     if (arg_count < 4 || arg_count > 5) // Allow 4 or 5 arguments
//         report_error("Invalid plane parameters. Expected 4 or 5 arguments.");
// }


// // Helper function to validate plane input (args and count)
// void validate_plane_input(char **args)
// {
//     if (!args || !args[1] || !args[2] || !args[3] || args[4])
//         report_error("Invalid plane arguments.");
// }

// Helper function to validate the plane orientation
void validate_plane_orientation(t_vec dir)
{
    if (dir.x > 1 || dir.y > 1 || dir.z > 1 || \
			dir.x < -1 || dir.y < -1 || dir.z < -1)
        report_error("Plane direction components must be between -1 and 1.");
}