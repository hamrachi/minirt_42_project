/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elel-bah <elel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 13:16:07 by elel-bah          #+#    #+#             */
/*   Updated: 2025/02/23 22:05:22 by elel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT_bonus.h"

int	get_thread_end_row(int thread_id, int rows_per_thread)
{
	int	end_row;

	if (thread_id == NUM_THREADS - 1)
		end_row = HEIGHT;
	else
		end_row = (thread_id + 1) * rows_per_thread;
	return (end_row);
}

void	init_thread_data(t_thread_data *data, t_thread_info *info)
{
	data->thread_id = info->thread_id;
	data->start_row = info->thread_id * info->rows_per_thread;
	data->end_row = get_thread_end_row(info->thread_id, info->rows_per_thread);
	data->scene = info->scene;
	data->info = info->render_info;
}

void	join_threads(pthread_t *threads)
{
	int	i;

	i = 0;
	while (i < NUM_THREADS)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
}

void	create_threads(pthread_t *threads, t_thread_data *thread_data)
{
	int	i;

	i = 0;
	while (i < NUM_THREADS)
	{
		if (pthread_create(&threads[i], NULL, \
			render_section, &thread_data[i]) != 0)
		{
			perror("Error creating thread");
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

void	init_thread_data_array(t_thread_data *thread_data, \
	t_world *sc, t_tracer *info, int rows_per_thread)
{
	t_thread_info	thread_info;
	pthread_mutex_t	render_mutex;
	int				i;

	pthread_mutex_init(&render_mutex, NULL);
	i = 0;
	while (i < NUM_THREADS)
	{
		thread_info.thread_id = i;
		thread_info.rows_per_thread = rows_per_thread;
		thread_info.scene = sc;
		thread_info.render_info = info;
		init_thread_data(&thread_data[i], &thread_info);
		thread_data[i].render_mutex = render_mutex;
		i++;
	}
}
