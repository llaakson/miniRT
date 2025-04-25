/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_scene_description.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalbrech <aalbrech@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 13:28:09 by aalbrech          #+#    #+#             */
/*   Updated: 2025/04/24 14:20:15 by aalbrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"
//open header??


static int line_has_valid_chars(char *line, int line_i)
{
	while (line[line_i])
	{
		if ((ft_isdigit(line[line_i]) == 0) &&
		(line[line_i] != 32 ) && (line[line_i] != '.') &&
		(line[line_i] != ',') && (line[line_i] !=  '-') &&
		(line[line_i] != '\n'))
			return (-1);
		line_i++;
	}
	return (0);
}

static void set_elements_to_struct(char *line, t_minirt *data)
{
	int i;
	char identifier[3];
	int identifier_i;

	i = 0;
	while (line[i] && line[i] == 32) //SPACE but nother other whitespace
		i++;
	identifier_i = 0;
	while (line[i] && identifier_i < 2 && line[i] != 32)
		identifier[identifier_i++] = line[i++];
	identifier[identifier_i] = '\0';
	if (line[i] != 32 && line[i] != '\0')
		error_exit("Invalid element identifier in file");
	if (line_has_valid_chars(line, i) == -1)
		error_exit("File has invalid char(s)");
	if (ft_strcmp(identifier, "A"))
		set_ambient_light(line, i, data);
	else if (ft_strcmp(identifier, "C"))
		set_camera(line, i, data);
	else if (ft_strcmp(identifier, "L"))
		set_light(line, i, data);
	else if (ft_strcmp(identifier, "sp"))
		set_object_sphere(line, i, data);
	else if (ft_strcmp(identifier, "pl"))
		set_object_plane(line, i, data);
	else if (ft_strcmp(identifier, "cy"))
		set_object_cylinder(line, i, data);
	else
		error_exit("Invalid element identifier in file");
}

static void get_elements_from_file(char *file, t_minirt *data)
{
	int fd;
	char *line;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		error_exit("Couldn't open file");
	track_rt_file_fd(fd);
	data->objects = tracked_malloc(sizeof(t_object));
	if (!data->objects)
		error_exit("Memory allocation failed");
	ft_memset(data->objects, 0, sizeof(t_object));
	line = get_next_line(fd);
	track_pointer(line);
	while (line != NULL)
	{
		if (!(line[0] == '\n' && line[1] == '\0'))
			set_elements_to_struct(line, data);
		tracked_free(line);
		line = get_next_line(fd);
		track_pointer(line);
	}
	track_rt_file_fd(-1);
	tracked_free(line);
}

static void check_missing_elements(t_minirt *data)
{
	if (data->ambLight == NULL)
	{
		data->ambLight = tracked_malloc(sizeof(t_ambientLight));
		if (!data->ambLight)
			error_exit("Memory allocation failed");
		ft_bzero(data->ambLight, sizeof(t_ambientLight));
		data->ambLight->ambientLightRatio = 0;
		data->ambLight->RGB.x = 0, data->ambLight->RGB.y = 0, data->ambLight->RGB.z = 0;
	}

	if (data->light == NULL)
	{
		data->light = tracked_malloc(sizeof(t_lighting));
		if (!data->light)
			error_exit("Memory allocation failed");
		ft_bzero(data->light, sizeof(t_lighting));
		data->light->lightBrightnessRatio = 0;
		data->light->coordinatesOfLightPoint.x = 0, data->light->coordinatesOfLightPoint.y = 0, data->light->coordinatesOfLightPoint.z = 0;
		data->light->RGB.x = 0, data->light->RGB.y = 0, data->light->RGB.z = 0;
	}
}

int setup_scene_description(char *file, t_minirt *data)
{
	if (file_extension_is_rt(file) == -1)
		error_exit("Wrong file extension");
	get_elements_from_file(file, data);
	check_missing_elements(data);
	return (0);
}