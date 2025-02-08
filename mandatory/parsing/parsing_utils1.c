/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elel-bah <elel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:36:29 by elel-bah          #+#    #+#             */
/*   Updated: 2024/12/17 19:45:17 by elel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT.h"

// Helper function to validate plane input (args and count)
void validate_plane_input(char **args)
{
    if (!args || !args[1] || !args[2] || !args[3] || args[4])
        report_error("Invalid plane arguments.");
}

// Helper function to validate the plane orientation
void validate_plane_orientation(t_vec dir)
{
    if (dir.x > 1 || dir.y > 1 || dir.z > 1 || \
			dir.x < -1 || dir.y < -1 || dir.z < -1)
        report_error("Plane direction components must be between -1 and 1.");
}