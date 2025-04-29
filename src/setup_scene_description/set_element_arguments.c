/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_element_arguments.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalbrech <aalbrech@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 21:52:35 by aalbrech          #+#    #+#             */
/*   Updated: 2025/04/29 13:47:31 by aalbrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

void	set_light_ratio(char *element_info, float *light_ratio)
{
	if (ft_strchr(element_info, ','))
		error_exit("Light ratio argument consists of only one number");
	ft_atof(element_info, light_ratio);
	if (*light_ratio < 0.0 || *light_ratio > 1.0)
		error_exit("Light ratio argument has to be in range 0.0-1.0");
}

void	set_rgb(char *element_info, t_xyz *rgb)
{
	char	**split_rgb;
	int		i;

	if (ft_strchr(element_info, '.'))
		error_exit("rgb color arguments must be whole numbers");
	split_rgb = ft_split(element_info, ',');
	if (!split_rgb)
		error_exit("Memory allocation failed");
	i = 0;
	while (split_rgb[i])
		track_pointer(split_rgb[i++]);
	track_pointer(split_rgb);
	if (i - 1 != 2 || !split_rgb[2])
		error_exit("rgb colors must be three");
	ft_atof(split_rgb[0], &rgb->x);
	ft_atof(split_rgb[1], &rgb->y);
	ft_atof(split_rgb[2], &rgb->z);
	if (rgb->x < 0 || rgb->y < 0 || rgb->z < 0)
		error_exit("rgb color argument has to be 0 or bigger");
	if (rgb->x > 255 || rgb->y > 255 || rgb->z > 255)
		error_exit("rgb color argument has to be 255 or smaller");
	i = 0;
	while (split_rgb[i])
		tracked_free(split_rgb[i++]);
	tracked_free(split_rgb);
}

void	set_coordinates(char *element_info, t_xyz *coordinates)
{
	char	**split_coordinates;
	int		i;

	split_coordinates = ft_split(element_info, ',');
	if (!split_coordinates)
		error_exit("Memory allocation failed");
	i = 0;
	while (split_coordinates[i] != NULL)
		track_pointer(split_coordinates[i++]);
	track_pointer(split_coordinates);
	if (i - 1 != 2 || !split_coordinates[2])
		error_exit("Coordinates has to be three numbers, x, y and z");
	ft_atof(split_coordinates[0], &coordinates->x);
	ft_atof(split_coordinates[1], &coordinates->y);
	ft_atof(split_coordinates[2], &coordinates->z);
	i = 0;
	while (split_coordinates[i])
		tracked_free(split_coordinates[i++]);
	tracked_free(split_coordinates);
}

void	set_normalized_vector(char *element_info, t_xyz *vector)
{
	char	**split_vector;
	int		i;

	split_vector = ft_split(element_info, ',');
	if (!split_vector)
		error_exit("Memory allocation failed");
	i = 0;
	while (split_vector[i])
		track_pointer(split_vector[i++]);
	track_pointer(split_vector);
	if (i - 1 != 2 || !split_vector[2])
		error_exit("Normalized vectors need three components, x, y and z");
	ft_atof(split_vector[0], &vector->x);
	ft_atof(split_vector[1], &vector->y);
	ft_atof(split_vector[2], &vector->z);
	if (vector->x < -1.0 || vector->y < -1.0 || vector->z < -1.0)
		error_exit("Normalized vector argument has to be -1 or bigger");
	if (vector->x > 1.0 || vector->y > 1.0 || vector->z > 1.0)
		error_exit("Normalized vector argument has to be 1 or smaller");
	if (fabsf(vec_length(*vector) - 1.0f) > 0.000001)
		error_exit("Normalized vector has length 1.0. √(x² + y² + z²) = 1.0");
	i = 0;
	while (split_vector[i])
		tracked_free(split_vector[i++]);
	tracked_free(split_vector);
}
