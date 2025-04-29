/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tracked.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalbrech <aalbrech@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 13:34:03 by aalbrech          #+#    #+#             */
/*   Updated: 2025/04/29 13:41:42 by aalbrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

void	tracked_free(void *ptr)
{
	t_mallocs	**curr;
	t_mallocs	*to_free;
	t_mallocs	**head;

	head = get_set_tracker_head();
	if (!ptr)
		return ;
	curr = head;
	while (*curr)
	{
		if ((*curr)->ptr == ptr)
		{
			to_free = *curr;
			*curr = (*curr)->next;
			free(to_free);
			break ;
		}
		curr = &((*curr)->next);
	}
	free(ptr);
}

void	tracked_free_all(void)
{
	t_mallocs	*curr;
	t_mallocs	*temp;
	t_mallocs	**head;

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
