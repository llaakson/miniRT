/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_elements_declared_once.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalbrech <aalbrech@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 15:53:53 by aalbrech          #+#    #+#             */
/*   Updated: 2025/04/27 14:39:20 by aalbrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

void	set_ambient_light(char *line, int line_i, t_minirt *data)
{
	char	*element_info;
	int		info_num;

	if (data->amb_light != NULL)
		error_exit("Element ambient lighting found twice in file");
	data->amb_light = tracked_malloc(sizeof(t_ambientLight));
	info_num = -1;
	element_info = get_next_element_info(line, &line_i);
	while (element_info != NULL)
	{
		info_num++;
		if (info_num == 0)
			set_light_ratio(element_info, &data->amb_light->ratio);
		else if (info_num == 1)
			set_rgb(element_info, &data->amb_light->rgb);
		else
			error_exit("Too many element arguments for ambient lighting");
		tracked_free(element_info);
		element_info = get_next_element_info(line, &line_i);
	}
	if (info_num != 1)
		error_exit("Too few element arguments for ambient light");
}

void	set_camera(char *line, int line_i, t_minirt *data)
{
	char	*element_info;
	int		info_num;

	if (data->camera != NULL)
		error_exit("Element camera found twice in file");
	data->camera = tracked_malloc(sizeof(t_camera));
	info_num = -1;
	element_info = get_next_element_info(line, &line_i);
	while (element_info != NULL)
	{
		info_num++;
		if (info_num == 0)
			set_coordinates(element_info, &data->camera->coordinates);
		else if (info_num == 1)
			set_normalized_vector(element_info, &data->camera->orientation);
		else if (info_num == 2)
			set_fov(element_info, &data->camera->FOV);
		else
			error_exit("Too many element arguments for camera");
		tracked_free(element_info);
		element_info = get_next_element_info(line, &line_i);
	}
	if (info_num != 2)
		error_exit("Too few element arguments for camera");
}

void	set_light(char *line, int line_i, t_minirt *data)
{
	char	*element_info;
	int		info_num;

	if (data->light != NULL)
		error_exit("Element light found twice in file");
	data->light = tracked_malloc(sizeof(t_lighting));
	info_num = -1;
	element_info = get_next_element_info(line, &line_i);
	while (element_info != NULL)
	{
		info_num++;
		if (info_num == 0)
			set_coordinates(element_info, &data->light->coordinates);
		else if (info_num == 1)
			set_light_ratio(element_info, &data->light->ratio);
		else if (info_num == 2)
			set_rgb(element_info, &data->light->rgb);
		else
			error_exit("Too many element arguments for light");
		tracked_free(element_info);
		element_info = get_next_element_info(line, &line_i);
	}
	if (info_num != 2)
		error_exit("Too few element arguments for light");
}
