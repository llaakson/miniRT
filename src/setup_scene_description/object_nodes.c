/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_nodes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalbrech <aalbrech@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 20:22:16 by aalbrech          #+#    #+#             */
/*   Updated: 2025/04/24 12:18:06 by aalbrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

t_sphere *add_new_sphere_node(t_minirt *data)
{
	t_sphere *prev = NULL;
	t_sphere *current = data->objects->spheres;
	t_sphere *new_node;

	while (current != NULL)
	{
		prev = current;
		current = current->next;
	}

	new_node = tracked_malloc(sizeof(t_sphere));
	if (!new_node)
		error_exit("Memory allocation failed");
	ft_bzero(new_node, sizeof(t_sphere));
	new_node->prev = prev;

	if (prev)
		prev->next = new_node;
	else
		data->objects->spheres = new_node;

	return new_node;
}

t_plane *add_new_plane_node(t_minirt *data)
{
	t_plane *prev = NULL;
	t_plane *current = data->objects->planes;
	t_plane *new_node;

	while (current != NULL)
	{
		prev = current;
		current = current->next;
	}

	new_node = tracked_malloc(sizeof(t_plane));
	if (!new_node)
		error_exit("Memory allocation failed");
	ft_bzero(new_node, sizeof(t_plane));
	new_node->prev = prev;

	if (prev)
		prev->next = new_node;
	else
		data->objects->planes = new_node;

	return new_node;
}

t_cylinder *add_new_cylinder_node(t_minirt *data)
{
	t_cylinder *prev = NULL;
	t_cylinder *current = data->objects->cylinders;
	t_cylinder *new_node;

	while (current != NULL)
	{
		prev = current;
		current = current->next;
	}
	new_node = tracked_malloc(sizeof(t_cylinder));
	if (!new_node)
		error_exit("Memory allocation failed");
	ft_bzero(new_node, sizeof(t_cylinder));
	new_node->prev = prev;

	if (prev)
		prev->next = new_node;
	else
		data->objects->cylinders = new_node;

	return new_node;
}
