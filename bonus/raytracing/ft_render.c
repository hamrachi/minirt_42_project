/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elel-bah <elel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 13:16:12 by elel-bah          #+#    #+#             */
/*   Updated: 2025/01/09 13:21:54 by elel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT_bonus.h"

void	ft_render(t_scene *sc)
{
	t_render	info;

	info.cam = set_camera(sc);
	image_init(&info);
	ft_draw(&info, sc);
	mlx_put_image_to_window(info.vars.mlx, info.vars.win, info.img.img, 0, 0);
	mlx_key_hook(info.vars.win, esc_key, &info.vars);
	mlx_hook(info.vars.win, 17, 0, cross_button, &info.vars);
	mlx_loop(info.vars.mlx);
}