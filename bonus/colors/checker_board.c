/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_board.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elel-bah <elel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 18:08:03 by elel-bah          #+#    #+#             */
/*   Updated: 2025/01/30 18:42:41 by elel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT_bonus.h"

// Function to calculate the checkerboard color
t_point3d apply_checkerboard(t_inter_data *intersection, t_texture *texture)
{
    int x;
    int y;
    int z;

    if (!texture->has_checkerboard)
        return (intersection->color); // No checkerboard, return the object's base color

    // Scale the hit point to the checker size
    x = floor(intersection->hit_point . x_coord / texture->checker_size);
    y = floor(intersection->hit_point . y_coord / texture->checker_size);
    z = floor(intersection->hit_point . z_coord / texture->checker_size);

    // Determine the color based on alternating pattern
    if ((x + y + z) % 2 == 0)
        return (intersection->color); // Base color
    return (texture->color2); // Checkerboard color
}

