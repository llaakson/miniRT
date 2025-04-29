/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_scene_checks.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalbrech <aalbrech@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 13:21:00 by aalbrech          #+#    #+#             */
/*   Updated: 2025/04/29 14:06:31 by aalbrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

int	file_extension_is_rt(char *file)
{
	char	*wanted_extension;
	char	*found_extension;

	wanted_extension = ".rt";
	found_extension = ft_strrchr(file, '.');
	if (!found_extension || ft_strcmp(file, found_extension))
		return (-1);
	if (ft_strcmp(wanted_extension, found_extension) == 1)
		return (0);
	return (-1);
}

int	no_extra_minus_in_str(char *str, int i)
{
	while (str[i])
	{
		if (str[i] == '-')
			error_exit("Element argument can't have extraneous minus signs");
		i++;
	}
	return (0);
}

void	check_missing_elements(t_minirt *data)
{
	if (data->amb_light == NULL)
	{
		data->amb_light = tracked_malloc(sizeof(t_ambient_light));
		data->amb_light->ratio = 0;
		data->amb_light->rgb = (t_xyz){0, 0, 0};
		data->amb_light->rgb = divide_color(data->amb_light->rgb);
		data->amb_light->rgb_ratio = multiply_intensity(
				data->amb_light->rgb, data->amb_light->ratio);
	}
	if (data->light == NULL)
	{
		data->light = tracked_malloc(sizeof(t_lighting));
		data->light->ratio = 0;
		data->light->coordinates = (t_xyz){0, 0, 0};
		data->light->rgb = (t_xyz){0, 0, 0};
	}
}

int	line_has_valid_chars(char *line, int line_i)
{
	while (line[line_i])
	{
		if ((ft_isdigit(line[line_i]) == 0)
			&& (line[line_i] != 32) && (line[line_i] != '.')
			&& (line[line_i] != ',') && (line[line_i] != '-')
			&& (line[line_i] != '\n'))
			return (-1);
		line_i++;
	}
	return (0);
}
