/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalbrech <aalbrech@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 13:38:57 by aalbrech          #+#    #+#             */
/*   Updated: 2025/04/28 11:43:57 by aalbrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

void *store_pointer(int i,  void *ptr) 
{
    static void* stored_ptr = NULL;

    if (i == 1) 
        stored_ptr = ptr;
    return stored_ptr;
}

void	error_exit(char *error)
{
	void *ptr = NULL;
	ptr = store_pointer(0, ptr);
	printf("Error: %s\n", error);
	if (ptr != NULL)
	{
		mlx_close_window(ptr);
		mlx_terminate(ptr);
	}
	tracked_free_all();
	track_rt_file_fd(-1);
	get_next_line(-2);
	exit(1);
}
