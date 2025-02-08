/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supersimpler1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elel-bah <elel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 16:58:16 by elel-bah          #+#    #+#             */
/*   Updated: 2024/12/23 16:52:08 by elel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT_bonus.h"

// Calculate ray parameters
t_ray_params	calculate_ray_params(t_ray_trace_context *ctx)
{
	t_ray_params	params;

	params.offset_u = (ctx->sx + 0.5) * ctx->config->subpixel_step;
	params.offset_v = (ctx->sy + 0.5) * ctx->config->subpixel_step;

	params.u = ((double)ctx->x + params.offset_u) * 2 / WIDTH - 1;
	params.v = ((double)ctx->y + params.offset_v) * 2 / HEIGHT - 1;

	return (params);
}

// Trace a single sample ray
t_vec	trace_sample_ray(t_ray_trace_context *ctx)
{
	t_ray_params	params;
	t_ray		ray;

	// Calculate ray parameters
	params = calculate_ray_params(ctx);

	// Generate and trace the ray
	ray = ray_primary(ctx->cam, params.u, params.v);
	return (ray_color(&ray, ctx->scene));
}

//=-=-=-=-

// Initialize and prepare context for SSAA

// Initialize the context structure (4 parameters)
void init_pixel_context(t_ray_trace_context *ctx, t_ssaa_config *config, t_camera *cam, t_scene *scene)
{
    ctx->config = config;
    ctx->cam = cam;
    ctx->scene = scene;
}

// Set pixel coordinates in context (3 parameters)
void set_pixel_coords(t_ray_trace_context *ctx, int x, int y)
{
    ctx->x = x;
    ctx->y = y;
}

// Process a single sample of the pixel
t_vec process_single_sample(t_ray_trace_context *ctx, int sx, int sy)
{
    ctx->sx = sx;
    ctx->sy = sy;
    return (trace_sample_ray(ctx));
}