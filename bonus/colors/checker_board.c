/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_board.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elel-bah <elel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 18:08:03 by elel-bah          #+#    #+#             */
/*   Updated: 2025/01/01 18:33:30 by elel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT_bonus.h"

// t_vec apply_checkerboard(t_inter *intersection, t_texture *texture)
// {
//     double uv_x, uv_y;
    
//     if (!texture->has_checkerboard)
//         return (intersection->color);
    
//     // Calculate UV coordinates using the normal vector
//     // This will help wrap the pattern around curved surfaces
//     uv_x = 0.5 + atan2(intersection->normal.z, intersection->normal.x) / (2 * M_PI);
//     uv_y = 0.5 - asin(intersection->normal.y) / M_PI;
    
//     // Scale the UV coordinates based on checker size
//     int x = floor(uv_x / texture->checker_size);
//     int y = floor(uv_y / texture->checker_size);
    
//     // Determine the color based on alternating pattern
//     if ((x + y) % 2 == 0)
//         return (intersection->color);
//     return (texture->color2);
// }

// Function to calculate the checkerboard color
t_vec apply_checkerboard(t_inter *intersection, t_texture *texture)
{
    int x, y, z;

    if (!texture->has_checkerboard)
        return (intersection->color); // No checkerboard, return the object's base color

    // Scale the hit point to the checker size
    x = floor(intersection->hit_point.x / texture->checker_size);
    y = floor(intersection->hit_point.y / texture->checker_size);
    z = floor(intersection->hit_point.z / texture->checker_size);

    // Determine the color based on alternating pattern
    if ((x + y + z) % 2 == 0)
        return (intersection->color); // Base color
    return (texture->color2); // Checkerboard color
}

