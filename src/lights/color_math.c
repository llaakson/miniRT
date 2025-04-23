#include "../../include/miniRT.h"

int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

uint32_t mix_color(t_xyz color)
{
    uint32_t result;

    color.x = color.x * 255;
    color.y = color.y * 255;
    color.z = color.z * 255;
    color = clamp_colors(color);
    result = ft_pixel(color.x,color.y,color.z,255);
    return (result);
}

void print_color(t_xyz color)
{
    printf("Color x %f y %f x %f\n", color.x, color.y, color.z);

}

t_xyz multiply_color_intensity(t_xyz color, double multiplier)
{
    t_xyz result;

    result.x = color.x * multiplier;
    result.y = color.y * multiplier;
    result.z = color.z * multiplier;
    return (result);
}

t_xyz multiply_color(t_xyz color1, t_xyz color2)
{
    t_xyz result;

    result.x = color1.x * color2.x;
    result.y = color1.y * color2.y;
    result.z = color1.z * color2.z;
    return (result);
}

t_xyz add_colors(t_xyz color1, t_xyz color2)
{
    t_xyz result;

    result.x = color1.x + color2.x;
    result.y = color1.y + color2.y;
    result.z = color1.z + color2.z;
    return (result);
}

t_xyz clamp_colors(t_xyz color)
{
    t_xyz result;

    result.x = fminf(255.0f, fmaxf(0.0f, color.x));
    result.y = fminf(255.0f, fmaxf(0.0f, color.y));
    result.z = fminf(255.0f, fmaxf(0.0f, color.z));
    return (result);
}

t_xyz divide_color(t_xyz color)
{
    t_xyz result;

    result.x = color.x / 255;
    result.y = color.y / 255;
    result.z = color.z / 255;
    return (result);
}