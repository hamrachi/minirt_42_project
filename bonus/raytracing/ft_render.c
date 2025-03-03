/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamrachi <hamrachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 13:16:12 by elel-bah          #+#    #+#             */
/*   Updated: 2025/03/03 21:33:43 by hamrachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT_bonus.h"

void	ft_draw_b(t_tracer *info, t_world *sc)
{
	pthread_t		threads[NUM_THREADS];
	t_thread_data	thread_data[NUM_THREADS];
	int				rows_per_thread;

	rows_per_thread = (HEIGHT + NUM_THREADS - 1) / NUM_THREADS;
	init_thread_data_array_b(thread_data, sc, info, rows_per_thread);
	create_threads_b(threads, thread_data);
	join_threads_b(threads);
	pthread_mutex_destroy(&thread_data[0].render_mutex);
}

void	ft_render_b(t_world *sc)
{
	t_tracer	info;

	info.camera = set_camera_b(sc);
	image_init_b(&info);
	ft_draw_b(&info, sc);
	mlx_put_image_to_window(info.data.mlx, \
		info.data.win, info.frame.mlx_img, 0, 0);
	mlx_key_hook(info.data.win, esc_key_b, &info.data);
	mlx_hook(info.data.win, 17, 0, cross_button_b, &info.data);
	mlx_loop(info.data.mlx);
}
