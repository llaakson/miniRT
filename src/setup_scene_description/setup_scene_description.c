/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_scene_description.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalbrech <aalbrech@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 13:28:09 by aalbrech          #+#    #+#             */
/*   Updated: 2025/04/27 15:06:53 by aalbrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"
//open header??

static void	set_specific_element(char *line, int i, char id[3], t_minirt *data)
{
	if (ft_strcmp(id, "A"))
		set_ambient_light(line, i, data);
	else if (ft_strcmp(id, "C"))
		set_camera(line, i, data);
	else if (ft_strcmp(id, "L"))
		set_light(line, i, data);
	else if (ft_strcmp(id, "sp"))
		set_object_sphere(line, i, data);
	else if (ft_strcmp(id, "pl"))
		set_object_plane(line, i, data);
	else if (ft_strcmp(id, "cy"))
		set_object_cylinder(line, i, data);
	else
		error_exit("Invalid element identifier in file");
}

static void	set_elements_to_struct(char *line, t_minirt *data)
{
	int		i;
	char	identifier[3];
	int		identifier_i;

	i = 0;
	while (line[i] && line[i] == 32)
		i++;
	identifier_i = 0;
	while (line[i] && identifier_i < 2 && line[i] != 32)
		identifier[identifier_i++] = line[i++];
	identifier[identifier_i] = '\0';
	if (line[i] != 32 && line[i] != '\0')
		error_exit("Invalid element identifier in file");
	if (line_has_valid_chars(line, i) == -1)
		error_exit("File has invalid char(s)");
	set_specific_element(line, i, identifier, data);
}

static void	get_elements_from_file(char *file, t_minirt *data)
{
	int		fd;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		error_exit("Couldn't open file");
	track_rt_file_fd(fd);
	data->objects = tracked_malloc(sizeof(t_object));
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

int	setup_scene_description(char *file, t_minirt *data)
{
	if (file_extension_is_rt(file) == -1)
		error_exit("Wrong file extension");
	get_elements_from_file(file, data);
	check_missing_elements(data);
	return (0);
}
