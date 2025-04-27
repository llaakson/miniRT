/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_tracker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalbrech <aalbrech@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 19:08:50 by aalbrech          #+#    #+#             */
/*   Updated: 2025/04/27 15:08:54 by aalbrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

static t_mallocs **get_set_tracker_head(void)
{
	static t_mallocs *head = NULL;
	return (&head);
}

void* tracked_malloc(size_t size)
{
    void* ptr;
	t_mallocs *node;
	t_mallocs **head;

	head = get_set_tracker_head();
	ptr = malloc(size);
    if (!ptr)
		error_exit("Memory allocation failed");
	ft_bzero(ptr, size);
    node = malloc(sizeof(t_mallocs));
    if (!node)
	{
        free(ptr);
        error_exit("Memory allocation failed");
    }
    node->ptr = ptr;
    node->next = *head;
    *head = node;
    return (ptr);
}

void track_pointer(void* ptr)
{
	t_mallocs *node;
	t_mallocs **head;

	head = get_set_tracker_head();
    if (!ptr)
		return ;
    node = malloc(sizeof(t_mallocs));
    if (!node)
	{
		free(ptr);
		error_exit("Memory allocation failed");
	}
    node->ptr = ptr;
    node->next = *head;
    *head = node;
}

void tracked_free(void* ptr)
{
	t_mallocs **curr;
	t_mallocs *to_free;
	t_mallocs **head;

	head = get_set_tracker_head();
    if (!ptr)
		return;
    curr = head;
    while (*curr)
	{
        if ((*curr)->ptr == ptr)
		{
            to_free = *curr;
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
    t_mallocs* curr;
	t_mallocs *temp;
	t_mallocs **head;

	head = get_set_tracker_head();
	curr = *head;
    while (curr)
	{
        free(curr->ptr);
        temp = curr;
        curr = curr->next;
        free(temp);
    }
    *head = NULL;
}

char	*tracked_realloc(char *str, size_t len)
{
	char	*new;
	size_t	i;

	new = tracked_malloc(len + 1);
	if (!new)
	{
		tracked_free(str);
		error_exit("Memory allocation failed");
	}
	if (!str)
		return (new);
	i = 0;
	while ((str[i]) && (i < len))
	{
		new[i] = str[i];
		i++;
	}
	tracked_free(str);
	new[i] = '\0';
	return (new);
}
