/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamrachi <hamrachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 15:20:33 by elel-bah          #+#    #+#             */
/*   Updated: 2025/03/01 16:45:01 by hamrachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT_bonus.h"

double	calculate_cylinder_intersection_b(t_cyl_calc cylinder_calc, \
		t_ray *ray, t_scene_element *cylinder)
{
	double		t1;
	double		t2;
	double		y1;
	double		y2;
	t_point3d	axis;

	t1 = (-cylinder_calc.quad_b + sqrt(cylinder_calc.delta)) / \
		(2 * cylinder_calc.quad_a);
	t2 = (-cylinder_calc.quad_b - sqrt(cylinder_calc.delta)) / \
		(2 * cylinder_calc.quad_a);
	axis = scale_to_one_b(cylinder->direction);
	y1 = dot_product_b(ray->direction, axis) * t1
		+ dot_product_b(cylinder_calc.ray_to_center, axis);
	y2 = dot_product_b(ray->direction, axis) * t2
		+ dot_product_b(cylinder_calc.ray_to_center, axis);
	if (t2 > EPSILON && y2 >= 0 && y2 <= cylinder->param.y_coord)
		return (t2);
	if (t1 > EPSILON && y1 >= 0 && y1 <= cylinder->param.y_coord)
		return (t1);
	return (-1.0);
}

double	find_cylinder_intersection_b(t_ray *ray, t_scene_element *cylinder)
{
	t_cyl_calc	calc;
	double		dot_dir_axis;
	double		dot_oc_axis;

	calc.norm_axis = scale_to_one_b(cylinder->direction);
	calc.ray_to_center = sub_vec_b(ray->origin, cylinder->center);
	dot_dir_axis = dot_product_b(ray->direction, calc.norm_axis);
	dot_oc_axis = dot_product_b(calc.ray_to_center, calc.norm_axis);
	calc.quad_a = dot_product_b(ray->direction, ray->direction)
		- (dot_dir_axis * dot_dir_axis);
	calc.quad_b = 2 * (dot_product_b(ray->direction, calc.ray_to_center)
			- (dot_dir_axis * dot_oc_axis));
	calc.quad_c = dot_product_b(calc.ray_to_center, calc.ray_to_center)
		- (dot_oc_axis * dot_oc_axis)
		- pow(cylinder->param.x_coord / 2, 2);
	calc.delta = calc.quad_b * calc.quad_b - 4 * calc.quad_a * calc.quad_c;
	if (calc.delta < EPSILON || calc.quad_a == 0)
		return (-1.0);
	return (calculate_cylinder_intersection_b(calc, ray, cylinder));
}

t_inter_data	calc_cylinder_normal_b(t_inter_data closest_hit, \
		t_scene_element *cylinder, t_ray *ray)
{
	t_inter_data	current_hit;
	double			hit_height;
	t_point3d		cyl_axis;

	current_hit.t = find_cylinder_intersection_b(ray, cylinder);
	if ((closest_hit.t > current_hit.t || closest_hit.t == -1) \
			&& current_hit.t > EPSILON)
	{
		current_hit.color = cylinder->color;
		current_hit.hit_point = vec_addition_b(ray->origin, \
				mult_vec_b(ray->direction, current_hit.t));
		cyl_axis = scale_to_one_b(cylinder->direction);
		hit_height = dot_product_b(ray->direction, \
				mult_vec_b(cyl_axis, current_hit.t))
			+ dot_product_b(sub_vec_b(ray->origin, cylinder->center), \
				cyl_axis);
		current_hit.normal = scale_to_one_b(sub_vec_b \
			(sub_vec_b(current_hit.hit_point, cylinder->center),
					mult_vec_b(cyl_axis, hit_height)));
		closest_hit = current_hit;
	}
	return (closest_hit);
}
