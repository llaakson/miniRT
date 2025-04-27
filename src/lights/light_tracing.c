
#include "../../include/miniRT.h"

t_xyz calculate_ambience(t_minirt *data, t_hit intersection)
{
    t_xyz result;
    t_xyz temp;

    temp = multiply_color_intensity(data->amb_light->rgb, data->amb_light->ratio);
    result = multiply_color(temp, intersection.rgb);
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
    specular.x = 1, specular.y = 1, specular.z = 1;
    view_direction = vec_normalize(vec_sub(data->camera->coordinates,intersection.coordinates));
    reflect_direction = calculate_reflection(vec_scale(light_direction,-1),intersection);
    spec = pow(fmax(vec_dot(view_direction,reflect_direction),0.0f), 68);
    spec = spec * specular_strength;
    specular = multiply_color_intensity(specular, spec);
    return (specular);
}

int calculate_light(t_minirt *data, t_hit intersection)
{
    t_ray shadow_ray;
    t_xyz lightning_direction;
    t_xyz color_str;
    t_xyz color_dot;
    double dot_product;
    double light_distance;
    uint32_t	color;
    t_xyz color_specular;

	color = 0;
    color_dot = intersection.rgb;
   	color_str = calculate_ambience(data, intersection);
    lightning_direction = vec_sub(data->light->coordinates,intersection.coordinates);
    light_distance = vec_length(lightning_direction);
    lightning_direction = vec_normalize(lightning_direction);
    shadow_ray.origin = vec_add(intersection.coordinates, vec_scale(intersection.surface_normal, 0.001f));
    shadow_ray.dir = lightning_direction;
    color = calculate_shadow(data, shadow_ray, light_distance);
    if (color != 0)
    {
        if (data->amb_light->ratio == 0)
            return (mix_color(multiply_color_intensity(intersection.rgb, 0)));
        else
            return (mix_color(color_str));
    }
    dot_product = vec_dot(intersection.surface_normal,lightning_direction);
    dot_product = fmax(0.0f, dot_product);
    color_dot = multiply_color_intensity(color_dot, dot_product);
    color_dot = multiply_color_intensity(color_dot, data->light->ratio);
    color_specular = calculate_specular(data,intersection, lightning_direction);
    color_dot = add_colors(color_dot, color_specular);
    if (!(data->amb_light->ratio == 0))
        color_dot = add_colors(color_dot, color_str);
    return(mix_color(color_dot));
}
