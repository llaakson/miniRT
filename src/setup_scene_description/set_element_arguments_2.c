/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_element_arguments_2.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalbrech <aalbrech@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 14:21:23 by aalbrech          #+#    #+#             */
/*   Updated: 2025/04/29 14:05:49 by aalbrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

void	set_fov(char *element_info, int *fov)
{
	if (ft_strchr(element_info, '.'))
		error_exit("Camera fov argument must be a whole number");
	no_extra_minus_in_str(element_info, 1);
	*fov = ft_atoi_overflow_checked(element_info);
	if (*fov < 0 || *fov > 180)
		error_exit("Camera fov argument must be in the range 0-180");
}

void	set_diameter_or_height(char *element_info, float *measurement)
{
	if (ft_strchr(element_info, ','))
		error_exit("Object diameter or height consists of only one number");
	ft_atof(element_info, measurement);
	if (*measurement <= 0.0)
		error_exit("Object diameter or height can't be negative or zero");
}
