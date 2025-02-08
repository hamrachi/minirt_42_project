/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specular.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elel-bah <elel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 18:05:18 by elel-bah          #+#    #+#             */
/*   Updated: 2025/02/03 13:47:28 by elel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT_bonus.h"

t_point3d calculate_light_reflection_vector(t_point3d hit, t_point3d normal, 
                                             t_point3d light_pos, t_point3d cam_pos)
{
    t_point3d light_dir;
    t_point3d view_dir;
    double dot_prod;

    // Calculate and normalize light direction
    light_dir = scale_to_one(sub_vec(light_pos, hit));
    
    // Calculate and normalize view direction
    view_dir = scale_to_one(sub_vec(hit, cam_pos));
    
    // Calculate dot product of normal and light direction
    dot_prod = dot_product(normal, light_dir);
    
    // Calculate reflection vector
    return sub_vec(mult_vec(normal, 2 * dot_prod), light_dir);
}

t_point3d specular(t_world *scene, t_inter_data inter, 
                                     t_light_source *light)
{
    t_point3d reflection;
    t_point3d view_dir;
    double intensity;

    // Calculate reflection vector
    reflection = calculate_light_reflection_vector(
        inter.hit_point, 
        inter.normal,
        light->position, 
        scene->camera.origin
    );
    
    // Calculate normalized view direction
    view_dir = scale_to_one(sub_vec(inter.hit_point, scene->camera.origin));
    
    // Calculate specular intensity
    intensity = pow(
        dot_product(reflection, view_dir), 
        50.0
    ) * light->brightness * 0.5;
    
    // Return specular color
    return mult_vec(light->light_color, intensity);
}
