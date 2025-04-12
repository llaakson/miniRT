/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_elements_objects.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalbrech <aalbrech@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 22:05:18 by aalbrech          #+#    #+#             */
/*   Updated: 2025/04/12 20:54:50 by aalbrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

void set_object_sphere(char *line, int line_i, t_minirt *data)
{
	char *element_info;
	int info_num;
	t_sphere *new_node;

	new_node = add_new_sphere_node(data);
	info_num = -1;
	element_info = get_next_element_info(line, &line_i);
	while (element_info != NULL)
	{
		info_num++;
		if (info_num == 0)
			set_coordinates(element_info, &new_node->sphereCenter);
		else if (info_num == 1)
			set_diameter_or_height(element_info, &new_node->diameter);
		else if (info_num == 2)
			set_RGB(element_info, &new_node->RGB);
		else
			error_exit("Too many element arguments for sphere");
		tracked_free(element_info);
		element_info = get_next_element_info(line, &line_i);
	}
	if (info_num != 2)
		error_exit("Too few element arguments for sphere");
}

void set_object_plane(char *line, int line_i, t_minirt *data)
{
	char *element_info;
	int info_num;
	t_plane *new_node;

	new_node = add_new_plane_node(data);
	info_num = -1;
	element_info = get_next_element_info(line, &line_i);
	while (element_info != NULL)
	{
		info_num++;
		if (info_num == 0)
			set_coordinates(element_info, &new_node->pointInPlane);
		else if (info_num == 1)
			set_normalized_vector(element_info, &new_node->normNormalVec);
		else if (info_num == 2)
			set_RGB(element_info, &new_node->RGB);
		else
			error_exit("Too many element arguments for plane");
		tracked_free(element_info);
		element_info = get_next_element_info(line, &line_i);
	}
	if (info_num != 2)
		error_exit("Too few element arguments for plane");
}

void set_object_cylinder(char *line, int line_i, t_minirt *data)
{
	char *element_info;
	int info_num;
	t_cylinder *new_node;

	new_node = add_new_cylinder_node(data);
	info_num = -1;
	element_info = get_next_element_info(line, &line_i);
	while (element_info != NULL)
	{
		info_num++;
		if (info_num == 0)
			set_coordinates(element_info, &new_node->cylinderCenter);
		else if (info_num == 1)
			set_normalized_vector(element_info, &new_node->normVecOfAxis);
		else if (info_num == 2)
			set_diameter_or_height(element_info, &new_node->diameter);
		else if (info_num == 3)
			set_diameter_or_height(element_info, &new_node->height);
		else if (info_num == 4)
			set_RGB(element_info, &new_node->RGB);
		else
			error_exit("Too many element arguments for plane");
		tracked_free(element_info);
		element_info = get_next_element_info(line, &line_i);
	}
	if (info_num != 4)
		error_exit("Too few element arguments for plane");
}