/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_math.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaakson <llaakson@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 14:26:42 by llaakson          #+#    #+#             */
/*   Updated: 2025/04/25 14:28:57 by llaakson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

t_xyz	multiply_color_intensity(t_xyz color, double multiplier)
{
	t_xyz	result;

	result.x = color.x * multiplier;
	result.y = color.y * multiplier;
	result.z = color.z * multiplier;
	return (result);
}

t_xyz	multiply_color(t_xyz color1, t_xyz color2)
{
	t_xyz	result;

	result.x = color1.x * color2.x;
	result.y = color1.y * color2.y;
	result.z = color1.z * color2.z;
	return (result);
}

t_xyz	add_colors(t_xyz color1, t_xyz color2)
{
	t_xyz	result;

	result.x = color1.x + color2.x;
	result.y = color1.y + color2.y;
	result.z = color1.z + color2.z;
	return (result);
}

t_xyz	clamp_colors(t_xyz color)
{
	t_xyz	result;

	result.x = fminf(255.0f, fmaxf(0.0f, color.x));
	result.y = fminf(255.0f, fmaxf(0.0f, color.y));
	result.z = fminf(255.0f, fmaxf(0.0f, color.z));
	return (result);
}

t_xyz	divide_color(t_xyz color)
{
	t_xyz	result;

	result.x = color.x / 255;
	result.y = color.y / 255;
	result.z = color.z / 255;
	return (result);
}
