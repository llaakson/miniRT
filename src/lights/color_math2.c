/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_math2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaakson <llaakson@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 14:20:53 by llaakson          #+#    #+#             */
/*   Updated: 2025/04/25 14:26:25 by llaakson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

int32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

uint32_t	mix_color(t_xyz color)
{
	uint32_t	result;

	color.x = color.x * 255;
	color.y = color.y * 255;
	color.z = color.z * 255;
	color = clamp_colors(color);
	result = ft_pixel(color.x, color.y, color.z, 255);
	return (result);
}
