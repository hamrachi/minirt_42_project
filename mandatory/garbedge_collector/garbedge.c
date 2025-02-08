/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbedge.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elel-bah <elel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 00:08:16 by elel-bah          #+#    #+#             */
/*   Updated: 2024/12/30 17:12:26 by elel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT.h"

t_collector **create_and_append(t_collector **garbage_collector, void *allocated_memory)
{
    t_collector *new_node;
    t_collector *temp;

    // Create a new collector node
    new_node = malloc(sizeof(t_collector));
    if (!new_node)
        return (NULL);
    new_node->adr = allocated_memory;
    new_node->next = NULL;
    // Append the node to the linked list
    if (!*garbage_collector)
        return (*garbage_collector = new_node, garbage_collector);
    temp = *garbage_collector;
    while (temp->next)
        temp = temp->next;
    temp->next = new_node;

    return (garbage_collector);
}
// Memory allocation with garbage collector tracking
void *gc_malloc(t_collector **garbage_collector, size_t size)
{
    void *allocated_memory;

    allocated_memory = malloc(size);
    if (!allocated_memory)
        return (NULL);
    return (create_and_append(garbage_collector, allocated_memory), allocated_memory);
}

// Cleanup all memory tracked by the garbage collector
void gc_cleanup(t_collector **garbage_collector, t_collector *collector_node)
{
    if (!collector_node)
        return;
    gc_cleanup(garbage_collector, collector_node->next);
    free(collector_node->adr);
    free(collector_node);
}
