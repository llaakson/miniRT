/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_element_arguments.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalbrech <aalbrech@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 21:52:35 by aalbrech          #+#    #+#             */
/*   Updated: 2025/04/24 14:38:53 by aalbrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

void set_light_ratio(char *element_info, float *light_ratio)
{
	if (ft_strchr(element_info, ','))
		error_exit("Light ratio argument consists of only one number");
	ft_atof(element_info, light_ratio);
	if (*light_ratio < 0.0 || *light_ratio > 1.0)
		error_exit("Light ratio argument or A and L has to be in range 0.0-1.0");
}

void set_RGB(char *element_info, t_xyz *RGB)
{
	char **split_RGB;

	if (ft_strchr(element_info, '.'))
		error_exit("RGB color arguments must be whole numbers");
	split_RGB = ft_split(element_info, ',');
	if (!split_RGB)
		error_exit("Memory allocation failed");
	int i = 0;
	while (split_RGB[i])
	{
		track_pointer(split_RGB[i]);
		i++;
	}
	track_pointer(split_RGB);
	if (i - 1 != 2 || !split_RGB[2])
		error_exit("RGB colors must be three");
	ft_atof(split_RGB[0], &RGB->x);
	ft_atof(split_RGB[1], &RGB->y);
	ft_atof(split_RGB[2], &RGB->z);
	if (RGB->x < 0 || RGB->y < 0 || RGB->z < 0)
		error_exit("RGB color argument has to be 0 or bigger");
	if (RGB->x > 255 || RGB->y > 255 || RGB->z > 255)
		error_exit("RGB color argument has to be 255 or smaller");
	i = 0;
	while (split_RGB[i])
		tracked_free(split_RGB[i++]);
	tracked_free(split_RGB);
}

void set_coordinates(char *element_info, t_xyz *coordinates)
{
	char **split_coordinates;

	split_coordinates = ft_split(element_info, ',');
	if (!split_coordinates)
		error_exit("Memory allocation failed");
	int i = 0;
	while (split_coordinates[i] != NULL)
	{
		track_pointer(split_coordinates[i]);
		i++;
	}
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

void set_normalized_vector(char *element_info, t_xyz *vector)
{
	char **split_vector;
	float vector_length;

	split_vector = ft_split(element_info, ',');
	if (!split_vector)
		error_exit("Memory allocation failed");
	int i = 0;
	while (split_vector[i])
	{
		track_pointer(split_vector[i]);
		i++;
	}
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
	vector_length = vec_length(*vector);
	if (fabsf(vector_length - 1.0f) > 1e-6f)
		error_exit("A normalized vector has the length of exactly 1.0. √(x² + y² + z²) = 1.0");
	i = 0;
	while (split_vector[i])
		tracked_free(split_vector[i++]);
	tracked_free(split_vector);
}

void set_horizontal_field_of_view_in_degrees(char *element_info, int *FOV)
{
	if (ft_strchr(element_info, '.'))
		error_exit("Camera FOV argument must be a whole number");
	no_extra_minus_in_str(element_info, 1);
	*FOV = ft_atoi_overflow_checked(element_info);
	if (*FOV < 0 || *FOV > 180)
		error_exit("Camera FOV argument must be in the range 0-180");

}

void set_diameter_or_height(char *element_info, float *measurement)
{
	if (ft_strchr(element_info, ','))
		error_exit("Object diameter or height consists of only one number");
	ft_atof(element_info, measurement);
	if (*measurement < 0.0) //????????
		error_exit("Object diameter or height can't be negative");
}