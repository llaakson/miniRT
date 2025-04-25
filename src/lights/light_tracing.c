
#include "../../include/miniRT.h"

t_xyz calculate_ambience(t_minirt *data, t_intersection intersection)
{
    t_xyz result;
    t_xyz temp;

    temp = multiply_color_intensity(data->ambLight->RGB, data->ambLight->ambientLightRatio);
    result = multiply_color(temp, intersection.RGB);
    return (result);
}

int calculate_shadow(t_minirt *data, t_ray ray, double light_distance)
{
    double shadow_distance;
    t_intersection intersection;

    intersection = intersect(data, ray);
    if (intersection.object.spheres || intersection.object.planes || intersection.object.cylinders)
    {   
        shadow_distance = vec_length(vec_subtract(intersection.coorinates, ray.origin));
        if (light_distance > shadow_distance)
            return (1);
    }
    return(0);
}

t_xyz calculate_reflection(t_xyz in, t_intersection intersection)
{
    t_xyz result;

    result = vec_subtract(in,(vec_scale(vec_scale(intersection.surface_normal,2),vec_dot(in,intersection.surface_normal)))); 
    return (result);
}

t_xyz calculate_specular(t_minirt *data, t_intersection intersection, t_xyz light_direction)
{
    double specular_strength;
    t_xyz view_direction;
    t_xyz reflect_direction;
    t_xyz specular;
    double spec;

    specular_strength = 0.5;
    specular.x = 1, specular.y = 1, specular.z = 1;
    view_direction = vec_normalize(vec_subtract(data->camera->coordinatesOfViewpoint,intersection.coorinates));
    reflect_direction = calculate_reflection(vec_scale(light_direction,-1),intersection);
    spec = pow(fmax(vec_dot(view_direction,reflect_direction),0.0f), 68);
    spec = spec * specular_strength;
    specular = multiply_color_intensity(specular, spec);
    return (specular);
}

int calculate_light(t_minirt *data, t_intersection intersection)
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
    color_dot = intersection.RGB;
   	color_str = calculate_ambience(data, intersection);
    lightning_direction = vec_subtract(data->light->coordinatesOfLightPoint,intersection.coorinates);
    light_distance = vec_length(lightning_direction);
    lightning_direction = vec_normalize(lightning_direction);
    shadow_ray.origin = vec_add(intersection.coorinates, vec_scale(intersection.surface_normal, 0.001f)); //need intersection.normal
    shadow_ray.direction = lightning_direction;
    color = calculate_shadow(data, shadow_ray, light_distance);
    if (color != 0)
        return (mix_color(color_str));
    dot_product = vec_dot(intersection.surface_normal,lightning_direction);
    dot_product = fmax(0.0f, dot_product);
    color_dot = multiply_color_intensity(color_dot, dot_product);
    color_dot = multiply_color_intensity(color_dot, data->light->lightBrightnessRatio);
    color_specular = calculate_specular(data,intersection, lightning_direction);
    color_dot = add_colors(color_dot, color_specular);
    color_dot = add_colors(color_dot, color_str);
    return(mix_color(color_dot));
}
