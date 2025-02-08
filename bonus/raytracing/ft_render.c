/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elel-bah <elel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 13:16:12 by elel-bah          #+#    #+#             */
/*   Updated: 2025/01/31 10:44:06 by elel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT_bonus.h"

void	ft_render(t_world *sc)
{
	t_tracer	info;

	info.camera = set_camera(sc);
	image_init(&info);
	ft_draw(&info, sc);
	mlx_put_image_to_window(info.data.mlx, info.data.win, info.frame.mlx_img, 0, 0);
	mlx_key_hook(info.data.win, esc_key, &info.data);
	mlx_hook(info.data.win, 17, 0, cross_button, &info.data);
	mlx_loop(info.data.mlx);
}