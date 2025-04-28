
#include "../../include/miniRT.h"

t_xyz	calculate_ambience(t_minirt *data, t_hit intersection)
{
	t_xyz result;
 
    result = multiply_color(data->amb_light->rgb_ratio, intersection.rgb);
    return (result);
}

int calculate_shadow(t_minirt *data, t_ray ray, double light_distance)
{
    double shadow_distance;
    t_hit intersection;

    intersection = intersect(data, ray);
    if (intersection.object.spheres || intersection.object.planes || intersection.object.cylinders)
    {
        shadow_distance = vec_length(vec_sub(intersection.coordinates, ray.origin));
        if (light_distance > shadow_distance)
            return (1);
    }
    return(0);
}

t_xyz calculate_reflection(t_xyz in, t_hit intersection)
{
    t_xyz result;

    result = vec_sub(in,(vec_scale(vec_scale(intersection.surface_normal,2),vec_dot(in,intersection.surface_normal))));
    return (result);
}

t_xyz calculate_specular(t_minirt *data, t_hit intersection, t_xyz light_direction)
{
    double specular_strength;
    t_xyz view_direction;
    t_xyz reflect_direction;
    t_xyz specular;
    double spec;

    specular_strength = 0.5;
    specular = (t_xyz){1, 1, 1};
    view_direction = vec_normalize(vec_sub(data->camera->coordinates,intersection.coordinates));
    reflect_direction = calculate_reflection(vec_scale(light_direction,-1),intersection);
    spec = pow(fmax(vec_dot(view_direction,reflect_direction),0.0f), 64);
    spec = spec * specular_strength;
    specular = multiply_color_intensity(specular, spec);
    return (specular);
}

int calculate_light(t_minirt *data, t_hit intersection)
{
    t_lights light;

	light.color = 0;
    light.color_dot = intersection.rgb;
   	light.color_str = calculate_ambience(data, intersection);
    light.lightning_direction = vec_sub(data->light->coordinates,intersection.coordinates);
    light.light_distance = vec_length(light.lightning_direction);
    light.lightning_direction = vec_normalize(light.lightning_direction);
    light.shadow_ray.origin = vec_add(intersection.coordinates, vec_scale(intersection.surface_normal,  0.1f));
    light.shadow_ray.dir = light.lightning_direction;
    light.color = calculate_shadow(data, light.shadow_ray, light.light_distance);
    if (light.color != 0)
    {
        if (data->amb_light->ratio == 0)
            return (mix_color(multiply_color_intensity(intersection.rgb, 0)));
        else
            return (mix_color(light.color_str));
    }
    light.dot_product = vec_dot(intersection.surface_normal,light.lightning_direction);
    light.dot_product = fmax(0.0f, light.dot_product);
    light.color_dot = multiply_color_intensity(light.color_dot, light.dot_product);
    light.color_dot = multiply_color_intensity(light.color_dot, data->light->ratio);
    light.color_specular = calculate_specular(data,intersection, light.lightning_direction);
    light.color_dot = add_colors(light.color_dot, light.color_specular);
    if (!(data->amb_light->ratio == 0))
        light.color_dot = add_colors(light.color_dot, light.color_str);
    return(mix_color(light.color_dot));
}
