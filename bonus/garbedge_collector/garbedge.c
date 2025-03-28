/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbedge.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamrachi <hamrachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 00:08:16 by elel-bah          #+#    #+#             */
/*   Updated: 2025/03/01 16:44:27 by hamrachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT_bonus.h"

t_heap_track	**create_and_append_b(t_heap_track **g_garbage_collector, \
		void *allocated_memory)
{
	t_heap_track	*new_node;
	t_heap_track	*temp;

	new_node = malloc(sizeof(t_heap_track));
	if (!new_node)
		return (NULL);
	new_node->addr = allocated_memory;
	new_node->next = NULL;
	if (!*g_garbage_collector)
		return (*g_garbage_collector = new_node, g_garbage_collector);
	temp = *g_garbage_collector;
	while (temp->next)
		temp = temp->next;
	temp->next = new_node;
	return (g_garbage_collector);
}

void	*gc_malloc_b(t_heap_track **g_garbage_collector, size_t size)
{
	void	*allocated_memory;

	allocated_memory = malloc(size);
	if (!allocated_memory)
		return (NULL);
	return (create_and_append_b(g_garbage_collector, allocated_memory), \
			allocated_memory);
}

void	gc_cleanup_b(t_heap_track **g_garbage_collector, \
	t_heap_track *collector_node)
{
	t_heap_track	*current;
	t_heap_track	*next_node;

	current = collector_node;
	while (current)
	{
		next_node = current->next;
		free(current->addr);
		free(current);
		current = next_node;
	}
	*g_garbage_collector = NULL;
}
