/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supersimpler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamrachi <hamrachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 15:15:31 by elel-bah          #+#    #+#             */
/*   Updated: 2025/03/03 21:33:48 by hamrachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT_bonus.h"

t_ssaa_config	init_ssaa_config_b(void)
{
	t_ssaa_config	config;

	config.samples_per_side = 4;
	config.total_samples = config.samples_per_side * config.samples_per_side;
	config.subpixel_step = 1.0 / config.samples_per_side;
	config.inv_total_samples = 1.0 / config.total_samples;
	return (config);
}

t_point3d	process_sample_row_b(t_ray_trace_context *ctx, int sy)
{
	t_point3d	color;
	t_point3d	sample_color;
	int			sx;

	color = (t_point3d){0, 0, 0};
	sx = 0;
	while (sx < ctx->config->samples_per_side)
	{
		sample_color = process_single_sample_b(ctx, sx, sy);
		color = vec_addition_b(color, sample_color);
		sx++;
	}
	return (color);
}

t_point3d	process_pixel_with_ssaa_b(int x, int y, \
	t_cam_matrix *cam, t_world *scene)
{
	t_ray_trace_context		ctx;
	t_point3d				color;
	t_point3d				row_color;
	t_ssaa_config			config;
	int						sy;

	config = init_ssaa_config_b();
	init_pixel_context_b(&ctx, &config, cam, scene);
	set_pixel_coords_b(&ctx, x, y);
	color = (t_point3d){0, 0, 0};
	sy = 0;
	while (sy < config.samples_per_side)
	{
		row_color = process_sample_row_b(&ctx, sy);
		color = vec_addition_b(color, row_color);
		sy++;
	}
	return (mult_vec_b(color, config.inv_total_samples));
}

void	*render_section_b(void *arg)
{
	t_thread_data	*data;
	int				x;
	int				y;
	t_point3d		color;

	data = (t_thread_data *)arg;
	y = data->start_row;
	while (y < data->end_row)
	{
		x = 0;
		while (x < WIDTH)
		{
			color = process_pixel_with_ssaa_b(x, y, \
				&data->info->camera, data->scene);
			my_mlx_pixel_put(&data->info->frame, x, HEIGHT - 1 - y,
				create_rgb_b(color.x_coord, color.y_coord, color.z_coord));
			x++;
		}
		y++;
	}
	return (NULL);
}
