/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_tracing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaakson <llaakson@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 18:29:21 by llaakson          #+#    #+#             */
/*   Updated: 2025/04/29 19:47:11 by llaakson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

int	calculate_shadow(t_minirt *data, t_ray ray, double light_distance)
{
	double	shadow;
	t_hit	intersection;

	intersection = intersect(data, ray);
	if (intersection.closest_intersect != INFINITY)
	{
		shadow = vec_length(vec_sub(intersection.coordinates, ray.origin));
		if (light_distance > shadow)
			return (1);
	}
	return (0);
}

t_xyz	calculate_reflection(t_xyz in, t_hit intersection)
{
	t_xyz	result;

	result = vec_sub(in, (vec_scale(vec_scale(intersection.surface_normal, 2),
					vec_dot(in, intersection.surface_normal))));
	return (result);
}

t_xyz	calculate_specular(t_minirt *data, t_hit hit, t_xyz direction)
{
	double	specular_strength;
	t_xyz	view_direction;
	t_xyz	reflect_direction;
	t_xyz	specular;
	double	spec;

	specular_strength = 0.5;
	specular = (t_xyz){1, 1, 1};
	view_direction = vec_sub(data->camera->coordinates, hit.coordinates);
	view_direction = vec_normalize(view_direction);
	reflect_direction = calculate_reflection(vec_scale(direction, -1), hit);
	spec = pow(fmax(vec_dot(view_direction, reflect_direction), 0.0f), 64);
	spec = spec * specular_strength;
	specular = multiply_intensity(specular, spec);
	return (specular);
}

t_xyz	color_mixer(t_minirt *data, t_hit intersection, t_lights light)
{
	light.dot_product = fmax(0.0f, light.dot_product);
	light.c_dot = multiply_intensity(light.c_dot, light.dot_product);
	light.c_dot = multiply_intensity(light.c_dot, data->light->ratio);
	light.c_specular = calculate_specular(data, intersection, light.direction);
	light.c_dot = add_colors(light.c_dot, light.c_specular);
	if (!(data->amb_light->ratio == 0))
		light.c_dot = add_colors(light.c_dot, light.c_str);
	return (light.c_dot);
}

int	calculate_light(t_minirt *data, t_hit intersection)
{
	t_lights	light;

	light.color = 0;
	light.c_dot = intersection.rgb;
	light.c_str = multiply_color(data->amb_light->rgb_ratio, intersection.rgb);
	light.direction = vec_sub(data->light->coordinates,
			intersection.coordinates);
	light.light_distance = vec_length(light.direction);
	light.direction = vec_normalize(light.direction);
	light.shadow_ray.origin = vec_add(intersection.coordinates,
			vec_scale(intersection.surface_normal, 0.1f));
	light.shadow_ray.dir = light.direction;
	light.color = calculate_shadow(data,
			light.shadow_ray, light.light_distance);
	light.dot_product = vec_dot(intersection.surface_normal, light.direction);
	if (light.color != 0 || light.dot_product < 0)
	{
		if (data->amb_light->ratio == 0)
			return (mix_color(multiply_intensity(intersection.rgb, 0)));
		else
			return (mix_color(light.c_str));
	}
	light.c_dot = color_mixer(data, intersection, light);
	return (mix_color(light.c_dot));
}
