/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_scene_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalbrech <aalbrech@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 21:45:32 by aalbrech          #+#    #+#             */
/*   Updated: 2025/05/02 13:22:58 by aalbrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

char	*get_next_element_info(char *line, int *line_i)
{
	char	*info;
	int		info_i;
	int		buffer_size;

	buffer_size = 20;
	info = tracked_malloc(buffer_size);
	info_i = 0;
	if (!line)
		return (NULL);
	while (line[*line_i] && line[*line_i] == 32)
		*line_i = *line_i + 1;
	if (!line[*line_i])
		return (NULL);
	while (line[*line_i] && line[*line_i] != 32)
	{
		if (info_i >= buffer_size - 1)
		{
			buffer_size *= 2;
			info = tracked_realloc(info, buffer_size);
		}
		info[info_i++] = line[*line_i];
		*line_i = *line_i + 1;
	}
	info[info_i] = '\0';
	return (info);
}

void	track_rt_file_fd(int fd)
{
	static int	saved_fd = -2;

	if (fd > -1)
		saved_fd = fd;
	if (fd == -1 && saved_fd != -2)
	{
		close(saved_fd);
		saved_fd = -2;
	}
}

int	count_chars(char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (count);
}
