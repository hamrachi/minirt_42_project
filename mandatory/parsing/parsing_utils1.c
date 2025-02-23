/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elel-bah <elel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:36:29 by elel-bah          #+#    #+#             */
/*   Updated: 2025/02/23 18:18:03 by elel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT.h"

void	validate_plane_input(char **args)
{
	if (!args || !args[1] || !args[2] || !args[3] || args[4])
		report_error("Invalid plane arguments.");
}

void	validate_plane_orientation(t_point3d dir)
{
	if (dir.x_coord > 1 || dir.y_coord > 1 || dir.z_coord > 1 || \
		dir.x_coord < -1 || dir.y_coord < -1 || dir.z_coord < -1)
		report_error("Plane direction components must be between -1 and 1.");
}
