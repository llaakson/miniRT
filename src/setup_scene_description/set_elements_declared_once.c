/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_elements_declared_once.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalbrech <aalbrech@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 15:53:53 by aalbrech          #+#    #+#             */
/*   Updated: 2025/04/12 19:54:52 by aalbrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

void set_ambient_light(char *line, int line_i, t_minirt *data)
{
	char *element_info;
	int info_num;

	if (data->ambLight != NULL)
		error_exit("Element ambient lighting found twice in file");
	data->ambLight = tracked_malloc(sizeof(t_ambientLight));
	if (!data->ambLight)
		error_exit("Memory allocation failed");
	ft_bzero(data->ambLight, sizeof(t_ambientLight));
	info_num = -1;
	element_info = get_next_element_info(line, &line_i);
	while (element_info != NULL)
	{
		info_num++;
		if (info_num == 0)
			set_light_ratio(element_info, &data->ambLight->ambientLightRatio);
		else if (info_num == 1)
			set_RGB(element_info, &data->ambLight->RGB);
		else
			error_exit("Too many element arguments for ambient lighting");
		tracked_free(element_info);
		element_info = get_next_element_info(line, &line_i);
	}
	if (info_num != 1)
		error_exit("Too few element arguments for ambient light");
}

void set_camera(char *line, int line_i, t_minirt *data)
{
	char *element_info;
	int info_num;

	if (data->camera != NULL)
		error_exit("Element camera found twice in file");
	data->camera = tracked_malloc(sizeof(t_camera));
	if (!data->camera)
		error_exit("Memory allocation failed");
	ft_bzero(data->camera, sizeof(t_camera));
	info_num = -1;
	element_info = get_next_element_info(line, &line_i);
	while (element_info != NULL)
	{
		info_num++;
		if (info_num == 0)
			set_coordinates(element_info, &data->camera->coordinatesOfViewpoint);
		else if (info_num == 1)
			set_normalized_vector(element_info, &data->camera->normOrientVec);
		else if (info_num == 2)
			set_horizontal_field_of_view_in_degrees(element_info, &data->camera->FOV);
		else
			error_exit("Too many element arguments for camera");
		tracked_free(element_info);
		element_info = get_next_element_info(line, &line_i);
	}
	if (info_num != 2)
		error_exit("Too few element arguments for camera");
}

void set_light(char *line, int line_i, t_minirt *data)
{
	char *element_info;
	int info_num;

	if (data->light != NULL)
		error_exit("Element light found twice in file");
	data->light = tracked_malloc(sizeof(t_lighting));
	if (!data->light)
		error_exit("Memory allocation failed");
	ft_bzero(data->light, sizeof(t_lighting));
	info_num = -1;
	element_info = get_next_element_info(line, &line_i);
	while (element_info != NULL)
	{
		info_num++;
		if (info_num == 0)
			set_coordinates(element_info, &data->light->coordinatesOfLightPoint);
		else if (info_num == 1)
			set_light_ratio(element_info, &data->light->lightBrightnessRatio);
		else if (info_num == 2)
			set_RGB(element_info, &data->light->RGB);
		else
			error_exit("Too many element arguments for light");
		tracked_free(element_info);
		element_info = get_next_element_info(line, &line_i);
	}
	if (info_num != 2)
		error_exit("Too few element arguments for light");
}
