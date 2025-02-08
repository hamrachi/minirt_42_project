/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elel-bah <elel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 13:16:07 by elel-bah          #+#    #+#             */
/*   Updated: 2025/01/31 10:42:53 by elel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT_bonus.h"

// Calculate end row for a thread
int get_thread_end_row(int thread_id, int rows_per_thread)
{
    int end_row;

    if (thread_id == NUM_THREADS - 1)
        end_row = HEIGHT;
    else
        end_row = (thread_id + 1) * rows_per_thread;
    return (end_row);
}


void init_thread_data(t_thread_data *data, t_thread_info *info)
{
    data->thread_id = info->thread_id;
    data->start_row = info->thread_id * info->rows_per_thread;
    data->end_row = get_thread_end_row(info->thread_id, info->rows_per_thread);
    data->scene = info->scene;
    data->info = info->render_info;
}

// Wait for threads to complete
void join_threads(pthread_t *threads)
{
    int i;

    i = 0;
    while (i < NUM_THREADS)
    {
        pthread_join(threads[i], NULL);
        i++;
    }
}

void create_threads(pthread_t *threads, t_thread_data *thread_data)
{
    int i;

    i = 0;
    while (i < NUM_THREADS)
    {
        if (pthread_create(&threads[i], NULL, render_section, &thread_data[i]) != 0)
        {
            perror("Error creating thread");
            exit(EXIT_FAILURE);
        }
        i++;
    }
}

void init_thread_data_array(t_thread_data *thread_data, t_world *sc, t_tracer *info, int rows_per_thread)
{
    t_thread_info thread_info;
    pthread_mutex_t render_mutex;
    int i;

    pthread_mutex_init(&render_mutex, NULL);
    
    i = 0;
    while (i < NUM_THREADS)
    {
        // Prepare thread info for the current thread
        thread_info.thread_id = i;
        thread_info.rows_per_thread = rows_per_thread;
        thread_info.scene = sc;
        thread_info.render_info = info;

        // Initialize thread data
        init_thread_data(&thread_data[i], &thread_info);

        // Pass the mutex to thread data if needed
        thread_data[i].render_mutex = render_mutex;

        i++;
    }
}

void ft_draw(t_tracer *info, t_world *sc)
{
    pthread_t       threads[NUM_THREADS];
    t_thread_data   thread_data[NUM_THREADS];
    int             rows_per_thread;

    // Ceiling division for even distribution
    rows_per_thread = (HEIGHT + NUM_THREADS - 1) / NUM_THREADS;
    // Initialize thread data array
    init_thread_data_array(thread_data, sc, info, rows_per_thread);
    // Create and join threads
    create_threads(threads, thread_data);
    join_threads(threads);
    // Destroy the mutex after all threads are done
    pthread_mutex_destroy(&thread_data[0].render_mutex);
}
