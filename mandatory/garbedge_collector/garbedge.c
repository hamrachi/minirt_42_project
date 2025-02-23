/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbedge.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elel-bah <elel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 00:08:16 by elel-bah          #+#    #+#             */
/*   Updated: 2025/02/23 15:41:31 by elel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT.h"

t_heap_track	**create_and_append(t_heap_track **garbage_collector, \
		void *allocated_memory)
{
	t_heap_track	*new_node;
	t_heap_track	*temp;

	new_node = malloc(sizeof(t_heap_track));
	if (!new_node)
		return (NULL);
	new_node->addr = allocated_memory;
	new_node->next = NULL;
	if (!*garbage_collector)
		return (*garbage_collector = new_node, garbage_collector);
	temp = *garbage_collector;
	while (temp->next)
		temp = temp->next;
	temp->next = new_node;
	return (garbage_collector);
}

void	*gc_malloc(t_heap_track **garbage_collector, size_t size)
{
	void	*allocated_memory;

	allocated_memory = malloc(size);
	if (!allocated_memory)
		return (NULL);
	return (create_and_append(garbage_collector, allocated_memory), \
			allocated_memory);
}

void	gc_cleanup(t_heap_track **garbage_collector, \
		t_heap_track *collector_node)
{
	if (!collector_node)
		return ;
	gc_cleanup(garbage_collector, collector_node->next);
	free(collector_node->addr);
	free(collector_node);
}
