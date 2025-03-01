/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_board.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamrachi <hamrachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 18:08:03 by elel-bah          #+#    #+#             */
/*   Updated: 2025/03/01 16:44:12 by hamrachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT_bonus.h"

t_point3d	apply_checkerboard_b(t_inter_data *intersection, t_texture *texture)
{
	int	x;
	int	y;
	int	z;

	if (!texture->has_checkerboard)
		return (intersection->color);
	x = floor(intersection->hit_point . x_coord / texture->checker_size);
	y = floor(intersection->hit_point . y_coord / texture->checker_size);
	z = floor(intersection->hit_point . z_coord / texture->checker_size);
	if ((x + y + z) % 2 == 0)
		return (intersection->color);
	return (texture->color2);
}
