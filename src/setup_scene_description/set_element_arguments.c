/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_element_arguments.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalbrech <aalbrech@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 21:52:35 by aalbrech          #+#    #+#             */
/*   Updated: 2025/05/02 13:32:35 by aalbrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

void	set_light_ratio(char *element_info, double *light_ratio)
{
	if (ft_strchr(element_info, ','))
		error_exit("Light ratio argument consists of only one number");
	ft_atof(element_info, light_ratio);
	if (*light_ratio < 0.0 || *light_ratio > 1.0)
		error_exit("Light ratio argument has to be in range 0.0-1.0");
}

static void	split_element_components(t_xyz *xyz, char *element_info)
{
	char	**split;
	int		i;

	split = ft_split(element_info, ',');
	if (!split)
		error_exit("Memory allocation failed");
	i = 0;
	while (split[i])
		track_pointer(split[i++]);
	track_pointer(split);
	if (count_chars(element_info, ',') != 2)
		error_exit("Extraneous comma ',' found in file");
	if (i - 1 != 2 || !split[2])
		error_exit("Vector, coordinates and RGB must have three components");
	ft_atof(split[0], &xyz->x);
	ft_atof(split[1], &xyz->y);
	ft_atof(split[2], &xyz->z);
	i = 0;
	while (split[i])
		tracked_free(split[i++]);
	tracked_free(split);
}

void	set_rgb(char *element_info, t_xyz *rgb)
{
	if (ft_strchr(element_info, '.'))
		error_exit("rgb color arguments must be whole numbers");
	split_element_components(rgb, element_info);
	if (rgb->x < 0 || rgb->y < 0 || rgb->z < 0)
		error_exit("rgb color argument has to be 0 or bigger");
	if (rgb->x > 255 || rgb->y > 255 || rgb->z > 255)
		error_exit("rgb color argument has to be 255 or smaller");
}

void	set_coordinates(char *element_info, t_xyz *coordinates)
{
	split_element_components(coordinates, element_info);
}

void	set_normalized_vector(char *element_info, t_xyz *vector)
{
	split_element_components(vector, element_info);
	if (fabs(vector->x) > 1.0 || fabs(vector->y) > 1.0 || fabs(vector->z) > 1.0)
		error_exit("Normalized vector argument must be between -1 and 1");
	if (fabs(vec_length(*vector) - 1.0f) > 0.000001)
		error_exit("Normalized vector has length 1.0. √(x² + y² + z²) = 1.0");
}
