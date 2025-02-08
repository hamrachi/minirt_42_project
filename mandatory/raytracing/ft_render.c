/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elel-bah <elel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 13:16:12 by elel-bah          #+#    #+#             */
/*   Updated: 2025/01/09 14:52:50 by elel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT.h"

// Calculate normalized device coordinates (NDC) for a pixel
t_ndc calculate_ndc(int x, int y)
{
    t_ndc coords;
    
    coords.v = (double)x * 2 / WIDTH - 1;
    coords.u = (double)y * 2 / HEIGHT - 1;
    return (coords);
}

// Process a single pixel and return its color
t_vec process_pixel(t_render *info, t_scene *sc, int x, int y)
{
    t_ndc   coords;
    t_ray   primary_ray;
    t_vec   pixel_color;
    
    coords = calculate_ndc(x, y);
    primary_ray = ray_primary(&info->cam, coords.v, coords.u);
    pixel_color = ray_color(&primary_ray, sc);
    return (pixel_color);
}

// Draw a single row of pixels
void draw_row(t_render *info, t_scene *sc, int y)
{
    int     x;
    t_vec   pixel_color;
    
    x = 0;
    while (x < WIDTH)
    {
        pixel_color = process_pixel(info, sc, x, y);
        my_mlx_pixel_put(&info->img, x, HEIGHT - 1 - y,
            create_rgb(pixel_color.x, pixel_color.y, pixel_color.z));
        x++;
    }
}

// Main drawing function
void ft_draw(t_render info, t_scene *sc)
{
    int y;
    
    y = HEIGHT - 1;
    while (y >= 0)
    {
        draw_row(&info, sc, y);
        y--;
    }
}

void	ft_render(t_scene *sc)
{
	t_render	info;

	info.cam = set_camera(sc);
	image_init(&info);
	ft_draw(info, sc);
	mlx_put_image_to_window(info.vars.mlx, info.vars.win, info.img.img, 0, 0);
	mlx_key_hook(info.vars.win, esc_key, &info.vars);
	mlx_hook(info.vars.win, 17, 0, cross_button, &info.vars);
	mlx_loop(info.vars.mlx);
}