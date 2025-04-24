/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalbrech <aalbrech@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 13:38:57 by aalbrech          #+#    #+#             */
/*   Updated: 2025/04/24 14:19:14 by aalbrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

void error_exit(char *error)
{

	printf("Error: %s\n", error);
	tracked_free_all();
	track_rt_file_fd(-1);
	get_next_line(-2);
	exit(1);
}