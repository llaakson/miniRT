/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_elements.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalbrech <aalbrech@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 15:53:53 by aalbrech          #+#    #+#             */
/*   Updated: 2025/04/11 02:42:26 by aalbrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

static char *get_next_element_info(char *line, int *line_i)
{
	char *info;
	int info_i;

	info = malloc(11);
	if (!info)
		return (NULL); //err??
	info_i = 0;
	if (!line || line[*line_i] == '\0') //needed?
		return (NULL);
	while (line[*line_i] && line[*line_i] == 32)
		*line_i = *line_i + 1;
	if (!line[*line_i]) //after whitespace line is done
		return (NULL);
	while (line[*line_i] && line[*line_i] != 32 && info_i < 10) //check malloc limit, what happens if more than 10?
	{
		info[info_i++] = line[*line_i];
		*line_i = *line_i + 1;
	}
	info[info_i] = '\0';
	return (info);
}

static int no_extra_minus_in_str(char *str, int i)
{
	while (str[i])
	{
		if (str[i] == '-')
			return (-1);
		i++;
	}
	return (0);
}
static float ft_atof(char *str, float *result)
{
	int i;
	float sign;
	float decimal_place;

	i = 0;
	sign = 1;
	*result = 0;
	decimal_place = 0.1;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	if (no_extra_minus_in_str(str, i) == -1)
		error_exit("EXTRA MINUS\n", NULL);
		//return (-1); //err check in calling func
	while (str[i] >= '0' && str[i] <= '9')
	{
        *result = *result * 10 + (str[i] - '0');
        i++;
    }
    // Parse decimal part (if any)
    if (str[i] == '.')
	{
        i++;
        while (str[i] >= '0' && str[i] <= '9')
		{
            *result += (str[i] - '0') * decimal_place;
            decimal_place *= 0.1;
            i++;
        }
	}
	//check max and min no overflow
	*result = *result *sign;
	return (0);
}

static void set_light_ratio(char **element_info, float *light_ratio)
{
	if (ft_strchr(*element_info, ','))
	{
		free_and_set_to_null(element_info);
		error_exit("Light ratio argument for A and L can't have comma(s) ','", NULL);
	}
	ft_atof(*element_info, light_ratio);
	if (*light_ratio < 0.0 || *light_ratio > 1.0)
	{
		free_and_set_to_null(element_info);
		error_exit("Light ratio argument or A and L has to be in range 0.0-1.0", NULL);
	}
}

static void set_RGB(char **element_info, t_xyz *RGB)
{
	char **split_RGB;

	if (ft_strchr(*element_info, '.'))
	{
		free_and_set_to_null(element_info);
		error_exit("RGB color arguments must be whole numbers", NULL);
	}
	split_RGB = ft_split(*element_info, ',');
	int i = 0;
	while (split_RGB[i])
		i++;
	if (i - 1 != 2 || !split_RGB[2])
	{
		free_and_set_to_null(element_info);
		//free splitrgb;
		error_exit("RGB colors must be three", NULL);
	}
	ft_atof(split_RGB[0], &RGB->x);
	ft_atof(split_RGB[1], &RGB->y);
	ft_atof(split_RGB[2], &RGB->z);
	if (RGB->x < 0 || RGB->y < 0 || RGB->z < 0)
	{
		free_and_set_to_null(element_info);
		//free splitrgb;
		error_exit("RGB color argument has to be 0 or bigger", NULL);
	}
	if (RGB->x > 255 || RGB->y > 255 || RGB->z > 255)
	{
		free_and_set_to_null(element_info);
		//free splitrgb;
		error_exit("RGB color argument has to be 255 or smaller", NULL);
	}
}

void set_ambient_light(char *line, int line_i, t_minirt *data)
{
	char *element_info;
	int info_num;

	if (data->ambLight != NULL)
		error_exit("Element ambient lighting found twice in file", NULL);
	data->ambLight = malloc(sizeof(t_ambientLight));
	if (!data->ambLight)
		error_exit("Memory allocation failed", NULL);
	info_num = -1;
	element_info = get_next_element_info(line, &line_i);
	while (element_info != NULL)
	{
		info_num++;
		if (info_num == 0)
			set_light_ratio(&element_info, &data->ambLight->ambientLightRatio);
		else if (info_num == 1)
			set_RGB(&element_info, &data->ambLight->RGB); //send ref or something?
		else
		{
			free_and_set_to_null(&element_info);
			error_exit("Too many element arguments for ambient lighting", NULL);
		}
		free_and_set_to_null(&element_info);
		element_info = get_next_element_info(line, &line_i);
	}
	if (info_num != 1) //check SIMILAR in all funcs test "C "
	{
		free_and_set_to_null(&element_info);
		error_exit("Too few element arguments for ambient light", NULL);
	}
}

static void set_coordinates(char **element_info, t_xyz *coordinates)
{
	char **split_coordinates;

	/*if (ft_strchr(*element_info, '.'))
	{
		free_and_set_to_null(element_info);
		error_exit("Coordinate arguments must be whole numbers", NULL); //change to cant be decimal??
	}*/
	split_coordinates = ft_split(*element_info, ',');
	int i = 0;
	while (split_coordinates[i])
		i++;
	if (i - 1 != 2 || !split_coordinates[2])
	{
		free_and_set_to_null(element_info);
		//free splitrgb;
		error_exit("Coordinates has to be three numbers", NULL);
	}
	ft_atof(split_coordinates[0], &coordinates->x);
	ft_atof(split_coordinates[1], &coordinates->y);
	ft_atof(split_coordinates[2], &coordinates->z);
}

