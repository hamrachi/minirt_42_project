/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elel-bah <elel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 13:54:58 by elel-bah          #+#    #+#             */
/*   Updated: 2025/01/04 18:30:01 by elel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT_bonus.h"

// t_vec compute_lighting(t_scene *scene, t_inter intersection, t_vec ambient_color)
// {
//     t_light *current_light;
//     t_vec final_color;
//     t_vec light_direction;
//     double diffuse_factor;
//     t_vec base_color;

//     final_color = create_vector(0, 0, 0);
//     current_light = scene->light;

//     // Apply checkerboard pattern to base color first
//     if (intersection.has_checkerboard)
//         base_color = apply_checkerboard(&intersection, &intersection.texture);
//     else
//         base_color = intersection.color;

//     while (current_light)
//     {
//         if (!is_point_in_shadow(scene, intersection, current_light))
//         {
//             // Diffuse Lighting using the checkerboard color
//             light_direction = sub_vec(current_light->src, intersection.hit_point);
//             diffuse_factor = dot_product(scale_to_one(light_direction), intersection.normal);
//             if (diffuse_factor > 0)
//             {
//                 // Use base_color instead of intersection.color for diffuse calculation
//                 t_inter temp_inter = intersection;
//                 temp_inter.color = base_color;
//                 final_color = blend_colors(final_color, diffuse(temp_inter, current_light, diffuse_factor));
//             }

//             // Specular Lighting
//             final_color = blend_colors(final_color, specular(scene, intersection, current_light));
//         }
//         current_light = current_light->next;
//     }

//     // Apply ambient light to the checkerboard color
//     ambient_color = scale_and_combine_colors(base_color, scene->amb.col, scene->amb.ratio);
//     final_color = blend_colors(final_color, ambient_color);

//     // Clamp Final Color
//     final_color.x = fmin(final_color.x, 255);
//     final_color.y = fmin(final_color.y, 255);
//     final_color.z = fmin(final_color.z, 255);    
//     return final_color;
// }


t_vec compute_lighting(t_scene *scene, t_inter intersection, t_vec ambient_color)//origine
{
    t_light *current_light;
    t_vec final_color;
    t_vec light_direction;
    double diffuse_factor;

    final_color = create_vector(0, 0, 0);
    current_light = scene->light;

    while (current_light)
    {
        if (!is_point_in_shadow(scene, intersection, current_light))
        {
            // Diffuse Lighting
            light_direction = sub_vec(current_light->src, intersection.hit_point);
            diffuse_factor = dot_product(scale_to_one(light_direction), intersection.normal);
            if (diffuse_factor > 0)
                final_color = blend_colors(final_color, diffuse(intersection, current_light, diffuse_factor));

            // Specular Lighting
            final_color = blend_colors(final_color, specular(scene, intersection, current_light));
        }
        current_light = current_light->next;
    }

    // Add Ambient Light
    final_color = blend_colors(final_color, ambient_color);

    // Clamp Final Color
    final_color.x = fmin(final_color.x, 255);
    final_color.y = fmin(final_color.y, 255);
    final_color.z = fmin(final_color.z, 255);    
    return final_color;
}


t_vec scale_and_combine_colors(t_vec base_color, t_vec light_color, double intensity_ratio)
{
    t_vec result_color;

    result_color.x = base_color.x * (light_color.x / 255) * intensity_ratio;
    result_color.y = base_color.y * (light_color.y / 255) * intensity_ratio;
    result_color.z = base_color.z * (light_color.z / 255) * intensity_ratio;

    return (result_color);
}



t_vec blend_colors(t_vec color_a, t_vec color_b)
{
    t_vec blended_color;

    blended_color = vec_addition(color_a, color_b);
    if (blended_color.x > 255)
        blended_color.x = 255;
    if (blended_color.y > 255)
        blended_color.y = 255;
    if (blended_color.z > 255)
        blended_color.z = 255;

    return (blended_color);
}


t_vec	ray_color(t_ray *ray, t_scene *sc)
{
	t_inter	inter;
	t_vec	px_col;
	t_vec	amb;

	inter = find_closest_intersection(ray, sc);
	if (inter.t > EPSILON)
	{
		amb = scale_and_combine_colors(inter.color, sc->amb.col, sc->amb.ratio);
		if (ray_is_inside(ray->direction, inter.normal))
			inter.normal = mult_vec(inter.normal, -1);
		px_col = compute_lighting(sc, inter, amb);
		return (px_col);
	}
	return (mult_vec(sc->amb.col, sc->amb.ratio));
}

int	create_rgb(int r, int g, int b)
{
	return (((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff));
}

