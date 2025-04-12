/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_scene_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalbrech <aalbrech@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 21:45:32 by aalbrech          #+#    #+#             */
/*   Updated: 2025/04/12 20:43:21 by aalbrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

char *get_next_element_info(char *line, int *line_i)
{
	char *info;
	int info_i;

	info = tracked_malloc(20); //must be big enough, how big?
	if (!info)
		error_exit("Memory allocation failed");
	info_i = 0;
	if (!line || line[*line_i] == '\0') //needed?
		return (NULL);
	while (line[*line_i] && line[*line_i] == 32)
		*line_i = *line_i + 1;
	if (!line[*line_i]) //after whitespace line is done
		return (NULL);
	while (line[*line_i] && line[*line_i] != 32 && info_i < 19)
	{
		info[info_i++] = line[*line_i];
		*line_i = *line_i + 1;
	}
	info[info_i] = '\0';
	return (info);
}