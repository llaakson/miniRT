/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_scene_checks.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalbrech <aalbrech@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 13:21:00 by aalbrech          #+#    #+#             */
/*   Updated: 2025/04/11 21:51:04 by aalbrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

int file_extension_is_rt(char *file)
{
	char *wanted_extension;
	char *found_extension;

	wanted_extension = ".rt";
	found_extension = ft_strrchr(file, '.');
	if (!found_extension || ft_strcmp(file, found_extension))
		return (-1);
	if (ft_strcmp(wanted_extension, found_extension) == 1)
		return (0);
	return (-1);
}

int no_extra_minus_in_str(char *str, int i)
{
	while (str[i])
	{
		if (str[i] == '-')
			error_exit("Element argument can't have extraneous minus signs");
		i++;
	}
	return (0);
}