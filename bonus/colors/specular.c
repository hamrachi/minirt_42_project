/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specular.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elel-bah <elel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 18:05:18 by elel-bah          #+#    #+#             */
/*   Updated: 2024/12/30 18:07:34 by elel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT_bonus.h"

t_vec specular(t_scene *scene, t_inter intersection, t_light *light)
{
    t_vec light_to_hit;         // Vector from light to intersection point
    t_vec normalized_light_dir; // Normalized direction of light
    t_vec view_vector;          // Direction from intersection point to camera
    t_vec reflection_vector;    // Reflected light direction
    double specular_intensity;  // Calculated specular intensity
    t_vec specular_color;       // Resultant specular color

    // Calculate the vector from light source to the intersection point
    light_to_hit = sub_vec(light->src, intersection.hit_point);

    // Normalize the light direction
    normalized_light_dir = scale_to_one(light_to_hit);

    // Calculate the view vector (from hit point to camera)
    t_vec hit_to_camera = sub_vec(intersection.hit_point, scene->cam.cen);
    view_vector = scale_to_one(hit_to_camera);
    // Calculate the reflection vector
    t_vec scaled_normal = mult_vec(intersection.normal, 2 * dot_product(intersection.normal, normalized_light_dir));
    reflection_vector = sub_vec(scaled_normal, normalized_light_dir);
    // Calculate the specular intensity using the reflection and view vectors
    specular_intensity = pow(dot_product(reflection_vector, view_vector), 50) * light->ratio * 0.5;
    // Calculate the specular color by scaling the light color
    specular_color = mult_vec(light->col, specular_intensity);
    return specular_color;
}