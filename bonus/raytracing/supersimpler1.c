/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supersimpler1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elel-bah <elel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 16:58:16 by elel-bah          #+#    #+#             */
/*   Updated: 2025/02/23 22:02:13 by elel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT_bonus.h"

t_ray_params	calculate_ray_params(t_ray_trace_context *ctx)
{
	t_ray_params	params;

	params.offset_u = (ctx->sx + 0.5) * ctx->config->subpixel_step;
	params.offset_v = (ctx->sy + 0.5) * ctx->config->subpixel_step;
	params.u = ((double)ctx->x + params.offset_u) * 2 / WIDTH - 1;
	params.v = ((double)ctx->y + params.offset_v) * 2 / HEIGHT - 1;
	return (params);
}

t_point3d	trace_sample_ray(t_ray_trace_context *ctx)
{
	t_ray_params	params;
	t_ray			ray;

	params = calculate_ray_params(ctx);
	ray = ray_primary(ctx->cam, params.u, params.v);
	return (ray_color(&ray, ctx->scene));
}

void	init_pixel_context(t_ray_trace_context *ctx, \
	t_ssaa_config *config, t_cam_matrix *cam, t_world *scene)
{
	ctx->config = config;
	ctx->cam = cam;
	ctx->scene = scene;
}

void	set_pixel_coords(t_ray_trace_context *ctx, int x, int y)
{
	ctx->x = x;
	ctx->y = y;
}

t_point3d	process_single_sample(t_ray_trace_context *ctx, int sx, int sy)
{
	ctx->sx = sx;
	ctx->sy = sy;
	return (trace_sample_ray(ctx));
}
