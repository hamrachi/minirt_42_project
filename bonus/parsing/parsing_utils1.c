/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamrachi <hamrachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:36:29 by elel-bah          #+#    #+#             */
/*   Updated: 2025/03/01 16:45:29 by hamrachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT_bonus.h"

void	validate_plane_input_b(char **args)
{
	int	arg_count;

	arg_count = 0;
	if (!args || !args[1] || !args[2] || !args[3])
		report_error_b("Plane parameters are invalid.");
	while (args[arg_count])
		arg_count++;
	if (arg_count == 4)
		return ;
	else if (arg_count == 7 && ft_strcmp_b(args[4], "checker") == 0)
		return ;
	else
		report_error_b("Invalid number of arguments for plane.");
}

void	validate_plane_orientation_b(t_point3d dir)
{
	if (dir.x_coord > 1 || dir.y_coord > 1 || dir.z_coord > 1 || \
		dir.x_coord < -1 || dir.y_coord < -1 || dir.z_coord < -1)
		report_error_b("Plane direction components must be between -1 and 1.");
}
