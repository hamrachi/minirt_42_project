/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elel-bah <elel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 13:16:12 by elel-bah          #+#    #+#             */
/*   Updated: 2025/02/23 18:23:47 by elel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT.h"

t_ndc	calculate_ndc(int x, int y)
{
	t_ndc	coords;

	coords.v = (double)x * 2 / WIDTH - 1;
	coords.u = (double)y * 2 / HEIGHT - 1;
	return (coords);
}

t_point3d	process_pixel(t_tracer *info, t_world *sc, int x, int y)
{
	t_ndc		coords;
	t_ray		primary_ray;
	t_point3d	pixel_color;

	coords = calculate_ndc(x, y);
	primary_ray = ray_primary(&info->camera, coords.v, coords.u);
	pixel_color = ray_color(&primary_ray, sc);
	return (pixel_color);
}

void	draw_row(t_tracer *info, t_world *sc, int y)
{
	int			x;
	t_point3d	pixel_color;

	x = 0;
	while (x < WIDTH)
	{
		pixel_color = process_pixel(info, sc, x, y);
		my_mlx_pixel_put(&info->frame, x, HEIGHT - 1 - y,
			create_rgb(pixel_color.x_coord, \
				pixel_color.y_coord, pixel_color.z_coord));
		x++;
	}
}

void	ft_draw(t_tracer info, t_world *sc)
{
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		draw_row(&info, sc, y);
		y++;
	}
}

void	ft_render(t_world *sc)
{
	t_tracer	info;

	info.camera = set_camera(sc);
	image_init(&info);
	ft_draw(info, sc);
	mlx_put_image_to_window(info.data.mlx, \
		info.data.win, info.frame.mlx_img, 0, 0);
	mlx_key_hook(info.data.win, esc_key, &info.data);
	mlx_hook(info.data.win, 17, 0, cross_button, &info.data);
	mlx_loop(info.data.mlx);
}
