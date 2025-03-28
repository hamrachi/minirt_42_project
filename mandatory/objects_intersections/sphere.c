/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamrachi <hamrachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 15:00:02 by elel-bah          #+#    #+#             */
/*   Updated: 2025/03/01 16:42:41 by hamrachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT.h"

t_inter_data	calc_sphere_normal(t_inter_data current_hit, \
	t_scene_element *sphere, t_ray *ray)
{
	t_inter_data	new_hit;

	new_hit.t = calc_sp_ray_inter(ray, sphere);
	if ((current_hit.t > new_hit.t || current_hit.t == -1) \
		&& new_hit.t > EPSILON)
	{
		new_hit.color = sphere->color;
		new_hit.hit_point = vec_addition(ray->origin, \
			mult_vec(ray->direction, new_hit.t));
		new_hit.normal = scale_to_one(\
			sub_vec(new_hit.hit_point, sphere->center));
		current_hit = new_hit;
	}
	return (current_hit);
}

double	calc_sp_ray_inter(t_ray *ray, t_scene_element *sphere)
{
	t_sph_calc		calc;
	t_point3d		ray_to_center;
	double			radius;

	ray_to_center = sub_vec(ray->origin, sphere->center);
	radius = sphere->param.x_coord / 2.0;
	calc.quad_a = dot_product(ray->direction, ray->direction);
	calc.quad_b = 2.0 * dot_product(ray_to_center, ray->direction);
	calc.quad_c = dot_product(ray_to_center, ray_to_center) - (radius * radius);
	calc.delta = calc.quad_b * calc.quad_b - (4 * calc.quad_a * calc.quad_c);
	if (calc.delta < EPSILON)
		return (-1);
	calc.hit1 = (-calc.quad_b - sqrt(calc.delta)) / (2.0 * calc.quad_a);
	calc.hit2 = (-calc.quad_b + sqrt(calc.delta)) / (2.0 * calc.quad_a);
	if (calc.hit1 * calc.hit2 > EPSILON)
	{
		if (calc.hit1 > EPSILON)
			return (find_min(calc.hit1, calc.hit2));
		return (-1);
	}
	if (calc.hit1 > EPSILON)
		return (calc.hit1);
	return (calc.hit2);
}
