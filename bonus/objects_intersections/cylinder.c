/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elel-bah <elel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 15:20:33 by elel-bah          #+#    #+#             */
/*   Updated: 2025/01/31 11:06:52 by elel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT_bonus.h"


double calculate_cylinder_intersection(t_cyl_calc cylinder_calc, t_ray *ray, t_scene_element *cylinder)
{
    double t1 = (-cylinder_calc.quad_b + sqrt(cylinder_calc.delta)) / (2 * cylinder_calc.quad_a);
    double t2 = (-cylinder_calc.quad_b - sqrt(cylinder_calc.delta)) / (2 * cylinder_calc.quad_a);
    
    // Calculate intersection heights
    t_point3d axis = scale_to_one(cylinder->direction);
    double y1 = dot_product(ray->direction, axis) * t1 
                + dot_product(cylinder_calc.ray_to_center, axis);
    double y2 = dot_product(ray->direction, axis) * t2 
                + dot_product(cylinder_calc.ray_to_center, axis);

    // Check height bounds for closest intersection point
    if (t2 > EPSILON && y2 >= 0 && y2 <= cylinder->param.y_coord)
        return t2;
    if (t1 > EPSILON && y1 >= 0 && y1 <= cylinder->param.y_coord)
        return t1;

    return (-1.0);
}

double find_cylinder_intersection(t_ray *ray, t_scene_element *cylinder)
{
    t_cyl_calc calc;
    
    calc.norm_axis = scale_to_one(cylinder->direction);
    calc.ray_to_center = sub_vec(ray->origin, cylinder->center);

    double dot_dir_axis = dot_product(ray->direction, calc.norm_axis);
    double dot_oc_axis = dot_product(calc.ray_to_center, calc.norm_axis);
    
    calc.quad_a = dot_product(ray->direction, ray->direction) 
                  - (dot_dir_axis * dot_dir_axis);
    calc.quad_b = 2 * (dot_product(ray->direction, calc.ray_to_center) 
                  - (dot_dir_axis * dot_oc_axis));
    calc.quad_c = dot_product(calc.ray_to_center, calc.ray_to_center)
                  - (dot_oc_axis * dot_oc_axis) 
                  - pow(cylinder->param.x_coord / 2, 2);

    calc.delta = calc.quad_b * calc.quad_b - 4 * calc.quad_a * calc.quad_c;

    if (calc.delta < EPSILON || calc.quad_a == 0)
        return (-1.0);

    return calculate_cylinder_intersection(calc, ray, cylinder);
}

t_inter_data calc_cylinder_normal(t_inter_data closest_hit, t_scene_element *cylinder, t_ray *ray)
{
    t_inter_data current_hit;
    double hit_height;
    t_point3d cyl_axis;

    // Compute the intersection of the ray with the cylinder
    current_hit.t = find_cylinder_intersection(ray, cylinder);
    if ((closest_hit.t > current_hit.t || closest_hit.t == -1) && current_hit.t > EPSILON)
    {
        // Update the current intersection details
        current_hit.color = cylinder->color;
        current_hit.hit_point = vec_addition(ray->origin, mult_vec(ray->direction, current_hit.t));
        
        // Calculate the cylinder's normalized axis vector
        cyl_axis = scale_to_one(cylinder->direction);
        
        // Determine the intersection height along the cylinder axis
        hit_height = dot_product(ray->direction, mult_vec(cyl_axis, current_hit.t))
            + dot_product(sub_vec(ray->origin, cylinder->center), cyl_axis);
        
        // Compute the normal vector at the intersection point
        current_hit.normal = scale_to_one(sub_vec(sub_vec(current_hit.hit_point, cylinder->center),
                    mult_vec(cyl_axis, hit_height)));
        
        // Update the closest intersection
        closest_hit = current_hit;
    }
    return (closest_hit);
}