static void set_normalized_vector(char **element_info, t_xyz *vector)
{
	char **split_vector;

	split_vector = ft_split(*element_info, ',');
	int i = 0;
	while (split_vector[i])
		i++;
	if (i - 1 != 2 || !split_vector[2])
	{
		free_and_set_to_null(element_info);
		//free splitrgb;
		error_exit("Normalized vectors need three ... ", NULL);
	}
	ft_atof(split_vector[0], &vector->x);
	ft_atof(split_vector[1], &vector->y);
	ft_atof(split_vector[2], &vector->z);
	if (vector->x < -1.0 || vector->y < -1.0 || vector->z < -1.0)
	{
		free_and_set_to_null(element_info);
		//free splitrgb;
		error_exit("Normalized vector argument has to be -1 or bigger", NULL);
	}
	if (vector->x > 1.0 || vector->y > 1.0 || vector->z > 1.0)
	{
		free_and_set_to_null(element_info);
		//free splitrgb;
		error_exit("Normalized vector argument has to be 1 or smaller", NULL);
	}
}
static void set_horizontal_field_of_view_in_degrees(char **element_info, int *FOV)
{
	if (ft_strchr(*element_info, '.'))
	{
		free_and_set_to_null(element_info);
		error_exit("Camera FOV argument must be a whole number", NULL); //change to cant be decimal??
	}
	if (no_extra_minus_in_str(*element_info, 1) == -1)
	{
		free_and_set_to_null(element_info);
		error_exit("Element argument can't have many minus signs", NULL); //change to cant be decimal??
	}
	*FOV = ft_atoi(*element_info);
	if (*FOV < 0 || *FOV > 180)
	{
		free_and_set_to_null(element_info);
		error_exit("Camera FOV argument must be in the range 0-180", NULL); //change to cant be decimal??
	}

}

void set_camera(char *line, int line_i, t_minirt *data)
{
	char *element_info;
	int info_num;

	if (data->camera != NULL)
		error_exit("Element camera found twice in file", NULL);
	data->camera = malloc(sizeof(t_camera));
	if (!data->camera)
		error_exit("Memory allocation failed", NULL);
	info_num = -1;
	element_info = get_next_element_info(line, &line_i);
	while (element_info != NULL)
	{
		info_num++;
		if (info_num == 0)
			set_coordinates(&element_info, &data->camera->coordinatesOfViewpoint);
		else if (info_num == 1)
			set_normalized_vector(&element_info, &data->camera->normOrientVec);
		else if (info_num == 2)
			set_horizontal_field_of_view_in_degrees(&element_info, &data->camera->FOV);
		else
		{
			free_and_set_to_null(&element_info);
			error_exit("Too many element arguments for camera", NULL);
		}
		free_and_set_to_null(&element_info);
		element_info = get_next_element_info(line, &line_i);
	}
	if (info_num != 2) //check SIMILAR in all funcs test "C "
	{
		free_and_set_to_null(&element_info);
		error_exit("Too few element arguments for camera", NULL);
	}
	//free element_info in ALL funcs
}

void set_light(char *line, int line_i, t_minirt *data)
{
	char *element_info;
	int info_num;

	if (data->light != NULL)
		error_exit("Element light found twice in file", NULL);
	data->light = malloc(sizeof(t_lighting));
	if (!data->light)
		error_exit("Memory allocation failed", NULL);
	info_num = -1;
	element_info = get_next_element_info(line, &line_i);
	while (element_info != NULL)
	{
		info_num++;
		if (info_num == 0)
			set_coordinates(&element_info, &data->light->coordinatesOfLightPoint);
		else if (info_num == 1)
			set_light_ratio(&element_info, &data->light->lightBrightnessRatio);
		else if (info_num == 2)
			set_RGB(&element_info, &data->light->RGB);
		else
		{
			free_and_set_to_null(&element_info);
			error_exit("Too many element arguments for light", NULL);
		}
		free_and_set_to_null(&element_info);
		element_info = get_next_element_info(line, &line_i);
	}
	if (info_num != 2) //check SIMILAR in all funcs test "C "
	{
		free_and_set_to_null(&element_info);
		error_exit("Too few element arguments for light", NULL);
	}
	//free element_info in ALL funcs
}