/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_tracker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalbrech <aalbrech@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 19:08:50 by aalbrech          #+#    #+#             */
/*   Updated: 2025/04/12 19:44:10 by aalbrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

static t_mallocs* head = NULL;

void* tracked_malloc(size_t size)
{
    void* ptr = malloc(size);
    if (!ptr) return NULL;

    t_mallocs* node = malloc(sizeof(t_mallocs));
    if (!node)
	{
        free(ptr);
        return NULL;
    }

    node->ptr = ptr;
    node->next = head;
    head = node;
    return ptr;
}

void tracked_free(void* ptr)
{
    if (!ptr) return;

    t_mallocs** curr = &head;
    while (*curr) {
        if ((*curr)->ptr == ptr) {
            t_mallocs* to_free = *curr;
            *curr = (*curr)->next;
            free(to_free);
            break;
        }
        curr = &((*curr)->next);
    }
    free(ptr);
}

void tracked_free_all(void)
{
    t_mallocs* curr = head;
    while (curr) {
        free(curr->ptr);
        t_mallocs* temp = curr;
        curr = curr->next;
        free(temp);
    }
    head = NULL;
}