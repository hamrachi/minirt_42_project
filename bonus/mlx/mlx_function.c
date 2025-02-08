/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_function.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elel-bah <elel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 15:55:58 by elel-bah          #+#    #+#             */
/*   Updated: 2025/01/31 10:42:27 by elel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT_bonus.h"


void	image_init(t_tracer	*info)
{
	info->data.mlx = mlx_init();
	info->data.win = mlx_new_window(info->data.mlx, WIDTH, HEIGHT, "MiniRT");
	info->frame.mlx_img = mlx_new_image(info->data.mlx, WIDTH, HEIGHT);
	info->frame.pixel_buffer = mlx_get_data_addr(info->frame.mlx_img, &info->frame.color_depth,
			&info->frame.stride, &info->frame.byte_order);
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