/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_function.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamrachi <hamrachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 15:55:58 by elel-bah          #+#    #+#             */
/*   Updated: 2025/02/08 21:56:17 by hamrachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT.h"


void	image_init(t_tracer	*info)
{
	info->data.mlx = mlx_init();
	if(!info->data.mlx)
		report_error("failed mlx");
	info->data.win = mlx_new_window(info->data.mlx, WIDTH, HEIGHT, "MiniRT");
	if(!info->data.win)
		free(info->data.mlx),report_error("error to get the windows");
	info->frame.mlx_img = mlx_new_image(info->data.mlx, WIDTH, HEIGHT);
	if(!info->frame.mlx_img)
	{
		mlx_destroy_window(info->data.mlx, info->data.win);
		report_error("error to get image");
	}
	info->frame.pixel_buffer = mlx_get_data_addr(info->frame.mlx_img, &info->frame.color_depth,
			&info->frame.stride, &info->frame.byte_order);
	if(!info->frame.pixel_buffer)
	{
		mlx_destroy_window(info->data.mlx, info->data.win);
		mlx_destroy_window(info->data.mlx, info->data.win);
		report_error("error to get adress");
	}
}

void	my_mlx_pixel_put(t_canvas *data, int x, int y, int color)
{
	char	*dst;

	dst = data->pixel_buffer + (y * data->stride + x * (data->color_depth / 8));
	*(unsigned int *)dst = color;
}

int	esc_key(int key, t_vars *vars)
{
	if (key == 53)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
	}
	return (0);
}

int	cross_button(t_vars *vars)
{
	mlx_destroy_window(vars->mlx, vars->win);
	exit(0);
	return (0);
}