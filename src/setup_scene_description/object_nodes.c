/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_nodes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalbrech <aalbrech@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 20:22:16 by aalbrech          #+#    #+#             */
/*   Updated: 2025/05/02 13:00:12 by aalbrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

t_sphere	*add_new_sphere_node(t_minirt *data)
{
	t_sphere	*current;
	t_sphere	*new_node;

	current = data->objects->spheres;
	while (current && current->next)
		current = current->next;
	new_node = tracked_malloc(sizeof(t_sphere));
	if (current)
		current->next = new_node;
	else
		data->objects->spheres = new_node;
	new_node->next = NULL;
	return (new_node);
}

t_plane	*add_new_plane_node(t_minirt *data)
{
	t_plane	*current;
	t_plane	*new_node;

	current = data->objects->planes;
	while (current && current->next)
		current = current->next;
	new_node = tracked_malloc(sizeof(t_plane));
	if (current)
		current->next = new_node;
	else
		data->objects->planes = new_node;
	new_node->next = NULL;
	return (new_node);
}

t_cylinder	*add_new_cylinder_node(t_minirt *data)
{
	t_cylinder	*current;
	t_cylinder	*new_node;

	current = data->objects->cylinders;
	while (current && current->next)
		current = current->next;
	new_node = tracked_malloc(sizeof(t_cylinder));
	if (current)
		current->next = new_node;
	else
		data->objects->cylinders = new_node;
	new_node->next = NULL;
	return (new_node);
}
